#include "notemodel.h"


NoteModel::NoteModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int NoteModel::rowCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return model.count();
}

int NoteModel::columnCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return LAST;
}

QVariant NoteModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

    if( orientation == Qt::Vertical ) {
        return section;
    }

    switch( section ) {
    case ID:
        return "ID";
    case TITLE:
        return "Название";
    case DESCRIPTION:
        return "Описание";
    case DATE:
        return "Дата";
    case ID_GROUP:
        return "ID_GROUP";
    case SUM:
        return "Сумма";
    }
    return QVariant();
}

QVariant NoteModel::data( const QModelIndex& index, int role ) const {
    if(!index.isValid())
        return QVariant();

    switch (role)
    {
    case _ID:
    {
        return model[ index.row() ][ ID ];
    }
    case _TITLE:
    {
        return model[ index.row() ][ TITLE ];
    }
    case _DESCRIPTION:
    {
        return model[ index.row() ][ DESCRIPTION ];
    }
    case _DATE:
    {
        return model[ index.row() ][ DATE ];
    }
    case _ID_GROUP:
    {
        return model[ index.row() ][ ID_GROUP ];
    }
    case _SUM:
    {
        return model[ index.row() ][ SUM ];
    }
    default:
    {
        return QVariant();
    }
    }
}

Qt::ItemFlags NoteModel::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );


    return flags;
}

void NoteModel::appendRow( const QString& title, const QString& description, const QDate& date, const int& idGroup, const qreal& sum ) {
    DataHash record;
    record[ TITLE ] = title;
    record[ DESCRIPTION ] = description;
    record[ DATE ] = date;
    record[ ID_GROUP ] = idGroup;
    record[ SUM ] = sum;
    record[ STATE_ROW ] = (int)StatesRows::ADDED;

    int row = model.count();
    beginInsertRows( QModelIndex(), row, row );
    model.append( record );
    endInsertRows();
}

void NoteModel::updateRow( int row, const QString& title, const QString& description, const QDate& date, const int& idGroup, const qreal& sum )
{
    beginResetModel();

    model[ row ][ TITLE ] = title;
    model[ row ][ DESCRIPTION ] = description;
    model[ row ][ DATE ] = date;
    model[ row ][ ID_GROUP ] = idGroup;
    model[ row ][ SUM ] = sum;
    model[ row ][ STATE_ROW ] = (int)StatesRows::EDITED;

    endResetModel();
}

void NoteModel::removeRow(int row)
{
    model[ row ][ STATE_ROW ] = StatesRows::DELETED;
}

void NoteModel::clear()
{
    model.clear();
}

bool NoteModel::select()
{
    beginResetModel();
    beginRemoveRows(createIndex(0, 0), 0, model.count());
    while(model.count() != 0)
        model.removeFirst();
    endRemoveRows();

    query.prepare(QString("SELECT * FROM %1 ORDER BY date").arg(table));
    query.exec();
    if(query.next())
    {
        int row = model.count();
        beginInsertRows( createIndex(0, 0), row, row+query.size()-1 );

        DataHash record;
        do
        {
            record[ ID ] = query.value( ID );
            record[ TITLE ] = query.value( TITLE );
            record[ DESCRIPTION ] = query.value( DESCRIPTION );
            record[ DATE ] = query.value( DATE );
            record[ ID_GROUP ] = query.value( ID_GROUP );
            record[ SUM ] = query.value( SUM );
            record[ STATE_ROW ] = StatesRows::NOT_EDITED;

            model.append( record );

        }while(query.next());

        endInsertRows();
    }

    endResetModel();

    return false;
}

bool NoteModel::select(int idGroup)
{
    beginResetModel();
    beginRemoveRows(createIndex(0, 0), 0, model.count());
    while(model.count() != 0)
        model.removeFirst();
    endRemoveRows();

    query.prepare(QString("SELECT * FROM %1 WHERE idGroup = :idGroup ORDER BY id DESC").arg(table));
    query.bindValue(":idGroup", idGroup);
    query.exec();
    if(query.next())
    {
        int row = model.count();
        beginInsertRows( createIndex(0, 0), row, row+query.size()-1 );

        DataHash record;
        do
        {
            record[ ID ] = query.value( ID );
            record[ TITLE ] = query.value( TITLE );
            record[ DESCRIPTION ] = query.value( DESCRIPTION );
            record[ DATE ] = query.value( DATE );
            record[ ID_GROUP ] = query.value( ID_GROUP );
            record[ SUM ] = query.value( SUM );
            record[ STATE_ROW ] = StatesRows::NOT_EDITED;

            model.append( record );

        }while(query.next());

        endInsertRows();
    }

    endResetModel();

    return false;
}

bool NoteModel::selectByNotebook(int idNotebook)
{
    beginResetModel();
    beginRemoveRows(createIndex(0, 0), 0, model.count());
    while(model.count() != 0)
        model.removeFirst();
    endRemoveRows();

    query.prepare(QString("SELECT * FROM %1 WHERE idGroup IN (SELECT id FROM category WHERE idNotebook = :idNotebook) ORDER BY id DESC").arg(table));
    query.bindValue(":idNotebook", idNotebook);
    query.exec();
    if(query.next())
    {
        int row = model.count();
        beginInsertRows( createIndex(0, 0), row, row+query.size()-1 );

        DataHash record;
        do
        {
            record[ ID ] = query.value( ID );
            record[ TITLE ] = query.value( TITLE );
            record[ DESCRIPTION ] = query.value( DESCRIPTION );
            record[ DATE ] = query.value( DATE );
            record[ ID_GROUP ] = query.value( ID_GROUP );
            record[ SUM ] = query.value( SUM );
            record[ STATE_ROW ] = StatesRows::NOT_EDITED;

            model.append( record );
            qDebug() << record;

        }while(query.next());

        endInsertRows();
    }

    endResetModel();

    return false;
}


bool NoteModel::saveChanges()
{
    for(int i = 0; i < model.size(); i++)
    {
        if(model[ i ][ STATE_ROW ] != StatesRows::NOT_EDITED)
        {
            qDebug() << "!= NOT_EDIT";
            if(model[ i ][ STATE_ROW ] == StatesRows::ADDED)
            {
                qDebug() << "ADDED";
                query.prepare(QString("INSERT INTO %1 (title, description, date, idGroup, sum) VALUES (:title, :description, :date, :idGroup, :sum)").arg(table));
                query.bindValue(":title", model[ i ][ TITLE ]);
                query.bindValue(":description", model[ i ][ DESCRIPTION ]);
                query.bindValue(":date", model[ i ][ DATE ]);
                query.bindValue(":idGroup", model[ i ][ ID_GROUP ]);
                query.bindValue(":sum", model[ i ][ SUM ]);

                query.exec();
            }
            else if(model[ i ][ STATE_ROW ] == StatesRows::EDITED)
            {
                qDebug() << "EDITED";
                query.prepare(QString("UPDATE %1 SET title = :title, description = :description, date = :date, idGroup = :idGroup, sum = :sum WHERE id = :id").arg(table));
                query.bindValue(":title", model[ i ][ TITLE ]);
                query.bindValue(":description", model[ i ][ DESCRIPTION ]);
                query.bindValue(":date", model[ i ][ DATE ]);
                query.bindValue(":idGroup", model[ i ][ ID_GROUP ]);
                query.bindValue(":sum", model[ i ][ SUM ]);
                query.bindValue(":id", model[ i ][ ID ]);

                query.exec();
            }
            else if(model[ i ][ STATE_ROW ] == StatesRows::DELETED)
            {
                qDebug() << "DELETED";
                query.prepare(QString("UPDATE %1 SET flag = 0 WHERE id = :id").arg(table));
                query.bindValue(":id", model[ i ][ ID ]);

                query.exec();
            }
        }
    }

    qDebug() << query.lastError();

    return true;
}

void NoteModel::setTable(QString t, QSqlDatabase *database)
{
    table = t;
    db = database;
}

qreal NoteModel::getTotalSumByGroupId(int id)
{
    qreal sum = 0;

    for(int i = 0; i < model.length(); i++)
        if(model[ i ][ ID_GROUP ] == id)
            sum += model[ i ][ SUM ].toReal();

    return sum;
}

qreal NoteModel::getTotalSumByGroupIdAndDate(int idGroup, QDate dateBegin, QDate dateEnd)
{
    qreal sum = 0;

    for(int i = 0; i < model.length(); i++)
        if(model[ i ][ ID_GROUP ] == idGroup && model[ i ][ DATE ].toDate() >= dateBegin && model[ i ][ DATE ].toDate() <= dateEnd && model[ i ][ SUM ].toReal() <= 0)
             sum += model[ i ][ SUM ].toReal();

    return sum;
}

QList<QDate> NoteModel::getListDateNotesByIdNotebook(int idNotebook, QDate dateBegin, QDate dateEnd)
{
    QList <QDate> resultList;

    query.prepare("SELECT DISTINCT(date) FROM note WHERE idGroup IN (SELECT id FROM category WHERE idNotebook = :idNotebook)");
    query.bindValue(":idNotebook", idNotebook);
    query.exec();

    while(query.next())
        if(query.value(0).toDate() >= dateBegin && query.value(0).toDate() <= dateEnd)
            resultList.append(query.value(0).toDate());

    qDebug() << resultList << dateBegin << dateEnd;

    return  resultList;
}

QStringList NoteModel::getListTotalPlusByDate(QList<QDate> listDate)
{
    QList <qreal> resultList;

    for(int i = 0; i < listDate.size(); i++)
    {
        qreal sum = 0;

        for(int j = 0; j < model.size(); j++)
        {
            if(model[ j ][ DATE ].toDate() == listDate[i] && model[ j ][ SUM ].toReal() > 0)
                sum += model[ j ][ SUM ].toReal();
        }

        resultList.append(sum);
    }

    qDebug() << resultList;

    QStringList list;

    for(int i = 0; i < resultList.size(); i++)
        list.append(QVariant(resultList.at(i)).toString());
    return list;
}

QStringList NoteModel::getListTotalMinusByDate(QList<QDate> listDate)
{
    QList <qreal> resultList;

    for(int i = 0; i < listDate.size(); i++)
    {
        qreal sum = 0;

        for(int j = 0; j < model.size(); j++)
        {
            if(model[ j ][ DATE ].toDate() == listDate[i] && model[ j ][ SUM ].toReal() < 0)
                sum += model[ j ][ SUM ].toReal();
        }

        resultList.append(sum);
    }

    QList <qreal> rlist;

    for(int i = 0; i < resultList.size(); i++)
    {
        rlist.append(qAbs(QVariant(resultList.at(i)).toFloat()));
    }

    qDebug() << rlist;
    QStringList list;
    for(int i = 0; i < rlist.size(); i++)
        list.append(QVariant(rlist.at(i)).toString());
    return list;
}

int NoteModel::getLastId()
{
    query.prepare("SELECT id FROM note ORDER BY id DESC");
    query.exec();

    query.next();

    return query.value(0).toInt();
}

QVariant NoteModel::getDataById(int id, Column column)
{
    for(int i = 0; i < model.size(); i++)
    {
        if(model[i][ID].toInt() == id)
            return model[i][column];
    }

    return QVariant();
}

bool NoteModel::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || model.count() <= index.row() ) {
        return false;
    }

    model[ index.row() ][ Column( index.column() ) ] = value;
    emit dataChanged( index, index );

    return true;
}

QHash<int, QByteArray> NoteModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles[_ID] = "_id";
    roles[_TITLE] = "_title";
    roles[_DESCRIPTION] = "_description";
    roles[_DATE] = "_icon";
    roles[_ID_GROUP] = "_id_group";
    roles[_SUM] = "_sum";

    return roles;
}
