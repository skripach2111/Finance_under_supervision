#include "labelmodel.h"

LabelModel::LabelModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int LabelModel::rowCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return model.count();
}

int LabelModel::columnCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return LAST;
}

QVariant LabelModel::headerData( int section, Qt::Orientation orientation, int role ) const
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
    case COLOR:
        return "Цвет";
    case ID_NOTEBOOK:
        return "ID_NOTEBOOK";
    case FLAG:
        return "FLAG";
    }

    return QVariant();
}

QVariant LabelModel::data( const QModelIndex& index, int role ) const {
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
    case _COLOR:
    {
        return model[ index.row() ][ COLOR ];
    }
    case _ID_NOTEBOOK:
    {
        return model[ index.row() ][ ID_NOTEBOOK ];
    }
    case _FLAG:
    {
        return model[ index.row() ][ FLAG ];
    }
    default:
    {
        return QVariant();
    }
    }
}

Qt::ItemFlags LabelModel::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );


    return flags;
}

void LabelModel::appendRow( const QString& title, const QString& color, const int& idNotebook, const bool& flag ) {
    DataHash record;
    record[ TITLE ] = title;
    record[ COLOR ] = color;
    record[ ID_NOTEBOOK ] = idNotebook;
    record[ FLAG ] = flag;
    record[ STATE_ROW ] = (int)StatesRows::ADDED;

    int row = model.count();
    beginInsertRows( QModelIndex(), row, row );
    model.append( record );
    endInsertRows();
}

void LabelModel::updateRow( int row, const QString& title, const QString& color, const int& idNotebook, const bool& flag )
{
    beginResetModel();

    model[ row ][ TITLE ] = title;
    model[ row ][ COLOR ] = color;
    model[ row ][ ID_NOTEBOOK ] = idNotebook;
    model[ row ][ FLAG ] = flag;
    model[ row ][ STATE_ROW ] = (int)StatesRows::EDITED;

    endResetModel();
}

void LabelModel::removeRow(int row)
{
    model[ row ][ STATE_ROW ] = StatesRows::DELETED;
}

bool LabelModel::select()
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
            record[ COLOR ] = query.value( COLOR );
            record[ ID_NOTEBOOK ] = query.value( ID_NOTEBOOK );
            record[ FLAG ] = query.value( FLAG );
            record[ STATE_ROW ] = StatesRows::NOT_EDITED;

            model.append( record );

        }while(query.next());

        endInsertRows();
    }

    endResetModel();

    return false;
}

bool LabelModel::select(int idNotebook)
{
    beginResetModel();
    beginRemoveRows(createIndex(0, 0), 0, model.count());
    while(model.count() != 0)
        model.removeFirst();
    endRemoveRows();

    query.prepare(QString("SELECT * FROM %1 WHERE idNotebook = :idNotebook").arg(table));
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
            record[ COLOR ] = query.value( COLOR );
            record[ ID_NOTEBOOK ] = query.value( ID_NOTEBOOK );
            record[ FLAG ] = query.value( FLAG );
            record[ STATE_ROW ] = StatesRows::NOT_EDITED;

            model.append( record );

        }while(query.next());

        endInsertRows();
    }

    endResetModel();

    return false;
}

bool LabelModel::select(int idNotebook, int idNote)
{
    beginResetModel();
    beginRemoveRows(createIndex(0, 0), 0, model.count());
    while(model.count() != 0)
        model.removeFirst();
    endRemoveRows();

    query.prepare(QString("SELECT * FROM %1 WHERE idNotebook = :idNotebook AND id IN (SELECT idLabel FROM labels_in_note WHERE idNote = :idNote)").arg(table));
    query.bindValue(":idNotebook", idNotebook);
    query.bindValue(":idNote", idNote);
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
            record[ COLOR ] = query.value( COLOR );
            record[ ID_NOTEBOOK ] = query.value( ID_NOTEBOOK );
            record[ FLAG ] = query.value( FLAG );
            record[ STATE_ROW ] = StatesRows::NOT_EDITED;

            model.append( record );

        }while(query.next());

        endInsertRows();
    }

    endResetModel();

    return false;
}


bool LabelModel::saveChanges()
{
    for(int i = 0; i < model.size(); i++)
    {
        if(model[ i ][ STATE_ROW ] != StatesRows::NOT_EDITED)
        {
            qDebug() << "!= NOT_EDIT";
            if(model[ i ][ STATE_ROW ] == StatesRows::ADDED)
            {
                qDebug() << "ADDED";
                query.prepare(QString("INSERT INTO %1 (title, color, idNotebook, flag) VALUES (:title, :color, :idNotebook, :flag)").arg(table));
                query.bindValue(":title", model[ i ][ TITLE ]);
                query.bindValue(":color", model[ i ][ COLOR ]);
                query.bindValue(":idNotebook", model[ i ][ ID_NOTEBOOK ]);
                query.bindValue(":flag", model[ i ][ FLAG ]);

                query.exec();
            }
            else if(model[ i ][ STATE_ROW ] == StatesRows::EDITED)
            {
                qDebug() << "EDITED";
                query.prepare(QString("UPDATE %1 SET title = :title, color = :color, idNotebook = :idNotebook, flag = :flag WHERE id = :id").arg(table));
                query.bindValue(":title", model[ i ][ TITLE ]);
                query.bindValue(":color", model[ i ][ COLOR ]);
                query.bindValue(":idNotebook", model[ i ][ ID_NOTEBOOK ]);
                query.bindValue(":flag", model[ i ][ FLAG ]);
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

void LabelModel::setTable(QString t, QSqlDatabase *database)
{
    table = t;
    db = database;
}

QList<QString> LabelModel::getTitleByNotebookId(int idNotebook)
{
    QList <QString> tmpList;
    for(int i = 0; i < model.size(); i++)
        if(model[ i ][ ID_NOTEBOOK ].toInt() == idNotebook)
            tmpList.append(model[ i ][ TITLE ].toString());

    return tmpList;
}

QList<int> LabelModel::getIdBaNotebookId(int idNotebook)
{
    QList <int> tmpList;
    for(int i = 0; i < model.size(); i++)
        if(model[ i ][ ID_NOTEBOOK ].toInt() == idNotebook)
            tmpList.append(model[ i ][ ID ].toInt());

    return tmpList;
}

QVariant LabelModel::getDataById(int id, Column column)
{
    for(int i = 0; i < model.size(); i++)
    {
        if(model[i][ID].toInt() == id)
            return model[i][column];
    }

    return QVariant();
}

bool LabelModel::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || model.count() <= index.row() ) {
        return false;
    }

    model[ index.row() ][ Column( index.column() ) ] = value;
    emit dataChanged( index, index );

    return true;
}

QHash<int, QByteArray> LabelModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles[_ID] = "_id";
    roles[_TITLE] = "_title";
    roles[_COLOR] = "_color";
    roles[_ID_NOTEBOOK] = "_id_notebook";
    roles[_FLAG] = "_flag";

    return roles;
}
