#include "tabwidget.h"
#include "ui_tabwidget.h"



TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget)
{
    ui->setupUi(this);
    TabWidget::prepareTabWidget();

}


void TabWidget::prepareTabWidget(){

    this->setWindowTitle("LAVANDIERE PRESSING");
    QPixmap pixmap("images/graphique.jpeg");
    ui->label->setPixmap(pixmap);
    TabWidget::prepareTabCaisse();

}

void TabWidget::prepareTabCaisse()
{
    m_pHeaderView = new QHeaderView(Qt::Horizontal);

    ui->tableView_Caisse->setModel(domcaisse.getModelGlobal());
     m_pHeaderView->setSectionsClickable(true);
    ui->tableView_Caisse->setHorizontalHeader(m_pHeaderView);
    ui->tableView_Caisse->setHorizontalHeader(m_pHeaderView);
    ui->tableView_Caisse->resizeColumnsToContents();
    ui->tableView_Caisse->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_Caisse->setSortingEnabled(true);
        connect(m_pHeaderView,SIGNAL(sectionClicked(int)),this,SLOT(sectionClicked(int)));


}

TabWidget::~TabWidget()
{
    delete ui;
}

void TabWidget::sectionClicked(int index)
{
    index=0;
    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
    m->setDynamicSortFilter(true);
    m->setSourceModel(ui->tableView_Caisse->model());
    ui->tableView_Caisse->setModel(m);
    ui->tableView_Caisse->setSortingEnabled(true);
    index++;
}


void TabWidget::on_lineEdit_rechercheCaisse_cursorPositionChanged()
{
    QString inputValue,filterChecked;
       inputValue=ui->lineEdit_rechercheCaisse->text();
       filterChecked="TYPE";

       if(ui->checkBox_afficheDepense->isChecked()){
           filterChecked="TYPE";
       }
       if(ui->checkBox_afficheVersement->isChecked()){
           filterChecked="TYPE";
       }
       if(ui->checkBox_libelle->isChecked()){
           filterChecked="LIBELLE";
       }
       if(ui->checkBox_montant->isChecked()){
           filterChecked="MONTANT";
       }
       if(ui->checkBox_annee->isChecked()){
           filterChecked="DAT";
       }
       ui->tableView_Caisse->setModel(domcaisse.getModelSpecial(inputValue,filterChecked));

}

void TabWidget::on_tableView_Caisse_doubleClicked()
{
     Caisse *cais= new Caisse();
     cais->setIDtoDisplay(ui->tableView_Caisse->currentIndex().sibling(ui->tableView_Caisse->currentIndex().row(),0).data().toInt());
     cais->setCaisse();
     cais->show();
}

void TabWidget::on_pushButton_actualiserCaisse_clicked()
{
ui->tableView_Caisse->setModel(domcaisse.getModelGlobal());
}

void TabWidget::on_pushButton_newCaisse_clicked()
{
   Caisse *cais= new Caisse();
   cais->setAjout(true);
   cais->verifAjout();
   cais->show();
}

void TabWidget::on_pushButton_bilanCaisse_clicked()
{
   bilancaisse *bilan= new bilancaisse();
   bilan->show();

}

void TabWidget::on_pushButton_historiqueCaisse_clicked()
{
    domcaisse.getHistoryFromDB();
    historiquecaisse *history= new historiquecaisse();
    history->show();
}

void TabWidget::on_tableView_Caisse_clicked()
{
   qDebug()<<"CLICKED";
}
