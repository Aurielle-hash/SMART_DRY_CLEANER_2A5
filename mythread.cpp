#include "mythread.h"
#include <QThread>

mythread::mythread(int id,QObject * parent) :QThread (parent)
{
this->socketDescriptor = id ;

}
void mythread::run()
{
    //thread starts here
    qDebug()<<socketDescriptor <<"strating thread" ;
    socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(this->socketDescriptor))
{
        emit error (socket->error());
        return;
    }

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
   qDebug()<<socketDescriptor <<"client connected" ;
   exec();
}

void mythread::readyRead()
{
   QByteArray data = socket-> readAll();
   qDebug()<<socketDescriptor <<"data in:"<< data ;
   socket->write(data);
}

void mythread::disconnected()
{   qDebug()<<socketDescriptor <<"client disconnected" ;
    socket->deleteLater();
    exit(0);
}
