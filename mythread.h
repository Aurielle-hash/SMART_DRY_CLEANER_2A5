#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class mythread : public QThread
{ Q_OBJECT
public:
    explicit mythread( int id , QObject *parent =0);
    void run() ;

signals:
     void error(QTcpSocket::SocketError socketerror);

public slots :

    void readyRead();
    void disconnected();

private :
    QTcpSocket *socket;
    int socketDescriptor;
};
/*
class mythread : public QTcpSocket
{
public:
    mythread(qintptr handle, QObject *parent = nullptr);

signals :
    void dureadyread(mythread *);


};
*/

#endif // THREAD_H
