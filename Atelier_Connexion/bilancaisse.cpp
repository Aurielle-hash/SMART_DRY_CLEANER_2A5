#include "bilancaisse.h"
#include "ui_bilancaisse.h"


bilancaisse::bilancaisse(QWidget *parent):
    QDialog(parent),
    ui(new Ui::bilancaisse)
{
    ui->setupUi(this);
    ui->dateEdit_BilanDatedebut->setDate(QDate::currentDate());
    ui->dateEdit_BilanDatefin->setDate(QDate::currentDate());

    this->setWindowTitle("Bilan de la Caisse");
    //bilancaisse::prepareTableViewBilan();//Appel de la fonction qui prepare l'interface
       ui->tableView_bilan->resizeColumnsToContents();
       ui->tableView_bilan->horizontalHeader()->setStretchLastSection(true);


       }



bilancaisse::~bilancaisse()
{
    delete ui;
}

void bilancaisse::prepareTableViewBilan(){

    QVector <QString> vectorbilan = bilancaisse::getBilanFromFile();

    QStandardItemModel *model = new QStandardItemModel(vectorbilan.size(),1,this);
    model->setHorizontalHeaderItem(0,new QStandardItem(QString("Bilan")));
    for (int i=0;i<vectorbilan.size();i++){
    QStandardItem *Row = new QStandardItem(vectorbilan[i]);
    model->setItem(i,Row);
    }
    ui->tableView_bilan->setModel(model);

}



QVector<QString> bilancaisse::getBilanFromFile()
{

    QString fileName = "bilan.txt",globalbilan="";
    QFile file(fileName);
    QVector <QString> bilanVector;
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    while (!in.atEnd()){
        QString line= in.readLine();
        bilanVector.push_back(line);
        globalbilan+=line+"\n";
    }

    file.close();
    return bilanVector;
}




void bilancaisse::on_pushButton_statistique_clicked()
{
    this->datefin= ui->dateEdit_BilanDatefin->date();
    this->datedebut= ui->dateEdit_BilanDatedebut->date();

  statistiquescaisse *statCaisse = new statistiquescaisse();
  statCaisse->setDateDebut(this->datedebut);
  statCaisse->setDateFin(this->datefin);
  statCaisse->show();

}

void bilancaisse::on_pushButton_clicked()
{
    this->datefin= ui->dateEdit_BilanDatefin->date();
    this->datedebut= ui->dateEdit_BilanDatedebut->date();
     domCaisse.getBilanFromDB(this->datedebut,this->datefin);
  bilancaisse::prepareTableViewBilan();
}
