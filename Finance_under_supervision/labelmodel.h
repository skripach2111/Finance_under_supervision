#ifndef LABELMODEL_H
#define LABELMODEL_H


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QAbstractTableModel>
#include <QObject>
#include <QDebug>

class LabelModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit LabelModel(QObject *parent = nullptr);

    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    virtual QHash<int, QByteArray> roleNames() const;

    void appendRow( const QString& title, const QString& color, const int& idNotebook, const bool& flag );
    void updateRow( int row, const QString& title, const QString& color, const int& idNotebook, const bool& flag );
    void removeRow(int row);

    bool select();
    bool select(int idNotebook);
    bool select(int idNotebook, int idNote);
    bool saveChanges();
    void setTable(QString t, QSqlDatabase *database);

    QList <QString> getTitleByNotebookId(int idNotebook);
    QList <int> getIdByNotebookId(int idNotebook);
    QList <int> getIdNoteByLabelId(int id);

    enum Column {
        ID = 0,
        TITLE,
        COLOR,
        ID_NOTEBOOK,
        FLAG,
        LAST,
        STATE_ROW
    };

    enum Role {
        _ID = Qt::UserRole + 1,
        _TITLE,
        _COLOR,
        _ID_NOTEBOOK,
        _FLAG,
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

    QString table = "label";
};

#endif // LABELMODEL_H
