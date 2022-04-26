#include "myserver.h"
#include"mythread.h"
#include "defs.h"

namespace smartdrycleaner
{
myserver::myserver(QObject *parent)
    :QTcpServer(parent)
{

}
 bool myserver::startServer(quint16 port)
 {
     return listen(QHostAddress::Any,port);
 }

void myserver:: incomingConnection(qintptr handle)
{qDebug()<<"User connected with handle:"<<handle;
    auto socket=new mythread(handle,this);
    mSockets<<socket;

    for(auto i : mSockets)
    {QTextStream T(i);
        T<<"Server: Connected :"<<handle;
        i->flush();

    }


    connect(socket,&mythread::DuReadyRead,[&]( mythread *S)
    {qDebug()<<"DuReadyRead";
        QTextStream T(S);
        auto text=T.readAll();
        for (auto i:mSockets)
        {
            QTextStream K(i);
            K<<text ;
            i->flush();
        }
    });
    connect(socket,&mythread::DuStateChanged,[&](mythread *S,int ST)
        {qDebug()<<"DuStateChanged with handle "<<S->socketDescriptor();
        if (ST==QTcpSocket::UnconnectedState ){
            qDebug()<<"Unconnected State with handle :"<<S->socketDescriptor();
            mSockets.removeOne(S);

            for(auto i: mSockets)
            {QTextStream K(i);
                K<<"Server:le client"<<S->socketDescriptor()<<"est deconnecté..";
                i->flush();
        }
            }

    });
}
}//end namespace smartdrycleaner
