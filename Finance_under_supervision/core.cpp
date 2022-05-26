#include "core.h"

Core::Core(QObject *parent)
{
    this->setParent(parent);

    if(db.connect("../fus.db").flag)
        qDebug() << "Database connected!";
    else
        qDebug() << "Error connect to database!";
}
