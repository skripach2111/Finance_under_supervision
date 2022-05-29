#include "core.h"

Core::Core(QObject *parent)
{
    this->setParent(parent);

    if(db.connect("../fus.db").flag)
        qDebug() << "Database connected!";
    else
        qDebug() << "Error connect to database!";
}

void Core::getNotebookModel()
{
    emit comingNotebookModel(db.notebookModel);
}
