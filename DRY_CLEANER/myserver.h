#ifndef SERVER_H
#define SERVER_H
#include "defs.h"
#include <QTcpServer>


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
#endif // SERVER_H
