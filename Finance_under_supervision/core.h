#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QDebug>

#include "databasemodule.h"

class Core : public QObject
{
    Q_OBJECT

    DatabaseModule db;
public:
    Core(QObject *parent = nullptr);
};

#endif // CORE_H
