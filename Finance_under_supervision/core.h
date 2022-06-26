#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QQuickItem>
#include <QDebug>

#include "databasemodule.h"

class Core : public QQuickItem
{
    Q_OBJECT

    DatabaseModule db;

    int _currentNotebook;
    int _currentGroup;
    int _currentNote;
    int _totalPlus;
    int _totalMinus;
    QDate _beginDate;
    QDate _endDate;

public:
    Core(QObject *parent = nullptr);

    Q_PROPERTY(NotebookModel* notebookModel READ notebookModel)
    Q_PROPERTY(GroupModel* groupModel READ groupModel)
    Q_PROPERTY(LabelModel* labelModel READ labelModel)
    Q_PROPERTY(NoteModel* noteModel READ noteModel NOTIFY noteModelChanged)
    Q_PROPERTY(int currentNotebook READ currentNotebook WRITE setCurrentNotebook NOTIFY currentNotebookChanged)
    Q_PROPERTY(int currentGroup READ currentGroup WRITE setCurrentGroup NOTIFY currentGroupChanged)
    Q_PROPERTY(int currentNote READ currentNote WRITE setCurrentNote NOTIFY currentNoteChanged)
    Q_PROPERTY(qreal totalPlus READ totalPlus NOTIFY totalPlusChanged)
    Q_PROPERTY(qreal totalMinus READ totalMinus NOTIFY totalMinusChanged)
    Q_PROPERTY(QDate beginDate READ beginDate WRITE setBeginDate NOTIFY beginDateChanged)
    Q_PROPERTY(QDate endDate READ endDate WRITE setEndDate NOTIFY endDateChanged)

    Q_INVOKABLE void getTotalMinus(int id);
    Q_INVOKABLE void getTotalPlus(int id);

    Q_INVOKABLE QString getNotebookTitleById(int id);
    Q_INVOKABLE void addNotebook(QString title);
    Q_INVOKABLE int getLastNotebook();

    Q_INVOKABLE qreal getTotalSumByGroupId(int id);
    Q_INVOKABLE QString getGroupTitleById(int id);
    Q_INVOKABLE QString getGroupIconById(int id);
    Q_INVOKABLE void addGroup(QString title, QString description, QString icon, int idNotebook);
    Q_INVOKABLE void removeGroup(int index);

    Q_INVOKABLE void selectNoteByCurrentNotebook();
    Q_INVOKABLE QString getNoteTitleById(int id);
    Q_INVOKABLE QString getNoteDescriptionById(int id);
    Q_INVOKABLE qreal getNoteSumById(int id);
    Q_INVOKABLE QString getNoteDateById(int id);
    Q_INVOKABLE int getNoteGroupById(int id);

    Q_INVOKABLE void addLabel(QString title, QString color, int idNotebook);
    Q_INVOKABLE void removeLabel(int index);

    Q_INVOKABLE QList <QString> getListGroupTitles(int idNotebook);
    Q_INVOKABLE QList <qreal> getListPlusByGroup(int idNotebook, QDate beginDate, QDate endDate);

    Q_INVOKABLE QList <QString> getListLabelTitles(int idNotebook);
    Q_INVOKABLE QList <qreal> getListPlusByLabel(int idNotebook, QDate beginDate, QDate endDate);

    Q_INVOKABLE QList <QDate> getListDateNotesByIdNotebook(int idNotebook, QDate dateBegin, QDate dateEnd);

    Q_INVOKABLE QStringList getListTotalPlusByDate();
    Q_INVOKABLE QStringList getListTotalMinusByDate();

    Q_INVOKABLE QStringList convertListDate();

    NotebookModel* notebookModel();
    GroupModel* groupModel();
    LabelModel* labelModel();
    NoteModel* noteModel();

    int currentNotebook();
    void setCurrentNotebook(int id);

    int currentGroup();
    void setCurrentGroup(int id);

    int currentNote();
    void setCurrentNote(int id);

    qreal totalPlus();
    qreal totalMinus();

    QDate beginDate();
    void setBeginDate(QDate date);

    QDate endDate();
    void setEndDate(QDate date);

signals:
    void currentGroupChanged();
    void currentNotebookChanged();
    void currentNoteChanged();
    void totalPlusChanged();
    void totalMinusChanged();
    void beginDateChanged();
    void endDateChanged();
    void noteModelChanged();

private slots:
    void onCurrentNotebookChanged();
    void onCurrentGroupChanged();

};

#endif // CORE_H
