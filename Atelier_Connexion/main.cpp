#include "mainwindow.h"
#include "tabwidget.h"
#include <QApplication>
#include "connection.h"

int main(int argc, char *argv[])
{
    //QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());
       QApplication a(argc, argv);

       connection c;
       bool test= c.connection_db();
    //    MainWindow w;
   //   w.show();

       TabWidget t;

       if(test){
            t.show();
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                                     QObject::tr("Connection succesful.\n"
                                           "Click CANCEL TO EXIT."),QMessageBox::Cancel);
              }
       else
       {
           QMessageBox::information(nullptr, QObject::tr("database is open"),
                                    QObject::tr("Connection failed.\n"
                                          "Click CANCEL TO EXIT."),QMessageBox::Cancel);
       }


       return a.exec();
}
