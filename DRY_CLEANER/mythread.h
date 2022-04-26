#ifndef THREAD_H
#define THREAD_H

#include "defs.h"



#include <QTcpSocket>
namespace smartdrycleaner
{
class mythread :public QTcpSocket
{
    Q_OBJECT
public:
    mythread(qintptr handle,QObject *parent =nullptr );

signals:
    void DuReadyRead(mythread *);
    void DuStateChanged (mythread *,int);
};
}//end of smartdrycleaner#endif // THREAD_H
