#include "notebookmodel.h"

NotebookModel::NotebookModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int NotebookModel::rowCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return model.count();
}

int NotebookModel::columnCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return LAST;
}

QVariant NotebookModel::headerData( int section, Qt::Orientation orientation, int role ) const
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
    }

    return QVariant();
}

QVariant NotebookModel::data( const QModelIndex& index, int role ) const {
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
    default:
    {
        return QVariant();
    }
    }
}

Qt::ItemFlags NotebookModel::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );


    return flags;
}

void NotebookModel::appendRow( const QString& title ) {
    DataHash record;
    record[ TITLE ] = title;
    record[ STATE_ROW ] = (int)StatesRows::ADDED;

    int row = model.count();
    beginInsertRows( QModelIndex(), row, row );
    model.append( record );
    endInsertRows();
}

void NotebookModel::updateRow(int row, const QString& title)
{
    beginResetModel();

    model[ row ][ TITLE ] = title;
    model[ row ][ STATE_ROW ] = (int)StatesRows::EDITED;

    endResetModel();
}

void NotebookModel::removeRow(int row)
{
    model[ row ][ STATE_ROW ] = StatesRows::DELETED;
}

bool NotebookModel::select()
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
            record[ STATE_ROW ] = StatesRows::NOT_EDITED;

            model.append( record );

        }while(query.next());

        endInsertRows();
    }

    endResetModel();

    return false;
}


bool NotebookModel::saveChanges()
{
    for(int i = 0; i < model.size(); i++)
    {
        if(model[ i ][ STATE_ROW ] != StatesRows::NOT_EDITED)
        {
            qDebug() << "!= NOT_EDIT";
            if(model[ i ][ STATE_ROW ] == StatesRows::ADDED)
            {
                qDebug() << "ADDED";
                query.prepare(QString("INSERT INTO %1 (title) VALUES (:title)").arg(table));
                query.bindValue(":title", model[ i ][ TITLE ]);

                query.exec();
            }
            else if(model[ i ][ STATE_ROW ] == StatesRows::EDITED)
            {
                qDebug() << "EDITED";
                query.prepare(QString("UPDATE %1 SET title = :title WHERE id = :id").arg(table));
                query.bindValue(":title", model[ i ][ TITLE ]);
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

void NotebookModel::setTable(QString t, QSqlDatabase *database)
{
    table = t;
    db = database;
}

qreal NotebookModel::getTotalPlusById(int id)
{
    query.prepare("SELECT SUM(sum) FROM note WHERE idGroup IN (SELECT id FROM category WHERE idNotebook = :idNotebook) AND sum > 0");
    query.bindValue(":idNotebook", id);
    query.exec();
    query.next();
    return query.value(0).toReal();
}

qreal NotebookModel::getTotalMinusById(int id)
{
    query.prepare("SELECT SUM(sum) FROM note WHERE idGroup IN (SELECT id FROM category WHERE idNotebook = :idNotebook) AND sum < 0");
    query.bindValue(":idNotebook", id);
    query.exec();
    query.next();
    return query.value(0).toReal();
}

QVariant NotebookModel::getDataById(int id, Column column)
{
    for(int i = 0; i < model.size(); i++)
    {
        if(model[i][ID].toInt() == id)
            return model[i][column];
    }

    return QVariant();
}

bool NotebookModel::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || model.count() <= index.row() ) {
        return false;
    }

    model[ index.row() ][ Column( index.column() ) ] = value;
    emit dataChanged( index, index );

    return true;
}

QHash<int, QByteArray> NotebookModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles[_ID] = "_id";
    roles[_TITLE] = "_title";

    return roles;
}
