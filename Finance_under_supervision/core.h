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
public:
    Core(QObject *parent = nullptr);

    Q_INVOKABLE void getNotebookModel();

signals:
    void comingNotebookModel(QSqlTableModel& notebookModel);
};

#endif // CORE_H
