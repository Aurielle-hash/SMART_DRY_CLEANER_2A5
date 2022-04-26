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
#include "mail/SmtpMime"
#include <QtCharts/QChartView>
//#include <QPieSlice>
//#include <QPieSeries>
#include <QLineEdit>
#include<QTextEdit>
#include<QSqlRecord>
#include <iostream>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int ret=A.connect_arduino();
    switch (ret) {
    case (0):qDebug()<<"arduino is available and connected to: "<<A.getarduino_port_name();
        break;
    case(1):qDebug()<<"arduino is available but not connected to: "<<A.getarduino_port_name();
        break;
    case(-1):qDebug()<<"arduino is not available";
        break;
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

    ui->tableView_Afficher->setModel(C.afficher());
    ui->comboBoxSup->setModel(C.afficherValeur("ID_CLT"));
    ui->comboBoxmod->setModel(C.afficherValeur("ID_CLT"));
    ui->comboBoxCode->setModel(C.afficherValeur("ID_CLT"));
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
                    ui->comboBoxCode->setModel(C.afficherValeur("ID_CLT"));

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
        ui->comboBoxCode->setModel(C.afficherValeur("ID_CLT"));

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
          painter.drawPixmap(QRect(200,200,2000,2000),QPixmap("C:/Users/aboub/Desktop/lavandiere.png"));
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



void MainWindow::on_pushButtoncode_clicked()
{
    QString idC=ui->comboBoxCode->currentText();
    /*QSqlQuery query;
    query.prepare("select NOM from client where ID_CLT like '%' || :idC || '%' ");
    query.bindValue(":idC", idC);
    query.exec();
    int nom = query.record().indexOf("NOM");
    QString nomr=query.value(nom).toString();*/

    std::string idCQr="ID du CLIENT : "+idC.toStdString();
    //std::string nomQr="Nom du CLIENT : "+nomr.toStdString();

                int n = idCQr.length();
                char char_array[n + 1];  //chaine qui va contenir l'identifiant a etre encode
                strcpy(char_array, idCQr.c_str());//copie de la chaine qui va contenir l'identifiant a etre encode
                //strcpy(char_array, nomQr.c_str());


                /*const QrCode::Ecc errCorLvl = QrCode::Ecc::HIGH;  // Error correction level
                const QrCode qr = QrCode::encodeText(char_array, errCorLvl); //generation du code QR
                C.qrCode.printRecu(qr,idCQr);*/
                std::vector<uint8_t> bytes(char_array, char_array + std::strlen(char_array));
                            const QrCode qr = QrCode::encodeSegments(
                                    {QrSegment::makeBytes(bytes)},QrCode::Ecc::HIGH);
                            C.qrCode.printRecu(qr,idCQr);


                            QMessageBox::information(nullptr, QObject::tr("Generer le code QR"),
                                                      QObject::tr("Code QR Générer avec succès .\n"
                                                                  "Click OK to exit."), QMessageBox::Ok);

}

/////////////////////////////////////MAIL

QStringList MainWindow::getRecipientsAddress(QString str)
{

    QStringList recipients;

    recipients = str.split(QRegExp(";"));

    return recipients;
}

/*void MainWindow::on_tb_getAttach1_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("All Files (*.*)"));

    ui->le_emailAttach1->setText(fileName);

}

void MainWindow::on_tb_getAttach2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("All Files (*.*)"));

    ui->le_emailAttach2->setText(fileName);
}

void MainWindow::on_tb_getAttach3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("All Files (*.*)"));

    ui->le_emailAttach3->setText(fileName);
}

void MainWindow::on_tb_getAttach4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("All Files (*.*)"));

    ui->le_emailAttach4->setText(fileName);
}*/



void MainWindow::on_geta1_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("All Files (*.*)"));

    ui->attach1->setText(fileName);
}

void MainWindow::on_geta2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("All Files (*.*)"));

    ui->attach2->setText(fileName);
}

void MainWindow::on_geta3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("All Files (*.*)"));

    ui->attach3->setText(fileName);
}

void MainWindow::on_geta4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("All Files (*.*)"));

    ui->attach4->setText(fileName);
}

void MainWindow::on_envoyer_mail_3_clicked()
{
    if(ui->lineEdit->text() != NULL && ui->lineEdit_2->text() !=NULL){
        if(ui->lineEdit_3->text().toInt() != 0 && ui->lineEdit_4->text()!= NULL){
            if(ui->lineEdit_5->text() != NULL && ui->le_toAdd_3->text() != NULL){

                SmtpClient smtp(ui->lineEdit_4->text(), ui->lineEdit_3->text().toInt(), SmtpClient::SslConnection);

                smtp.setUser(ui->lineEdit->text());
                smtp.setPassword(ui->lineEdit_2->text());

                MimeMessage message;

                EmailAddress sender(ui->lineEdit_5->text(), ui->lineEdit_9->text());
                message.setSender(&sender);

                //create list of to
                QStringList to = getRecipientsAddress(ui->le_toAdd_3->text());
                QStringList cc = getRecipientsAddress(ui->le_ccAdd_3->text());
                QStringList bcc = getRecipientsAddress(ui->le_bccAdd_3->text());

                for (QStringList::iterator it = to.begin();it != to.end(); ++it) {
                     message.addRecipient(new EmailAddress(*it),MimeMessage::To);
                }
                for (QStringList::iterator it = cc.begin();it != cc.end(); ++it) {
                     message.addRecipient(new EmailAddress(*it),MimeMessage::Cc);
                }
                for (QStringList::iterator it = bcc.begin();it != bcc.end(); ++it) {
                     message.addRecipient(new EmailAddress(*it),MimeMessage::Bcc);
                }

                //set message subject
                message.setSubject(ui->objet->text());

                MimeText text;
                text.setText(ui->le_emailContent->document()->toPlainText());
                message.addPart(&text);

                MimeAttachment attachment1(new QFile(ui->attach1->text()));
                MimeAttachment attachment2(new QFile(ui->attach2->text()));
                MimeAttachment attachment3(new QFile(ui->attach3->text()));
                MimeAttachment attachment4(new QFile(ui->attach4->text()));

                //attachments
                if(ui->attach1->text() != NULL){
                   message.addPart(&attachment1);
                }

                if(ui->attach2->text() != NULL){
                    message.addPart(&attachment2);
                }

                if(ui->attach3->text() != NULL){
                    message.addPart(&attachment3);
                }

                if(ui->attach4->text() != NULL){
                    message.addPart(&attachment4);
                }


                 if (!smtp.connectToHost()) {
                     QMessageBox::critical(this,"Failed to connect","Cannot connect to host");
                     //return -1;
                 }

                 if (!smtp.login()) {
                     QMessageBox::critical(this,"Failed to connect","Failed to login");
                    // return -2;
                 }

                 smtp.sendMail(message);

                 QMessageBox::information(this,"Email Send","Operation completed succesfully!");

                 smtp.quit();

            }else QMessageBox::information(this,"Fill info", "please input senders addres and reciever addres");
        }else QMessageBox::information(this,"Fill info", "please input port and smtp");
    }else QMessageBox::information(this,"Fill info", "please input username and password");
}

void MainWindow::update_label()
{
        data=A.read_from_arduino();
        qDebug()<<data;
        QString rec = QString(data);
        qDebug()<<rec;

        if(C.rechardui(rec)){
            QMessageBox::information(this,"LECTURE","Acces AUTORISE!");
        }
        else{
            QMessageBox::information(this,"LECTURE","Acces REFUSE!");
        }

        /*QString rec = Empl.recupererNom(QString(data)).toByteArray();

        QByteArray result= rec.toByteArray();
        QByteArray nom= Empl.recupererNom(data.toStdString());
        qDebug()<<"RESULT"<<result;

       if(data=="\xE3")
       // if(nom!="REFUS")
        {
           // QMessageBox::information(this,"LECTURE","LIVREUR AUTORISE!");
            A.notification("LIVREUR CHRISTIAN AUTHENTIFIER AVEC SUCCES!");
           A.write_to_arduino("CHRISTIAN");
            //data= "-1";
        }
        else
        {
            A.notification("ECHEC D'AUTHENTIFICATION!");
            A.write_to_arduino("REFUS");
            //data= "-1";
        }*/
}
