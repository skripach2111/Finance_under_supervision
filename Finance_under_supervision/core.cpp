#include "core.h"

Core::Core(QObject *parent)
{
    this->setParent(parent);

    if(db.connect("../fus.db").flag)
        qDebug() << "Database connected!";
    else
        qDebug() << "Error connect to database!";
}

qreal Core::getTotalSumByGroupId(int id)
{
    return db.noteModel->getTotalSumByGroupId(id);
}

NotebookModel* Core::notebookModel()
{
    return db.notebookModel;
}

GroupModel *Core::groupModel()
{
    return db.groupModel;
}

LabelModel *Core::labelModel()
{
    return db.labelModel;
}

int Core::currentNotebook()
{
    return _currentNotebook;
}

void Core::setCurrentNotebook(int id)
{
    _currentNotebook = id;
}

void Core::currentNotebookChanged()
{
    db.groupModel->select(_currentNotebook);
    db.labelModel->select(_currentNotebook);
}

int Core::currentGroup()
{
    return _currentGroup;
}

void Core::setCurrentGroup(int id)
{
    _currentGroup = id;
}
