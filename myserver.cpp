#include "myserver.h"
#include <QThread>
myserver::myserver(QObject *parent): QTcpServer(parent)
{

}
  void myserver::startserver()
{
  if(!this->listen(QHostAddress::Any,1234))
  {
  qDebug() << "could not start server";
  }
  else
  {
      qDebug () <<"listening...";
  }

  }
   void myserver::incommingconnection(int socketDescriptor)
   { qDebug() << socketDescriptor << "connection...";
       mythread  *thread = new mythread (socketDescriptor,this);
       connect(thread,SIGNAL(finishes()),thread,SLOT(deleteLater()));
thread ->start();


   }
