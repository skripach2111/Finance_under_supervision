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

public:
    Core(QObject *parent = nullptr);

    Q_PROPERTY(NotebookModel* notebookModel READ notebookModel)
    Q_PROPERTY(GroupModel* groupModel READ groupModel)
    Q_PROPERTY(LabelModel* labelModel READ labelModel)
    Q_PROPERTY(int currentNotebook READ currentNotebook WRITE setCurrentNotebook NOTIFY currentNotebookChanged)
    Q_PROPERTY(int currentGroup READ currentGroup WRITE setCurrentGroup NOTIFY currentGroupChanged)

    Q_INVOKABLE qreal getTotalSumByGroupId(int id);

    NotebookModel* notebookModel();
    GroupModel* groupModel();
    LabelModel* labelModel();

    int currentNotebook();
    void setCurrentNotebook(int id);
    void currentNotebookChanged();

    int currentGroup();
    void setCurrentGroup(int id);
    void currentGroupChanged();
};

#endif // CORE_H
