#ifndef CONNECTION_H
#define CONNECTION_H
#include "defs.h"
#include <QSqlDatabase>

class connection
{
    QSqlDatabase db;
public:
    connection();
    bool connection_db();
    void closeConnection();
};


#endif // CONNECTION_H
