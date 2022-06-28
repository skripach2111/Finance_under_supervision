#include "groupmodel.h"

GroupModel::GroupModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int GroupModel::rowCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return model.count();
}

int GroupModel::columnCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return LAST;
}

QVariant GroupModel::headerData( int section, Qt::Orientation orientation, int role ) const
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
    case ICON:
        return "Исонка";
    case ID_NOTEBOOK:
        return "ID_NOTEBOOK";
    case FLAG:
        return "FLAG";
    }

    return QVariant();
}

QVariant GroupModel::data( const QModelIndex& index, int role ) const {
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
    case _ICON:
    {
        return model[ index.row() ][ ICON ];
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

Qt::ItemFlags GroupModel::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );


    return flags;
}

void GroupModel::appendRow( const QString& title, const QString& description, const QString& icon, const int& idNotebook, const bool& flag ) {
    DataHash record;
    record[ TITLE ] = title;
    record[ DESCRIPTION ] = description;
    record[ ICON ] = icon;
    record[ ID_NOTEBOOK ] = idNotebook;
    record[ FLAG ] = flag;
    record[ STATE_ROW ] = (int)StatesRows::ADDED;

    int row = model.count();
    beginInsertRows( QModelIndex(), row, row );
    model.append( record );
    endInsertRows();
}

void GroupModel::updateRow( int row, const QString& title, const QString& description, const QString& icon, const int& idNotebook, const bool& flag )
{
    beginResetModel();

    model[ row ][ TITLE ] = title;
    model[ row ][ DESCRIPTION ] = description;
    model[ row ][ ICON ] = icon;
    model[ row ][ ID_NOTEBOOK ] = idNotebook;
    model[ row ][ FLAG ] = flag;
    model[ row ][ STATE_ROW ] = (int)StatesRows::EDITED;

    endResetModel();
}

void GroupModel::removeRow(int row)
{
    model[ row ][ STATE_ROW ] = StatesRows::DELETED;
}

bool GroupModel::select()
{
    beginResetModel();
    beginRemoveRows(createIndex(0, 0), 0, model.count());
    while(model.count() != 0)
        model.removeFirst();
    endRemoveRows();

    query.prepare(QString("SELECT * FROM %1 WHERE flag = 1").arg(table));
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
            record[ ICON ] = query.value( ICON );
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

bool GroupModel::select(int idNotebook)
{
    beginResetModel();
    beginRemoveRows(createIndex(0, 0), 0, model.count());
    while(model.count() != 0)
        model.removeFirst();
    endRemoveRows();

    query.prepare(QString("SELECT * FROM %1 WHERE idNotebook = :idNotebook AND flag = 1").arg(table));
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
            record[ ICON ] = query.value( ICON );
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


bool GroupModel::saveChanges()
{
    for(int i = 0; i < model.size(); i++)
    {
        if(model[ i ][ STATE_ROW ] != StatesRows::NOT_EDITED)
        {
            qDebug() << "!= NOT_EDIT";
            if(model[ i ][ STATE_ROW ] == StatesRows::ADDED)
            {
                qDebug() << "ADDED";
                query.prepare(QString("INSERT INTO %1 (title, description, icon, idNotebook, flag) VALUES (:title, :description, :icon, :idNotebook, :flag)").arg(table));
                query.bindValue(":title", model[ i ][ TITLE ]);
                query.bindValue(":description", model[ i ][ DESCRIPTION ]);
                query.bindValue(":icon", model[ i ][ ICON ]);
                query.bindValue(":idNotebook", model[ i ][ ID_NOTEBOOK ]);
                query.bindValue(":flag", model[ i ][ FLAG ]);

                query.exec();
            }
            else if(model[ i ][ STATE_ROW ] == StatesRows::EDITED)
            {
                qDebug() << "EDITED";
                query.prepare(QString("UPDATE %1 SET title = :title, description = :description, icon = :icon, idNotebook = :idNotebook, flag = :flag WHERE id = :id").arg(table));
                query.bindValue(":title", model[ i ][ TITLE ]);
                query.bindValue(":description", model[ i ][ DESCRIPTION ]);
                query.bindValue(":icon", model[ i ][ ICON ]);
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

void GroupModel::setTable(QString t, QSqlDatabase *database)
{
    table = t;
    db = database;
}

QList <QString> GroupModel::getGroupTitleByIdNotebook(int idNotebook)
{
    QList <QString> tmpList;
    for(int i = 0; i < model.size(); i++)
        if(model[ i ][ ID_NOTEBOOK ].toInt() == idNotebook)
            tmpList.append(model[ i ][ TITLE ].toString());

    return tmpList;
}

QList<int> GroupModel::getGroupIdByIdNotebook(int idNotebook)
{
    QList <int> tmpList;
    for(int i = 0; i < model.size(); i++)
        if(model[ i ][ ID_NOTEBOOK ].toInt() == idNotebook)
            tmpList.append(model[ i ][ ID ].toInt());

    return tmpList;
}

int GroupModel::getRowById(int id)
{
    for(int i = 0; i < model.size(); i++)
        if(id == model[i][ID].toInt())
            return i;
}

QVariant GroupModel::getDataById(int id, Column column)
{
    for(int i = 0; i < model.size(); i++)
    {
        if(model[i][ID].toInt() == id)
            return model[i][column];
    }

    return QVariant();
}

bool GroupModel::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || model.count() <= index.row() ) {
        return false;
    }

    model[ index.row() ][ Column( index.column() ) ] = value;
    emit dataChanged( index, index );

    return true;
}

QHash<int, QByteArray> GroupModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles[_ID] = "_id";
    roles[_TITLE] = "_title";
    roles[_DESCRIPTION] = "_description";
    roles[_ICON] = "_icon";
    roles[_ID_NOTEBOOK] = "_id_notebook";
    roles[_FLAG] = "_flag";

    return roles;
}
