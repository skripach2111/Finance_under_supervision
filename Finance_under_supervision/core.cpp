#include "core.h"

Core::Core(QObject *parent)
{
    this->setParent(parent);

    if(db.connect("../fus.db").flag)
        qDebug() << "Database connected!";
    else
        qDebug() << "Error connect to database!";

    connect(this, SIGNAL(currentNotebookChanged()), this, SLOT(onCurrentNotebookChanged()));
    connect(this, SIGNAL(currentGroupChanged()), this, SLOT(onCurrentGroupChanged()));
}

void Core::getTotalMinus(int id)
{
    _totalMinus = db.notebookModel->getTotalMinusById(id);
    emit totalMinusChanged();
}

void Core::getTotalPlus(int id)
{
    _totalPlus = db.notebookModel->getTotalPlusById(id);
    emit totalPlusChanged();
}

QString Core::getNotebookTitleById(int id)
{
    return db.notebookModel->getDataById(id, NotebookModel::Column::TITLE).toString();
}

qreal Core::getTotalSumByGroupId(int id)
{
    return db.noteModel->getTotalSumByGroupId(id);
}

QString Core::getGroupTitleById(int id)
{
    return db.groupModel->getDataById(id, GroupModel::Column::TITLE).toString();
}

QString Core::getGroupIconById(int id)
{
    return db.groupModel->getDataById(id, GroupModel::Column::ICON).toString();
}

QString Core::getNoteTitleById(int id)
{
    return db.noteModel->getDataById(id, NoteModel::Column::TITLE).toString();
}

QString Core::getNoteDescriptionById(int id)
{
    return db.noteModel->getDataById(id, NoteModel::Column::DESCRIPTION).toString();
}

qreal Core::getNoteSumById(int id)
{
    return db.noteModel->getDataById(id, NoteModel::Column::SUM).toReal();
}

QString Core::getNoteDateById(int id)
{
    return db.noteModel->getDataById(id, NoteModel::Column::DATE).toString();
}

int Core::getNoteGroupById(int id)
{
    return db.noteModel->getDataById(id, NoteModel::Column::ID_GROUP).toInt();
}

QList<QString> Core::getListGroupTitles(int idNotebook)
{
    return  db.groupModel->getGroupTitleByIdNotebook(idNotebook);
}

QList<qreal> Core::getListPlusByGroup(int idNotebook, QDate beginDate, QDate endDate)
{
    QList <int> listGroupId = db.groupModel->getGroupIdByIdNotebook(idNotebook);
    QList <qreal> listSum;

    for(int i = 0; i < listGroupId.size(); i++)
    {
        qreal sum = db.noteModel->getTotalSumByGroupIdAndDate(listGroupId[i], beginDate, endDate);
        if(sum <= 0)
            listSum.append(sum);
        else
            listSum.append(0);
    }

    return listSum;
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

NoteModel *Core::noteModel()
{
    return db.noteModel;
}

int Core::currentNotebook()
{
    return _currentNotebook;
}

void Core::setCurrentNotebook(int id)
{
    _currentNotebook = id;
    onCurrentNotebookChanged();
}

void Core::onCurrentNotebookChanged()
{
    db.groupModel->select(_currentNotebook);
    db.labelModel->select(_currentNotebook);

    qDebug() << "Current notebook changed!";
}

int Core::currentGroup()
{
    return _currentGroup;
}

void Core::setCurrentGroup(int id)
{
    _currentGroup = id;
    onCurrentGroupChanged();
}

int Core::currentNote()
{
    return _currentNote;
}

void Core::setCurrentNote(int id)
{
    _currentNote = id;
    db.labelModel->select(_currentNotebook, _currentNote);
}

qreal Core::totalPlus()
{
    return _totalPlus;
}

qreal Core::totalMinus()
{
    return _totalMinus;
}

QDate Core::beginDate()
{
    return _beginDate;
}

void Core::setBeginDate(QDate date)
{
    _beginDate = date;
    emit beginDateChanged();
}

QDate Core::endDate()
{
    return _endDate;
}

void Core::setEndDate(QDate date)
{
    _endDate = date;
    emit endDateChanged();
}

void Core::onCurrentGroupChanged()
{
    if(_currentGroup == -1)
        db.noteModel->select();
    else
        db.noteModel->select(_currentGroup);

    qDebug() << "Current group changed!";
}
