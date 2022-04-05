#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "staff.h"
#include "QMessageBox"
#include <QApplication>
#include <QIntValidator>
#include <QSqlQuery>
#include <QLineEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPrinter>
#include <QFile>
#include<QFileDialog>
#include <QPrintDialog>
#include<QPdfWriter>
#include <QtPrintSupport/QPrinter>
#include <QTextStream>
#include <iostream>
#include <string>
#include "myserver.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator( new QIntValidator(0, 999999, this));
    ui->le_salaire->setValidator( new QIntValidator(0, 999999, this));
    ui->le_nbh->setValidator( new QIntValidator(0, 48, this));
 ui->tabstaff->setModel(S.afficher());
 ui->le_id_supp->setValidator( new QIntValidator(0, 999999, this));


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{

int id_staff=ui->le_id->text().toInt();
QString nom=ui->le_nom->text();
QString prenom=ui->le_prenom->text();
QString email=ui->le_email->text();
int nb_heurs=ui->le_nbh->text().toInt();
int  salaire=ui->le_salaire->text().toInt();
QString fonction=ui->le_fonction->text();

Staff S(nom,prenom,id_staff,nb_heurs,salaire,email,fonction);
bool test=S.ajouter();
if (test )
{QMessageBox::information(nullptr,QObject::tr("OK"),
            QObject::tr("ajout effectuer. \n"
                        "click to exit"),QMessageBox::Cancel);
    ui->tabstaff->setModel(S.afficher());

}
else
    QMessageBox ::critical(nullptr,QObject::tr("not ok"),
                           QObject::tr ("ajout non effectuer. \n"
                                        "click to exit"),QMessageBox::Cancel);



}

void MainWindow::on_pb_supprimer_clicked()
{

Staff id_staff; id_staff.setid(ui->le_id_supp->text().toInt());
bool test=id_staff.supprimer(id_staff.getid());
if (test )
{QMessageBox::information(nullptr,QObject::tr("OK"),
            QObject::tr("suppresion effectuer. \n"
                        "click to exit"),QMessageBox::Cancel);
    ui->tabstaff->setModel(S.afficher());
}
else
    QMessageBox ::critical(nullptr,QObject::tr("not ok"),
                           QObject::tr ("suppresion non effectuer. \n"
                                        "click to exit"),QMessageBox::Cancel);



}


void MainWindow::on_pb_modifier_clicked()
{
        QString nom= ui->le_nommodif->text();
        QString prenom= ui->le_prenommodif->text();
        int nb_heurs = ui->le_nbhmodif->text().toInt();
        int id_staff = ui->le_idmodif->text().toInt();
        int salaire = ui->le_salairemodif->text().toInt();
        QString email= ui->le_emailmodif->text();
        QString fonction= ui->le_fonctionmodif->text();

      Staff S2(nom,prenom,id_staff,nb_heurs,salaire,email,fonction);
      bool test=S2.modifier(id_staff);
      if(test)
     {

          ui->tabstaff->setModel(S.afficher());
     QMessageBox::information(nullptr, QObject::tr("modifier un staff"),
                       QObject::tr("staff modifié.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

     }
       else
           QMessageBox::critical(nullptr, QObject::tr("modifier un staff"),
                       QObject::tr("Erreur !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

     }

void MainWindow::on_tri_2_clicked()
{

    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from STAFF order by nb_heurs ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id-staff"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("fonction"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_heurs"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("salaire"));


     ui->tri_4->setModel(model);

}
void MainWindow::on_tri_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from STAFF order by salaire ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id-staff"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("fonction"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_heurs"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("salaire"));


     ui->tri_5->setModel(model);
}
void MainWindow::on_tri_3_clicked()
{

    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from STAFF order by fonction ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id-staff"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("fonction"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_heurs"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("salaire"));


     ui->tri_6->setModel(model);

}

void MainWindow::on_PDF_clicked()
{
    QSqlDatabase DRY_CLEANER;
                QTableView tablemateriel;
                QSqlQueryModel * Modal=new  QSqlQueryModel();

                QSqlQuery qry;
                 qry.prepare("SELECT * FROM EMPLOIS ");
                 qry.exec();
                 Modal->setQuery(qry);
                 tablemateriel.setModel(Modal);


                 DRY_CLEANER.close();

                 QString strStream;
                 QTextStream out(&strStream);


                 const int rowCount = tablemateriel.model()->rowCount();
                 const int columnCount =  tablemateriel.model()->columnCount();

                 const QString strTitle ="Document";


                 out <<  "<html>\n"
                         "<img src='C:/Users/LENOVO/Documents/login/images/bg.png' height='120' width='120'/>"
                     "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                     <<  QString("<title>%1</title>\n").arg(strTitle)
                     <<  "</head>\n"
                     "<body bgcolor=#ffffff link=#5000A0>\n"
                    << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("Liste des materiels")
                    <<"<br>"

                    <<"<table border=1 cellspacing=0 cellpadding=2 width=\"100%\">\n";
                 out << "<thead><tr bgcolor=#f0f0f0>";
                 for (int column = 0; column < columnCount; column++)
                     if (!tablemateriel.isColumnHidden(column))
                         out << QString("<th>%1</th>").arg(tablemateriel.model()->headerData(column, Qt::Horizontal).toString());
                 out << "</tr></thead>\n";

                 for (int row = 0; row < rowCount; row++) {
                     out << "<tr>";
                     for (int column = 0; column < columnCount; column++) {
                         if (!tablemateriel.isColumnHidden(column)) {
                             QString data = tablemateriel.model()->data(tablemateriel.model()->index(row, column)).toString().simplified();
                             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                         }
                     }
                     out << "</tr>\n";
                 }
                 out <<  "</table>\n"
                         "<br><br>"
                         <<"<br>"
                         <<"<table border=1 cellspacing=0 cellpadding=2>\n";

                     out << "<thead><tr bgcolor=#f0f0f0>";

                         out <<  "</table>\n"

                     "</body>\n"
                     "</html>\n";

                 QTextDocument *document = new QTextDocument();
                 document->setHtml(strStream);

                 QPrinter printer;
                 QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                 if (dialog->exec() == QDialog::Accepted) {

                     document->print(&printer);
                 }

                 printer.setOutputFormat(QPrinter::PdfFormat);
                 printer.setPaperSize(QPrinter::A4);
                 printer.setOutputFileName("/tmp/emplois.pdf");
                 printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                 delete document;

}

void MainWindow::tablewidgetdisplay()
{
  QTableWidget * emplois_2 =  new QTableWidget (this);
  emplois_2->setRowCount(2);
  emplois_2->setColumnCount(7);
  this ->setCentralWidget(emplois_2);
}

/*void MainWindow::readdisplaytable()
{ QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOIS");
    int i=0;
QString s;

    while (query.next())
    { s=query.value(0).toString();
        cout<<s.toStdString();
        ui->emplois_2->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
         ui->emplois_2->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
          ui->emplois_2->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
           ui->emplois_2->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
            ui->emplois_2->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
             ui->emplois_2->setItem(i,5,new QTableWidgetItem(query.value(5).toString()));
      ui->emplois_2->setItem(i,6,new QTableWidgetItem(query.value(6).toString()));
     i++;
    }
}
*/



void MainWindow::on_effectuer_clicked()
{




   QSqlQuery query;
        query.prepare("SELECT * FROM EMPLOIS");
       query.exec();
        int i=0;
    QString s;

        while (query.next())
        {// s=query.value(0).toString();
           // cout<<s.toStdString()<<"freifhreiu";
            ui->emplois_2->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
            ui->emplois_2->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
            ui->emplois_2->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
            ui->emplois_2->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
            ui->emplois_2->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
            ui->emplois_2->setItem(i,5,new QTableWidgetItem(query.value(5).toString()));
            ui->emplois_2->setItem(i,6,new QTableWidgetItem(query.value(6).toString()));


            i++;
        }

       /* ui->emplois_2->cellChanged(0,1);

        query.prepare("INSERT INTO emplois (lun) "
                      "VALUES (:lun");
        query.bindValue(":lun", lun);

       query.exec();
        QTableWidgetItem *item =ui->emplois_2->currentItem();
        QString lun= item->text();
         cout<<lun.toStdString();


        QString text = ui->emplois_2->item(0,0)->text();
        cout<<text.toStdString();*/


}



void MainWindow::on_modifier_clicked()
{
    ui->emplois_2->cellChanged(0,0);
    QString text = ui->emplois_2->item(0,0)->text();
    cout<<text.toStdString();

    /*query.prepare("INSERT INTO emplois (lun) "
                  "VALUES (:lun");
    query.bindValue(":lun", lun);

   query.exec();
    QTableWidgetItem *item =ui->emplois_2->currentItem();
    QString lun= item->text();
     cout<<lun.toStdString();
*/





}
/*
void QTableWidget::cellChanged(int row,int column)
{
   QSqlQuery query ;
QString str;
QTableWidgetItem* itme = ui.emplois_2->item( row, column );
if (itm)
str = itm->text();
   query.prepare("update EMPLOIS set  ");
   query.exec();

}*/


void MainWindow::on_start_s_clicked()
{
    myserver server;
    server.startserver();

}

/*
void MainWindow::on_envoyer_clicked()
{
    // This is a first demo application of the SmtpClient for Qt project

        // First we need to create an SmtpClient object
        // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

        SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

        // We need to set the username (your email address) and the password
        // for smtp authentification.

        smtp.setUser("karimchecambou123@gmail.com");
        smtp.setPassword("livealifeuwillremember.");

        // Now we create a MimeMessage object. This will be the email.

        MimeMessage message;
        QString mal =ui->mail->text();
        QString sub =ui->subject->text();
        QString com =ui->commande->toPlainText();
        message.setSender(new EmailAddress("karimchecambou123@gmail.com", "chkampawlow"));
        message.addRecipient(new EmailAddress(mal, "karim checambou"));
        message.setSubject(sub);

        // Now add some text to the email.
        // First we create a MimeText object.

        MimeText text;

        text.setText(com);

        // Now add it to the mail

        message.addPart(&text);

        // Now we can send the mail

        smtp.connectToHost();
        smtp.login();
        if(smtp.sendMail(message))
        {
            QMessageBox::information(this,"ok","message envoyer");
        }
        else
        {
            QMessageBox::critical(this,"Error","message non envoyer");
        }
        smtp.quit();
}
*/
