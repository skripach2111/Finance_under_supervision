#ifndef NOTEBOOKMODEL_H
#define NOTEBOOKMODEL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QAbstractTableModel>
#include <QObject>
#include <QDebug>

class NotebookModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit NotebookModel(QObject *parent = nullptr);

    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    virtual QHash<int, QByteArray> roleNames() const;

    void appendRow( const QString& title );
    void updateRow( int row, const QString& title );
    void removeRow(int row);

    bool select();
    bool saveChanges();
    void setTable(QString t, QSqlDatabase *database);

    qreal getTotalPlusById(int id);
    qreal getTotalMinusById(int id);

    int getLastId();

    enum Column {
        ID = 0,
        TITLE,
        LAST,
        STATE_ROW
    };

    enum Role {
        _ID = Qt::UserRole + 1,
        _TITLE,
        _LAST,
        _STATE_ROW
    };

    enum StatesRows {
        NOT_EDITED = 0x1,
        ADDED,
        EDITED,
        DELETED
    };

    QVariant getDataById(int id, Column column);

private:

    typedef QHash< Column, QVariant > DataHash;
    typedef QList< DataHash > DataList;
    DataList model;

    QSqlDatabase *db;
    QSqlQuery query;

    QString table = "notebook";
};

#endif // NOTEBOOKMODEL_H
