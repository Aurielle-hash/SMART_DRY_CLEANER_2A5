#ifndef MYSERVER_H
#define MYSERVER_H

#include<QTcpServer>
namespace smartdrycleaner
{
class mythread;

class myserver: public QTcpServer
{
public:
    myserver(QObject* parent=nullptr);
    bool startServer(quint16 port);

private :
QList <mythread *> mSockets;
protected:
void incomingConnection(qintptr handle);

};
   } //end of smartdrycleaner
#endif // MYSERVER_H
