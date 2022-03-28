#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "staff.h"
#include "agenda.h"
#include "QMessageBox"
#include <QApplication>
#include <QIntValidator>
#include <QSqlQuery>
#include <QLineEdit>
#include <QTableWidget>
#include <QPrinter>
#include <QFile>

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
    QSqlQuery query2;
Staff id_staff; id_staff.setid(ui->le_id_supp->text().toInt());

query2.prepare("select id_staff from STAFF where id_staff=:id_staff");
query2.bindValue(":id_staff",id_staff);

query2.exec();
query2.next();

int name=query2.value(0).toInt();
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

void MainWindow::on_tri_clicked()
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


     ui->table_view_tri->setModel(model);

}
void MainWindow::on_tri_2_clicked()
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


     ui->table_view_tri_2->setModel(model);
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


     ui->table_view_tri_3->setModel(model);

}

/*void MainWindow::on_PDF_clicked()
{
    QString strStream;
               QTextStream out(&strStream);
                               const int rowCount = ui->show_fact->model()->rowCount();
                               const int columnCount = ui->show_fact->model()->columnCount();
                               QString TT = QDate::currentDate().toString("yyyy/MM/dd");



                               out <<  "<html>\n"
                                   "<head>\n"
                                   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                   <<  QString("<title>%1</title>\n").arg("strTitle")
                                   <<  "</head>\n"
                                   "<body bgcolor=#ffffff link=#5000A0>\n"
                                       "<h1 style=\"text-align: center;\">"
                                       "<strong>                                                      "+TT+" </ strong>"


                                  //     "<align='right'> " << datefich << "</align>"

                                   "<center> <H1> LES FACTURES </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";


                               // headers
                               out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                               for (int column = 0; column < columnCount; column++)
                                   if (!ui->show_fact->isColumnHidden(column))
                                       out << QString("<th>%1</th>").arg(ui->show_fact->model()->headerData(column, Qt::Horizontal).toString());
                               out << "</tr></thead>\n";

                               // data table
                               for (int row = 0; row < rowCount; row++) {
                                   out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                   for (int column = 0; column < columnCount; column++) {
                                       if (!ui->show_fact->isColumnHidden(column)) {
                                           QString data = ui->show_fact->model()->data(ui->show_fact->model()->index(row, column)).toString().simplified();
                                           out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                       }
                                   }
                                   out << "</tr>\n";
                               }
                               out <<  "</table> </center>\n"
                                   "</body>\n"
                                   "</html>\n";


                               QTextDocument *document = new QTextDocument();
                               document->setHtml(strStream);
                               QPrinter printer;

                               QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                               if (dialog->exec() == QDialog::Accepted) {
                                   document->print(&printer);
                               }


                               delete document;
}

view->setEditTriggers(QAbstractItemView::NoEditTriggers);
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("lun"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("mar"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("mer"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("jeu"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("ven"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("sam"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("dim"));
*/
void MainWindow::on_PDF_clicked()
{
    QPrinter printer(QPrinter::PrinterResolution);
             printer.setOutputFormat(QPrinter::PdfFormat);
             printer.setPaperSize(QPrinter::A4);
             printer.setOrientation(QPrinter::Landscape);
             printer.setOutputFileName(strFile);

             QTextDocument doc;
             QString style("<style>");
             style.append("table { border-collapse: collapse;font-size:10px; }");
             style.append("table, th, td { border: 1px solid black;text-align: left; }");
             //style.append("th, td { border: 1px solid black;text-align: left; }");
             style.append("</style>");

             QString text("<table><thead>");
             text.append("<tr>");
             for (int i = 0; i < emplois->columnCount(); i++) {
                 text.append("<th>").append(emplois->horizontalHeaderItem(i)->data(Qt::DisplayRole).toString()).append("</th>");
             }
             text.append("</tr></thead>");
             text.append("<tbody>");
             for (int i = 0; i < emplois->rowCount(); i++) {
                 text.append("<tr>");
                 for (int j = 0; j < emplois->columnCount(); j++) {
                     QTableWidgetItem *item = emplois->item(i, j);
                     if (!item || item->text().isEmpty()) {
                         emplois->setItem(i, j, new QTableWidgetItem("0"));
                     }
                     text.append("<td>").append(emplois->item(i, j)->text()).append("</td>");
                 }
                 text.append("</tr>");
             }
             text.append("</tbody></table>");
             doc.setDefaultStyleSheet(style);
             doc.setHtml(text);
             doc.setPageSize(printer.pageRect().size());
             doc.print(&printer);
}

