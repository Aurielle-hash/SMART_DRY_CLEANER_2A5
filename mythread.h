#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class mythread : public QThread
{
Q_OBJECT
public:
explicit mythread(int ID, QObject *parent=0);
void run();

signals:
void error(QTcpSocket::SocketError socketerror);
public slots:
void readyRead();
void disconnected();
public slots:

private:
QTcpSocket *socket;
int socketDescriptor;
};
#endif // MYTHREAD_H
