#ifndef RESULTQUERY_H
#define RESULTQUERY_H

#include <QSqlError>

class ResultQuery
{
public:
    bool flag;
    QSqlError error;

public:
    ResultQuery(bool flag, QSqlError error) {
        this->flag = flag;
        this->error = error;
    }

    ResultQuery(bool flag) {
        this->flag = flag;
    }
};

#endif // RESULTQUERY_H
