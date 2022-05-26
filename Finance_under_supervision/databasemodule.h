#ifndef DATABASEMODULE_H
#define DATABASEMODULE_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>

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
};

#endif // DATABASEMODULE_H
