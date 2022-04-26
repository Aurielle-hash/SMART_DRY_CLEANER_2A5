#include "mainwindow.h"
#include "tabwidget.h"
#include <QApplication>
#include <QtGui>
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
            a.setStyle("fusion");
            //QSound sound("tonFichier.wav");
            //sound.play();


            QMessageBox::information(nullptr, QObject::tr("database is open"),
                                     QObject::tr("Connection succesful.\n"
                                           "Click CANCEL TO EXIT."),QMessageBox::Cancel);
              }
       else
       {
           QMessageBox::information(nullptr, QObject::tr("database is open"),
                                    QObject::tr("Connection failed.\n"
                                          "Click CANCEL TO EXIT."),QMessageBox::Cancel);
           // Pour arreter :
           //sound.stop();
       }


       return a.exec();
}
