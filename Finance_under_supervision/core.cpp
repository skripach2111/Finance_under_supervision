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

void Core::addNotebook(QString title)
{
    db.notebookModel->appendRow(title);
    db.notebookModel->saveChanges();
    db.notebookModel->select();
}

int Core::getLastNotebook()
{
    return db.notebookModel->getLastId();
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

void Core::addGroup(QString title, QString description, QString icon, int idNotebook)
{
    db.groupModel->appendRow(title, description, icon, idNotebook, true);
    db.groupModel->saveChanges();
    db.groupModel->select();
}

void Core::selectNoteByCurrentNotebook()
{
    db.noteModel->selectByNotebook(_currentNotebook);
    emit noteModelChanged();
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

void Core::addLabel(QString title, QString color, int idNotebook)
{
    db.labelModel->appendRow(title, color, idNotebook, true);
    db.labelModel->saveChanges();
    db.labelModel->select();
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

QList<QString> Core::getListLabelTitles(int idNotebook)
{
    qDebug() << db.labelModel->getTitleByNotebookId(idNotebook);
    return db.labelModel->getTitleByNotebookId(idNotebook);
}

QList<qreal> Core::getListPlusByLabel(int idNotebook, QDate beginDate, QDate endDate)
{
    QList <int> listLabelId = db.labelModel->getIdByNotebookId(idNotebook);
    QList <qreal> resultList;

    for(int i = 0; i < listLabelId.size(); i++)
    {
        qreal sum = 0;
        QList <int> listNoteId = db.labelModel->getIdNoteByLabelId(listLabelId[i]);

        for(int j = 0; j < listNoteId.size(); j++)
        {
            if(QVariant(getNoteDateById(listNoteId[j])).toDate() >= beginDate && QVariant(getNoteDateById(listNoteId[j])).toDate() <= endDate && getNoteSumById(listNoteId[j]) <= 0)
                sum += getNoteSumById(listNoteId[j]);

            qDebug() << getNoteSumById(listNoteId[j]);
        }

        resultList.append(sum);
    }
    qDebug() << resultList;
    return resultList;
}

QList<QDate> Core::getListDateNotesByIdNotebook(int idNotebook, QDate dateBegin, QDate dateEnd)
{
    return db.noteModel->getListDateNotesByIdNotebook(idNotebook, dateBegin, dateEnd);
}

QStringList Core::getListTotalPlusByDate()
{
    return  db.noteModel->getListTotalPlusByDate(db.noteModel->getListDateNotesByIdNotebook(_currentNotebook, _beginDate, _endDate));
}

QStringList Core::getListTotalMinusByDate()
{
    return db.noteModel->getListTotalMinusByDate(db.noteModel->getListDateNotesByIdNotebook(_currentNotebook, _beginDate, _endDate));
}

QStringList Core::convertListDate()
{
    QList<QDate> listDate = db.noteModel->getListDateNotesByIdNotebook(_currentNotebook, _beginDate, _endDate);
    QStringList listDateString;

    for(int i = 0; i < listDate.size(); i++)
        listDateString.append(listDate.at(i).toString());

    return  listDateString;
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
    db.noteModel->selectByNotebook(_currentNotebook);
}

void Core::onCurrentNotebookChanged()
{
    db.groupModel->select(_currentNotebook);
    db.labelModel->select(_currentNotebook);
    db.noteModel->selectByNotebook(_currentNotebook);

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
        db.noteModel->selectByNotebook(_currentNotebook);
    else
        db.noteModel->select(_currentGroup);

    qDebug() << "Current group changed!";
}
