#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QObject>
#include <QDebug>
#include "mythread.h"

class myserver : public QTcpServer
{ Q_OBJECT
public:
    explicit myserver(QObject *parent=0);
    void startserver();
signals :

public slots:

protected:
    void incommingconnection(int socketDescriptor);

};

#endif // SERVER_H
