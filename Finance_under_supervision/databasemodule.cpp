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

        QSqlQuery qu;
        qu.prepare("SELECT * FROM notebook");
        qu.exec();
        while(qu.next())
            qDebug() << qu.value(0).toInt() << qu.value(1).toString();
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

void DatabaseModule::addLabelInNote(int idLabel, int idNote)
{
    QSqlQuery qu;
    qu.prepare("INSERT INTO labels_in_note (idLabel, idNote) VALUES (:idLabel, :idNote)");
    qu.bindValue(":idLabel", idLabel);
    qu.bindValue(":idNote", idNote);
    qu.exec();
}

void DatabaseModule::disconnect()
{
    db.close();
}
