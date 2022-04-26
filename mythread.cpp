#include "mythread.h"
namespace smartdrycleaner
{
mythread::mythread(qintptr handle,QObject *parent )
    :QTcpSocket(parent)
{
setSocketDescriptor(handle);
connect(this,&mythread::readyRead,[&](){
    emit DuReadyRead(this);
});
connect (this,&mythread::stateChanged,[&](int S )
{
   emit DuStateChanged(this,S);
});
}
}//end namespace smartdrycleaner
