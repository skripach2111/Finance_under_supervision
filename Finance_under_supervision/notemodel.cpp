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

bool NoteModel::select()
{
    beginResetModel();
    beginRemoveRows(createIndex(0, 0), 0, model.count());
    while(model.count() != 0)
        model.removeFirst();
    endRemoveRows();

    query.prepare(QString("SELECT * FROM %1").arg(table));
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

    query.prepare(QString("SELECT * FROM %1 WHERE idGroup = :idGroup").arg(table));
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
        sum += model[ i ][ SUM ].toReal();

    return sum;
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
