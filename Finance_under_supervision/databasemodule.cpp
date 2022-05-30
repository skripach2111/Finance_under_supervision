#include "databasemodule.h"

DatabaseModule::DatabaseModule(QObject *parent)
{
    this->setParent(parent);

    db = QSqlDatabase::addDatabase("QSQLITE");
}

DatabaseModule::DatabaseModule(QString dbName, QObject *parent)
{
    this->setParent(parent);

    db = QSqlDatabase::addDatabase("QSQLITE");
    setDatabaseName(dbName);
}

bool DatabaseModule::setDatabaseName(QString dbName)
{
    db.setDatabaseName(dbName);

    if(db.databaseName() == dbName)
        return true;
    else
        return false;
}

QString DatabaseModule::getDatabaseName()
{
    return db.databaseName();
}

ResultQuery DatabaseModule::connect()
{


    if(db.open())
    {
        notebookModel = new NotebookModel(this);
        notebookModel->select();
        groupModel = new GroupModel(this);
        groupModel->select();
        noteModel = new NoteModel(this);
        noteModel->select();
        labelModel = new LabelModel(this);
        labelModel->select();
        return ResultQuery(true);
    }

    return ResultQuery(false, db.lastError());
}

ResultQuery DatabaseModule::connect(QString dbName)
{
    if(setDatabaseName(dbName))
        return connect();

    return ResultQuery(false, db.lastError());
}

ResultQuery DatabaseModule::connect(QSqlDatabase db)
{
    this->db = db;

    return connect();
}

void DatabaseModule::disconnect()
{
    db.close();
}
