#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "materiel.h"
#include "connexion.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <qstring.h>
#include<QMessageBox>
#include<QTableView>
#include<QSqlQueryModel>
#include<QIntValidator>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QTextStream>
#include <QPrintDialog>
#include<QPdfWriter>
#include<QPainter>
#include<QDesktopServices>
#include<QFileDialog>


#include<QSystemTrayIcon>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mSystemTrayIcon=new QSystemTrayIcon(this);
    mSystemTrayIcon->setIcon(QIcon(":/test.png"));
    mSystemTrayIcon ->setVisible(true);

    ui->tablemateriel->setModel(S.afficher());

    ui->le_id_supp->setValidator(new QIntValidator (0,9999,this));
    ui->le_id_3->setValidator(new QIntValidator (0,9999,this));

    ui->le_id->setValidator(new QIntValidator (0,9999,this));
    }

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_supprimer_clicked()
{

    int id=ui->le_id_supp->text().toInt();
        QString idtest= ui->le_id_supp->text();
        if(idtest.isEmpty())
            {
                QMessageBox::critical(0,qApp->tr("erreur"),
                                      qApp->tr("veillez remplir le champs vide"),QMessageBox::Cancel);
            }
        else
        {
            QMessageBox::critical(0,qApp->tr("attention"),
                                  qApp->tr("voulez vous supprimer cette depense?"),QMessageBox::Yes,QMessageBox::No);
            if(QMessageBox::Yes)
            {
                bool test= S.supprimer(id);
                if (test)
                {
                    ui->tablemateriel->setModel(S.afficher());
                    ui->tablemateriel->setModel(S.rechercher(""));
                    ui->tablemateriel->clearSelection();
                }
            }

        }

}






void MainWindow::on_pb_ajout_clicked()
{
    int id=ui->le_id->text().toInt();

    int quantite=ui->le_quantite->text().toInt();
    QString nom=ui->le_nom->text();
    QString categorie=ui->le_cat->text();
    qreal prix=ui->le_prix->text().toInt();
stock S(id,quantite,nom,categorie,prix);
bool test=S.ajouter();
 QMessageBox msgBox;
if (test)

   { msgBox.setText("ajout avec succes");}
if (quantite<5)
{ mSystemTrayIcon->showMessage(tr("alerte"),tr("la quantite du produit est faible"));}

else

   { msgBox.setText("echec ");}
msgBox.exec();
ui->tablemateriel->setModel(S.afficher());

}


void MainWindow::on_pb_modifier_clicked()
{
    int id=ui->le_id_3->text().toInt();
    int quantite=ui->le_quantite_3->text().toInt();
    float prix=ui->le_prix_3->text().toInt();
    QString nom=ui->le_nom_3->text();
    QString categorie=ui->le_cat_3->text();

    stock S;
           bool test;
           test=S.modifier(id,quantite,nom,categorie,prix);
           if(test)
           {
              ui->tablemateriel->setModel(S.afficher());

              QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr(" modifier avec succes") ,QMessageBox::Ok);

             }else

                 QMessageBox::critical(nullptr,QObject::tr("Not Ok"),
                   QObject::tr("Erreur !.\n""Click Ok to exit."), QMessageBox::Ok);
}


void MainWindow::on_tri_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from stock order by prix_materiel desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_stock"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_materiel"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("categorie"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix_materiel"));

     ui->tablemateriel->setModel(model);

}


void MainWindow::on_groupBox_clicked()
{
   /* QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from stock order by prix_materiel desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_stock"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_materiel"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("categorie"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix_materiel"));

     ui->tablemateriel->setModel(model); */
}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from stock order by id_stock desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_stock"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_materiel"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("categorie"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix_materiel"));

     ui->tablemateriel->setModel(model);
}

void MainWindow::on_pushButton_5_clicked()
{
    stock s;
        QString choix=ui->comboBox->currentText();

        if (choix=="ID")
        {
            QString id = ui->lineEdit->text();
            ui->tablemateriel->setModel(s.rechercher(id));
        }
        if (choix=="PRIX")
        {
            QString prix = ui->lineEdit->text();
            ui->tablemateriel->setModel(s.rechercherprix(prix));
        }
        if (choix=="QUANTITE")
        {
            QString quantite = ui->lineEdit->text();
            ui->tablemateriel->setModel(s.rechercherquantite(quantite));
        }


}

void MainWindow::on_pushButton_8_clicked()
{
    QSqlDatabase db;
                QTableView tablemateriel;
                QSqlQueryModel * Modal=new  QSqlQueryModel();

                QSqlQuery qry;
                 qry.prepare("SELECT * FROM stock ");
                 qry.exec();
                 Modal->setQuery(qry);
                 tablemateriel.setModel(Modal);


                 db.close();

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
                 printer.setOutputFileName("/tmp/produit.pdf");
                 printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                 delete document;

}



                           
    

    















