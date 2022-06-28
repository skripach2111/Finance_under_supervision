#ifndef DATABASEMODULE_H
#define DATABASEMODULE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QString>
#include <QDebug>

#include "notebookmodel.h"
#include "groupmodel.h"
#include "notemodel.h"
#include "labelmodel.h"

#include "resultquery.h"

class DatabaseModule : public QObject
{
    Q_OBJECT

    QSqlDatabase db;

public:
    DatabaseModule(QObject *parent = nullptr);
    DatabaseModule(QString dbName, QObject *parent = nullptr);

    bool setDatabaseName(QString name);
    QString getDatabaseName();

    ResultQuery connect();
    ResultQuery connect(QString dbName);
    ResultQuery connect(QSqlDatabase db);

    void addLabelInNote(int idLabel, int idNote);

    void disconnect();

    NotebookModel* notebookModel;
    GroupModel* groupModel;
    NoteModel* noteModel;
    LabelModel* labelModel;
};

#endif // DATABASEMODULE_H
