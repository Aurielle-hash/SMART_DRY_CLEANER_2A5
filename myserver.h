#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QObject>
#include <QDebug>
#include "mythread.h"
//class myserver;

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

/*
class myserver : public QTcpServer
{
public:
  myserver (QObject *parent = nullptr);
private:
  QList<myserver *> mSockets ;
};
*/
#endif // SERVER_H
