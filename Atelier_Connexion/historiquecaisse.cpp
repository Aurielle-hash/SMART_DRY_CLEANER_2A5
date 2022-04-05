#include "historiquecaisse.h"
#include "ui_historiquecaisse.h"

historiquecaisse::historiquecaisse(QWidget *parent):
    QDialog(parent),
    ui(new Ui::historiquecaisse)
{
    ui->setupUi(this);
    this->setWindowTitle("Historique");
    historiquecaisse::prepareTableViewHistorique();//Appel de la fonction qui prepare l'interface
    ui->tableView_historique->resizeColumnsToContents();
    ui->tableView_historique->horizontalHeader()->setStretchLastSection(true);
}

historiquecaisse::~historiquecaisse()
{
    delete ui;
}

void historiquecaisse::prepareTableViewHistorique()
{
    QVector <QString> vectorHistorique=historiquecaisse::getHistoriqueFromFile();

    QStandardItemModel *model = new QStandardItemModel(vectorHistorique.size(),1,this);
    model->setHorizontalHeaderItem(0,new QStandardItem(QString("Historique")));
    for (int i=0;i<vectorHistorique.size();i++){
    QStandardItem *Row = new QStandardItem(vectorHistorique[i]);
    model->setItem(i,Row);
    }
    ui->tableView_historique->setModel(model);

}



QVector<QString> historiquecaisse::getHistoriqueFromFile()
{
    QString fileName = "historique.txt",globalHistorique="";
    QFile file(fileName);
    QVector <QString> HistoriqueVector;
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    while (!in.atEnd()){
        QString line= in.readLine();
        HistoriqueVector.push_back(line);
        globalHistorique+=line+"\n";
    }

    file.close();
    return HistoriqueVector;
}





