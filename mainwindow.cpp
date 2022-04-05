#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QtDebug>
#include <QMessageBox>
#include <QTableView>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QtCharts/QChartView>
//#include <QPieSlice>
//#include <QPieSeries>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_Afficher->setModel(C.afficher());
    ui->comboBoxSup->setModel(C.afficherValeur("ID_CLT"));
    ui->comboBoxmod->setModel(C.afficherValeur("ID_CLT"));
    ui->comboBoxArticleA->setModel(C.afficherValeurArticle("ID"));
    ui->comboBoxArticleM->setModel(C.afficherValeurArticle("ID"));

    ui->lineEdit_idcA->setValidator(new QIntValidator(0, 9999, this));
    //ui->lineEdit_idA->setValidator(new QIntValidator(0, 9, this));
    ui->lineEdit_NumtelA->setValidator(new QIntValidator(0, 99999999, this));

    //ui->lineEdit_idM->setValidator(new QIntValidator(0, 9, this));
    ui->lineEdit_NumtelM->setValidator(new QIntValidator(0, 99999999, this));



    /*#define mail_RX "^([a-zA-Z0-9]+(([\.\-\_]?[a-zA-Z0-9]+)+)?)\@(([a-zA-Z0-9]+[\.\-\_])+[a-zA-Z]{2,4})$"
    QRegExp rxMail(mail_RX);
    QRegExpValidator*valiMail= new QRegExpValidator(rxMail,this);

    ui->lineEdit_MailA->setValidator(valiMail);
    ui->lineEdit_MailM->setValidator(valiMail);*/


    #define NOM_RX "^([a-z]+[,.]?[ ]?|[a-z]+['-]?)+$"
    QRegExp rxNom(NOM_RX);
    QRegExpValidator*valiNom= new QRegExpValidator(rxNom,this);


    ui->lineEdit_NomA->setValidator(valiNom);
    ui->lineEdit_PrenomA->setValidator(valiNom);
    ui->lineEdit_NomM->setValidator(valiNom);
    ui->lineEdit_PrenomM->setValidator(valiNom);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Ajouter_clicked()
{
                int idc = ui->lineEdit_idcA->text().toInt();
                //int ida = ui->lineEdit_idA->text().toInt();
                int ida=ui->comboBoxArticleA->currentText().toInt();
                QString n= ui->lineEdit_NomA->text();
                QString p= ui->lineEdit_PrenomA->text();
                QString a= ui->lineEdit_AdresseA->text();
                QString m= ui->lineEdit_MailA->text();
                int num= ui->lineEdit_NumtelA->text().toInt();
                client C(idc, ida, n, p, a, m, num);

                bool test = C.ajouter();

                QMessageBox msgBox;

                if(test){
                    ui->comboBoxArticleA->setModel(C.afficherValeurArticle("ID"));
                    ui->tableView_Afficher->setModel(C.afficher());
                    msgBox.setText("Ajout avec succes");
                    ui->comboBoxmod->setModel(C.afficherValeur("ID_CLT"));
                    ui->comboBoxSup->setModel(C.afficherValeur("ID_CLT"));

                }
                else
                    msgBox.setText("Echec d'ajout");
                msgBox.exec();
}

void MainWindow::on_pushButton_Supprimer_clicked()
{
   //int id = ui->lineEdit_idcRS->text().toInt();
   int id=ui->comboBoxSup->currentText().toInt();
    bool test = C.supprimer(id);
    QMessageBox msgBox;

    if(test){
        ui->tableView_Afficher->setModel(C.afficher());
        msgBox.setText("Suppression avec succes");
        ui->comboBoxSup->setModel(C.afficherValeur("ID_CLT"));
        ui->comboBoxmod->setModel(C.afficherValeur("ID_CLT"));

    }
    else
        msgBox.setText("Echec Suppression");

    msgBox.exec();

}

void MainWindow::on_pushButton_Modifier_clicked()
{

    //int idc = ui->lineEdit_idcM->text().toInt();
    int idc=ui->comboBoxmod->currentText().toInt();
    //int id = ui->lineEdit_idM->text().toInt();
    int id=ui->comboBoxArticleM->currentText().toInt();
    QString n= ui->lineEdit_NomM->text();
    QString p= ui->lineEdit_PrenomM->text();
    QString a= ui->lineEdit_AdresseM->text();
    QString m= ui->lineEdit_MailM->text();
    int num= ui->lineEdit_NumtelM->text().toInt();
    client C(idc, id, n, p, a, m, num);

    bool test = C.modifier(idc);

    QMessageBox msgBox;

    if(test){
        //ui->comboBoxmod->setModel(C.afficherValeur("ID_CLT"));
        ui->tableView_Afficher->setModel(C.afficher());
        msgBox.setText("Modifier avec succes");

    }
    else
        msgBox.setText("Echec de modification");
    msgBox.exec();

}

void MainWindow::on_pushButton_refresh_clicked()
{
    ui->tableView_Afficher->setModel(C.afficher());
    ui->comboBoxSup->setModel(C.afficherValeur("ID_CLT"));
}



void MainWindow::on_checkBoxNM_stateChanged(int arg1)
{
    bool nm=ui->checkBoxNM->isChecked();
    bool nd=ui->checkBoxND->isChecked();
    bool pm=ui->checkBoxPM->isChecked();
    bool pd=ui->checkBoxPD->isChecked();

    if(nm && !nd && !pm && !pd)
     ui->tableView_Afficher->setModel(C.trierA("NOM"));
     else
         ui->tableView_Afficher->setModel(C.afficher());


    }

void MainWindow::on_checkBoxND_stateChanged(int arg1)
{
    bool nm=ui->checkBoxNM->isChecked();
    bool nd=ui->checkBoxND->isChecked();
    bool pm=ui->checkBoxPM->isChecked();
    bool pd=ui->checkBoxPD->isChecked();

    if(!nm && nd && !pm && !pd)
     ui->tableView_Afficher->setModel(C.trierD("NOM"));
     else
         ui->tableView_Afficher->setModel(C.afficher());
}

void MainWindow::on_checkBoxPM_stateChanged(int arg1)
{
    bool nm=ui->checkBoxNM->isChecked();
    bool nd=ui->checkBoxND->isChecked();
    bool pm=ui->checkBoxPM->isChecked();
    bool pd=ui->checkBoxPD->isChecked();

    if(!nm && !nd && pm && !pd)
     ui->tableView_Afficher->setModel(C.trierA("PRENOM"));
     else
         ui->tableView_Afficher->setModel(C.afficher());
}

void MainWindow::on_checkBoxPD_stateChanged(int arg1)
{
    bool nm=ui->checkBoxNM->isChecked();
    bool nd=ui->checkBoxND->isChecked();
    bool pm=ui->checkBoxPM->isChecked();
    bool pd=ui->checkBoxPD->isChecked();

    if(!nm && !nd && !pm && pd)
     ui->tableView_Afficher->setModel(C.trierD("PRENOM"));
     else
         ui->tableView_Afficher->setModel(C.afficher());
}

void MainWindow::on_pushButtonrechercher_clicked()
{

    QString r = ui->lineEditrechercher->text();

    /*m test = C.rechercher(r);
    QMessageBox msgBox;
    if(test){
        ui->tableView_Afficher->setModel(C.rechercher("ID_CLT"));
    }
    else{
        msgBox.setText("ID inexistant");
    msgBox.exec();
    }*/

    if(r.length()>0)
     ui->tableView_Afficher->setModel(C.rechercher(r));
     else
         ui->tableView_Afficher->setModel(C.afficher());
}



void MainWindow::on_pushButton_pdf_clicked()
{
    QPdfWriter pdf("C:/Users/aboub/Desktop/PDFclient.pdf");

          QPainter painter(&pdf);

          int i = 4000;
          painter.setPen(Qt::red);
          painter.setFont(QFont("Arial", 30));
          painter.drawPixmap(QRect(200,200,2000,2000),QPixmap("C:/Users/aboub/Desktop/teasing.png"));
          painter.drawText(3000,1500,"LISTE DES CLIENTS");
          painter.setPen(Qt::black);
          painter.setFont(QFont("Arial", 50));
          // painter.drawText(1100,2000,afficheDC);
          painter.drawRect(2700,200,7300,2600);
          //painter.drawRect(1500,200,7300,2600);
          //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
          painter.drawRect(0,3000,9600,500);
          painter.setFont(QFont("Arial", 9));
          painter.drawText(300,3300,"ID_CLIENT");
          painter.drawText(2300,3300,"ID_ARTICLE");
          painter.drawText(4300,3300,"NOM");
          painter.drawText(6300,3300,"PRENOM");
          painter.drawText(8000,3300,"ADRESSE");
          painter.drawText(10300,3300,"MAIL");
          painter.drawText(12300,3300,"NUMTEL");
          //painter.drawText(14300,3300,"MAIL");
          QSqlQuery query;
          query.prepare("select * from client");
          query.exec();
          while (query.next())
          {
              painter.drawText(300,i,query.value(0).toString());
              painter.drawText(2300,i,query.value(1).toString());
              painter.drawText(4300,i,query.value(2).toString());
              painter.drawText(6300,i,query.value(3).toString());
              painter.drawText(8000,i,query.value(4).toString());
              painter.drawText(10000,i,query.value(5).toString());
              painter.drawText(12000,i,query.value(6).toString());
              //painter.drawText(14000,i,query.value(7).toString());
              i = i +500;
          }

          int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
          if (reponse == QMessageBox::Yes)
          {
              QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/aboub/Desktop/PDFclient.pdf"));

              painter.end();
          }
          if (reponse == QMessageBox::No)
          {
              painter.end();
          }
}


void MainWindow::on_pushButton_excel_clicked()
{
    QTableView *table;
                   table = ui->tableView_Afficher;

                   QString filters("CSV files (.xlsx);;All files (.*)");
                   QString defaultFilter("CSV files (*.xlsx)");
                   QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                      filters, &defaultFilter);
                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();
                   if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                       QTextStream data(&file);
                       QStringList strList;
                       for (int i = 0; i < model->columnCount(); i++) {
                           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                           else
                               strList.append("");
                       }
                       data << strList.join(";") << "\n";
                       for (int i = 0; i < model->rowCount(); i++) {
                           strList.clear();
                           for (int j = 0; j < model->columnCount(); j++) {

                               if (model->data(model->index(i, j)).toString().length() > 0)
                                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") + "\n";
                       }
                       file.close();
                       QMessageBox::information(nullptr, QObject::tr("Exporter le fichier excel"),
                                                 QObject::tr("Fichier Générer avec succès .\n"
                                                             "Click OK to exit."), QMessageBox::Ok);
                   }
}
