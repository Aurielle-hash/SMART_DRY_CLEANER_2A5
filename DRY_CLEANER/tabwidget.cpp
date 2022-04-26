#include "tabwidget.h"
#include "ui_tabwidget.h"

QString days ="";
bool card ;
using qrcodegen::QrCode;


TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget)
{
    ui->setupUi(this);
    TabWidget::prepareTabWidget();

}


void TabWidget::prepareTabWidget(){

    this->setWindowTitle("LAVANDIERE PRESSING");

    TabWidget::prepareTabCaisse();

    TabWidget::prepareTabStock();
    TabWidget::prepareTabemploye();
    /*TabWidget::prepareTabArticle();*/
    TabWidget::prepareTabClient();

}

void TabWidget::prepareTabemploye()
{
    ui->le_id->setValidator( new QIntValidator(0, 999999, this));
    ui->le_salaire->setValidator( new QIntValidator(0, 999999, this));
    ui->le_nbh->setValidator( new QIntValidator(0, 48, this));

       QSqlQueryModel* model2=new QSqlQueryModel();
           model2->setQuery("select ID_STAFF from STAFF");
           ui->comboBox_id->setModel(model2);
    ui->tabstaff->setModel(St.afficher());


}


void TabWidget::prepareTabStock()
{
    //********** ARDUINO CODE

        int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).

         //********** ARDUINO YOUFA

        mSystemTrayIcon=new QSystemTrayIcon(this);
        mSystemTrayIcon->setIcon(QIcon(":/test1.png"));
        mSystemTrayIcon ->setVisible(true);

        ui->tablemateriel->setModel(S.afficher());

        ui->le_id_supp->setValidator(new QIntValidator (0,9999,this));
        ui->le_id_3->setValidator(new QIntValidator (0,9999,this));

        ui->le_id->setValidator(new QIntValidator (0,9999,this));
        ui->le_nom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z_]{0,20}"),this));
        ui->le_cat->setValidator(new QRegExpValidator(QRegExp("[A-Za-z_]{0,20}"),this));


}

void TabWidget::prepareTabClient()

{
      ui->tableView_Afficher->setModel(C.afficher());
      ui->comboBoxSup->setModel(C.afficherValeur("ID_CLT"));
      ui->comboBoxmod->setModel(C.afficherValeur("ID_CLT"));
      ui->comboBoxCode->setModel(C.afficherValeur("ID_CLT"));
      ui->comboBoxArticleA->setModel(C.afficherValeurArticle("ID"));
      ui->comboBoxArticleM->setModel(C.afficherValeurArticle("ID"));
      ui->lineEdit_idcA->setValidator(new QIntValidator(0, 9999, this));
      ui->lineEdit_NumtelA->setValidator(new QIntValidator(0, 99999999, this));
      ui->lineEdit_NumtelM->setValidator(new QIntValidator(0, 99999999, this));
      #define NOM_RX "^([a-z]+[,.]?[ ]?|[a-z]+['-]?)+$"
    QRegExp rxNom(NOM_RX);
    QRegExpValidator*valiNom= new QRegExpValidator(rxNom,this);
    ui->lineEdit_NomA->setValidator(valiNom);
        ui->lineEdit_PrenomA->setValidator(valiNom);
        ui->lineEdit_NomM->setValidator(valiNom);
        ui->lineEdit_PrenomM->setValidator(valiNom);

}



void TabWidget::prepareTabCaisse()
{
    ui->stackedWidget->setCurrentIndex(0);
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


   //GESTION CAISSE
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

void TabWidget::prepareBilan()
{

    ui->stackedWidget->setCurrentIndex(1);
    ui->dateEdit_BilanDatedebut->setDate(QDate::currentDate());
    ui->dateEdit_BilanDatefin->setDate(QDate::currentDate());

    //this->setWindowTitle("Bilan de la Caisse");
    //TabWidget::prepareTableViewBilan();//Appel de la fonction qui prepare l'interface
       ui->tableView_bilan->resizeColumnsToContents();
       ui->tableView_bilan->horizontalHeader()->setStretchLastSection(true);
}

void TabWidget::prepareCaisse()
{

    ui->stackedWidget->setCurrentIndex(4);
    this->Blocked=true;
    this->ajout=false;
   // this->setWindowTitle("Fiche Caisse");
    ui->pushButton_bloquedCaisse->setEnabled(true);
    ui->pushButton_supprimerCaisse->setEnabled(true);
       this->PixTrueIcon=QPixmap("C:/Users/Clavel Njanen/images/True_icon.png");
       this->PixFalseIcon=QPixmap("C:/Users/Clavel Njanen/images/False_icon.png");

}

void TabWidget::prepareStats()
{

    ui->stackedWidget->setCurrentIndex(3);
    //this->setWindowTitle("Statistiques caisse");
    //this->datedebut=QDate::fromString("03/03/1998","dd/MM/yyyy");
    //this->datefin=QDate::fromString("05/06/2000","dd/MM/yyyy");
    TabWidget::makePlot();
}

void TabWidget::prepareHistory()
{

    ui->stackedWidget->setCurrentIndex(2);
    //this->setWindowTitle("Historique");
    TabWidget::prepareTableViewHistorique();//Appel de la fonction qui prepare l'interface
    ui->tableView_historique->resizeColumnsToContents();
    ui->tableView_historique->horizontalHeader()->setStretchLastSection(true);
}



void TabWidget::prepareTableViewBilan(){

    QVector <QString> vectorbilan = TabWidget::getBilanFromFile();

    QStandardItemModel *model = new QStandardItemModel(vectorbilan.size(),1,this);
    model->setHorizontalHeaderItem(0,new QStandardItem(QString("Bilan")));
    for (int i=0;i<vectorbilan.size();i++){
    QStandardItem *Row = new QStandardItem(vectorbilan[i]);
    model->setItem(i,Row);
    }
    ui->tableView_bilan->setModel(model);

}

QVector<QString> TabWidget::getBilanFromFile()
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
     setIDtoDisplay(ui->tableView_Caisse->currentIndex().sibling(ui->tableView_Caisse->currentIndex().row(),0).data().toInt());
      TabWidget::prepareCaisse();
     setCaisse();

}

void TabWidget::on_pushButton_actualiserCaisse_clicked()
{
ui->tableView_Caisse->setModel(domcaisse.getModelGlobal());
}

void TabWidget::verifAjout()
{
    if (this->ajout){

            ui->stackedWidget->setCurrentIndex(4);
           //this->setWindowTitle("Nouvelle fiche Caisse");
            /*PixTrueIcon=QPixmap("C:/Users/Clavel Njanen/images/True_icon.png");
            PixFalseIcon=QPixmap("C:/Users/Clavel Njanen/images/False_icon.png");*/
            ui->lineEdit_montant->clear();
            ui->dateEdit_date->clear();
            ui->plainTextEdit_description->clear();

          ui->pushButton_bloquedCaisse->setEnabled(false);
          ui->pushButton_supprimerCaisse->setEnabled(false);
          ui->dateEdit_date->setDate(QDate::currentDate());
     }

}

void TabWidget::setCaisse()
{
    domcaisse.getData(IDtoDisplay);

       ui->lineEdit_montant->setText(QString::number(domcaisse.getMontant()));
       ui->dateEdit_date->setDate(domcaisse.getDate());
       ui->plainTextEdit_description->setPlainText(domcaisse.getLibelle());

       ui->comboBox_type->setCurrentIndex(ui->comboBox_type->findData(domcaisse.getType(), Qt::DisplayRole));
        cleanControlFiche();

}

void TabWidget::cleanControlFiche()
{
    ui->label_dateControl->clear();
    ui->label_typeControl->clear();
    ui->label_descriptionControl->clear();
    ui->label_montantControl->clear();

}

void TabWidget::on_pushButton_newCaisse_clicked()
{

   setAjout(true);
   verifAjout();

}

void TabWidget::on_pushButton_bilanCaisse_clicked()
{
   TabWidget::prepareBilan();

}

void TabWidget::prepareTableViewHistorique()
{
    QVector <QString> vectorHistorique=TabWidget::getHistoriqueFromFile();

    QStandardItemModel *model = new QStandardItemModel(vectorHistorique.size(),1,this);
    model->setHorizontalHeaderItem(0,new QStandardItem(QString("Historique")));
    for (int i=0;i<vectorHistorique.size();i++){
    QStandardItem *Row = new QStandardItem(vectorHistorique[i]);
    model->setItem(i,Row);
    }
    ui->tableView_historique->setModel(model);

}



QVector<QString> TabWidget::getHistoriqueFromFile()
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

void TabWidget::on_pushButton_historiqueCaisse_clicked()
{
    domcaisse.getHistoryFromDB();
   TabWidget::prepareHistory();

}

void TabWidget::on_tableView_Caisse_clicked()
{
   qDebug()<<"CLICKED";
}

void TabWidget::on_pushButton_validerBilan_clicked()
{
    this->datefin= ui->dateEdit_BilanDatefin->date();
    this->datedebut= ui->dateEdit_BilanDatedebut->date();
     domcaisse.getBilanFromDB(this->datedebut,this->datefin);
  TabWidget::prepareTableViewBilan();
}

void TabWidget::on_pushButton_retour_a_Caisse_b_clicked()
{
    TabWidget::prepareTabCaisse();
}

void TabWidget::on_pushButton_statistique_clicked()
{
    setDateDebut(ui->dateEdit_BilanDatedebut->date());
    setDateFin(ui->dateEdit_BilanDatefin->date());
    TabWidget::prepareStats();
}

void TabWidget::on_pushButton_retour_a_Caisse_h_clicked()
{

    TabWidget::prepareTabCaisse();
}

void TabWidget::makePlot()
{

    // create empty bar chart objects:
        QCPBars *depense = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis); //regen
        QCPBars *versement = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis); //nuclear

        ui->customPlot->addPlottable(depense);
        ui->customPlot->addPlottable(versement);
        // Initialisation des noms et des couleurs:
        QPen pen;
            pen.setWidthF(1.2);
            depense->setName("Depenses");
            pen.setColor(QColor(255, 131, 0));
            depense->setPen(pen);
            depense->setBrush(QColor(255, 131, 0, 50));

            versement->setName("Versements");
            pen.setColor(QColor(1, 92, 191));
            versement->setPen(pen);
            versement->setBrush(QColor(1, 92, 191, 50));

            // stack bars ontop of each other:
                depense->moveAbove(versement);

                // prepare x axis with Date labels:
                    QVector<double> ticks;
                    QVector<QString> labels=domcaisse.getListDate(datedebut,datefin);
                    for (int i=0;i<labels.size();i++){
                        qDebug()<< labels[i];
                        ticks << (i+1);
                    }

                   ui->customPlot->xAxis->setAutoTicks(false);
                    ui->customPlot->xAxis->setAutoTickLabels(false);
                    ui->customPlot->xAxis->setTickVector(ticks);
                    ui->customPlot->xAxis->setTickVectorLabels(labels);
                    ui->customPlot->xAxis->setTickLabelRotation(60);
                    ui->customPlot->xAxis->setSubTickCount(0);
                    ui->customPlot->xAxis->setTickLength(0, 4);
                    ui->customPlot->xAxis->grid()->setVisible(true);
                    ui->customPlot->xAxis->setRange(0,labels.size()+1);

                    // prepare y axis:
                     ui->customPlot->yAxis->setRange(0, 25.1);
                     ui->customPlot->yAxis->setPadding(5); // un peu plus d'espace à la bordure de gauche
                     ui->customPlot->yAxis->setLabel("Entrées-Sorties/Date");
                     ui->customPlot->yAxis->grid()->setSubGridVisible(true);
                     QPen gridPen;

                     gridPen.setStyle(Qt::SolidLine);
                     gridPen.setColor(QColor(0, 0, 0, 25));
                     ui->customPlot->yAxis->grid()->setPen(gridPen);
                     gridPen.setStyle(Qt::DotLine);
                     ui->customPlot->yAxis->grid()->setSubGridPen(gridPen);

                     // Add data:
                     QVector<double> depense_Data, versementData;

                     //Implémenter une boucle !
                         for (int i=0;i<labels.size();i++){

                             QDate date= QDate::fromString(labels[i],"dd/MM/yyyy");

                             depense_Data << domcaisse.getMontantTotalFraisParDate(date,"depense");
                             versementData << domcaisse.getMontantTotalFraisParDate(date,"versement");


                         }

                          depense->setData(ticks,depense_Data);
                          versement->setData(ticks,versementData);

                          // setup legend:
                          ui->customPlot->legend->setVisible(true);
                          ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                          ui->customPlot->legend->setBrush(QColor(255, 255, 255, 200));
                          QPen legendPen;
                          legendPen.setColor(QColor(130, 130, 130, 200));
                          ui->customPlot->legend->setBorderPen(legendPen);
                          QFont legendFont = font();
                          legendFont.setPointSize(10);
                          ui->customPlot->legend->setFont(legendFont);
                          ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}




void TabWidget::on_pushButton_retourBilan_clicked()
{
    TabWidget::prepareBilan();
}

bool TabWidget::VerifDate()
{

    if (ui->dateEdit_date->date()==QDate::fromString("01/01/1000","dd/MM/yyyy"))
       {
           ui->label_dateControl->setPixmap(PixFalseIcon);
           return false;
       }
       else
       {

        ui->label_dateControl->setPixmap(PixTrueIcon);
           return true;
       }
}

bool TabWidget::VerifType()
{

    if (ui->comboBox_type->currentIndex()>-1)
    {
         ui->label_typeControl->setPixmap(PixTrueIcon);
        return true;
    }
    else
    {
         ui->label_typeControl->setPixmap(PixFalseIcon);
        return false;
    }
}

bool TabWidget::VerifMontant()
{

    if (ui->lineEdit_montant->text().isEmpty() || ui->lineEdit_montant->text().contains(QRegExp("[^.0-9]")) || ui->lineEdit_montant->text().length()<3 || ui->lineEdit_montant->text().length()>8)
    {
        ui->label_montantControl->setPixmap(PixFalseIcon);
        return false;
    }
    else
    {
        ui->label_montantControl->setPixmap(PixTrueIcon);
        return true;
    }
}


void TabWidget::on_pushButton_sauvegarderCaisse_clicked()
{

    if(!this->ajout){

             domcaisse.setLibelle(ui->plainTextEdit_description->toPlainText());
             domcaisse.setDate(ui->dateEdit_date->date());
             domcaisse.setMontant(ui->lineEdit_montant->text().toFloat());
             domcaisse.setType(ui->comboBox_type->currentText());


             if (this->Blocked){
                 QMessageBox::critical(this,
                                       tr("CAISSE PRESSING"),
                                       tr("L'interface est bloquée, Veuillez la débloquée !") );
             }
             else{

                  VerifDate();
                  VerifMontant();
                  VerifType();

                  if( VerifDate() && VerifMontant() && VerifType()){

                      if (domcaisse.update(this->IDtoDisplay)){
                                     QMessageBox::information(this,
                                                              tr("CAISSE PRESSING"),
                                                              tr("Caisse modifiée avec succès!"));
                      }
                      else{
                          QMessageBox::critical(this,
                                                tr("CAISSE PRESSING"),
                                                tr("caisse n'a pas été modifiée, Une erreur s'est produite lors de l'insertion des données dans la base !"));
                      }

                  }
                      else{
                          QMessageBox::critical(this,
                                                tr("CAISSE PRESSING"),
                                                tr("La caisse n'a pas été modifiée, Veuillez verifier les champs  saisis !"));
                  }
              }
          }

    else
    {
        domcaisse.setLibelle(ui->plainTextEdit_description->toPlainText());
        domcaisse.setDate(ui->dateEdit_date->date());
        domcaisse.setMontant(ui->lineEdit_montant->text().toFloat());
        domcaisse.setType(ui->comboBox_type->currentText());

        VerifDate();
        VerifMontant();
        VerifType();

        if( VerifDate() && VerifMontant() && VerifType())
        {
            if(domcaisse.found(domcaisse.getType(),domcaisse.getLibelle())<1){
                if (domcaisse.ajout()){
                     QMessageBox::information(this,
                                             tr("CAISSE PRESSING"),
                                             tr("La caisse a été ajoutée avec succès!"));
                             }
            }

            else {
                QMessageBox::critical(this,
                                     tr("CAISSE PRESSING"),
                                     tr("La caisse n'a pas été ajoutée, car elle existe déjà dans la base de données !") );
             }

        }
        else{
            QMessageBox::critical(this,
                                  tr("CAISSE PRESSING"),
                                  tr("La caisse n'a pas été ajoutée, Veuillez verifier les champs saisis !") );
        }
    }
}

void TabWidget::on_pushButton_supprimerCaisse_clicked()
{

    QMessageBox::StandardButton reply;
           reply = QMessageBox::question(this, "Supprimer Caisse", "Etes-vous sûr de vouloir supprimer cette caisse ?",
                                         QMessageBox::Yes|QMessageBox::No);
           if (reply == QMessageBox::Yes) {

               if (domcaisse.supprime(IDtoDisplay)){
                   QMessageBox::information(this,
                                            tr("CAISSE PRESSING"),
                                            tr("Cette caisse a été supprimée avec succès !") );
                                           // this->hide();
              }
           }
}

void TabWidget::on_pushButton_bloquedCaisse_clicked()
{

    if(this->Blocked){
        ui->pushButton_bloquedCaisse->setText("Bloquer");
    }
    else {
        ui->pushButton_bloquedCaisse->setText("Débloquer");
    }
    this->Blocked=!Blocked;
}

void TabWidget::on_pushButton_retour_caisse_E_clicked()
{
    TabWidget::prepareTabCaisse();
}






     // GESTION CLIENTS

void TabWidget::on_pushButton_Ajouter_clicked()
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

void TabWidget::on_pushButton_Modifier_clicked()
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

void TabWidget::on_pushButton_Supprimer_clicked()
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

void TabWidget::on_pushButton_refresh_clicked()
{
    ui->tableView_Afficher->setModel(C.afficher());
    ui->comboBoxSup->setModel(C.afficherValeur("ID_CLT"));
}


void TabWidget::on_checkBoxNM_stateChanged(int arg1)
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

void TabWidget::on_checkBoxND_stateChanged(int arg1)
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

void TabWidget::on_checkBoxPM_stateChanged(int arg1)
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

void TabWidget::on_checkBoxPD_stateChanged(int arg1)
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


void TabWidget::on_pushButtonrechercher_clicked()
{

     QString r = ui->lineEditrechercher->text();

     if(r.length()>0)
         ui->tableView_Afficher->setModel(C.rechercher(r));
         else
             ui->tableView_Afficher->setModel(C.afficher());
}

void TabWidget::on_pushButton_pdf_clicked()
{
    QPdfWriter pdf("C:/Users/Clavel Njanen/Desktop/PDFclient.pdf");

            QPainter painter(&pdf);

            int i = 4000;
            painter.setPen(Qt::red);
            painter.setFont(QFont("Arial", 30));
            painter.drawPixmap(QRect(200,200,2000,2000),QPixmap("C:/Users/Clavel Njanen/images/graphique.png"));
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
                QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Clavel Njanen/Desktop/PDFclient.pdf"));

                painter.end();
            }
            if (reponse == QMessageBox::No)
            {
                painter.end();
            }

}

void TabWidget::on_pushButton_excel_clicked()
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

void TabWidget::on_pushButtoncode_clicked()
{

    QString idC=ui->comboBoxCode->currentText();

       std::string idCQr="0000000000000000000000000000"+idC.toStdString();

                   int n = idCQr.length();
                   char char_array[n + 1];  //chaine qui va contenir l'identifiant a etre encode
                   strcpy(char_array, idCQr.c_str());//copie de la chaine qui va contenir l'identifiant a etre encode



                   /*const QrCode::Ecc errCorLvl = QrCode::Ecc::HIGH;  // Error correction level
                   const QrCode qr = QrCode::encodeText(char_array, errCorLvl); //generation du code QR
                   C.qrCode.printRecu(qr,idCQr);*/
                   std::vector<uint8_t> bytes(char_array, char_array + std::strlen(char_array));
                               const QrCode qr = QrCode::encodeSegments(
                                       {QrSegment::makeBytes(bytes)},
                                           QrCode::Ecc::HIGH);
                               C.qrCode.printRecu(qr,idCQr);

                               QMessageBox::information(nullptr, QObject::tr("Generation de code QR"),
                                                         QObject::tr("Code QR generer avec succes .\n"
                                                                     "Click OK to exit."), QMessageBox::Ok);
}

QStringList TabWidget::getRecipientsAddress(QString str)
{

    QStringList recipients;

    recipients = str.split(QRegExp(";"));

    return recipients;
}


void TabWidget::on_geta1_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Open File"), "", tr("All Files (*.*)"));

       ui->attach1->setText(fileName);

}

void TabWidget::on_geta2_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), "", tr("All Files (*.*)"));

        ui->attach2->setText(fileName);
}

void TabWidget::on_geta3_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), "", tr("All Files (*.*)"));

        ui->attach3->setText(fileName);
}

void TabWidget::on_geta4_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), "", tr("All Files (*.*)"));

        ui->attach4->setText(fileName);
}

void TabWidget::on_envoyer_mail_3_clicked()
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






      //GESTION STOCK

void TabWidget::on_pb_supprimer_clicked()
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
                                     qApp->tr("voulez vous supprimer ce materiel?"),QMessageBox::Yes,QMessageBox::No);
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

void TabWidget::on_pb_ajout_clicked()
{
    int id=ui->le_id->text().toInt();

        int quantite=ui->le_quantite->text().toInt();
        QString nom=ui->le_nom->text();
        QString categorie=ui->le_cat->text();
        float prix=ui->le_prix->text().toFloat();
    stock S(id,quantite,nom,categorie,prix);
     QMessageBox msgBox;

     bool test= S.ajouter();
     if(id!=0)
                {
                      if(test)
                   {
                       ui->tablemateriel->setModel(S.afficher());
                       QMessageBox::information(nullptr, QObject::tr("Ajouter"),
                                   QObject::tr(" ajout avec succes.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
          if (quantite<5)
           { mSystemTrayIcon->showMessage(tr("alerte"),tr("la quantite du produit est faible"));}

     }}
       else

          QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                                  QObject::tr("Remplissez tous les champs.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void TabWidget::on_pb_modifier_clicked()
{
    int id=ui->le_id_3->text().toInt();
       int quantite=ui->le_quantite_3->text().toInt();
       float prix=ui->le_prix_3->text().toFloat();
       QString nom=ui->le_nom_3->text();
       QString categorie=ui->le_cat_3->text();
       bool   test=S.modifier(id,quantite,nom,categorie,prix);
       if(id!=0)
                 {

                 if(test)
                 {

                 QMessageBox::information(nullptr, QObject::tr("modifier un stock"),
                                   QObject::tr("stock modifié.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
                 if (quantite<5)
                                   { mSystemTrayIcon->showMessage(tr("alerte"),tr("la quantite du produit est faible"));}
                 }
                   else{
                       QMessageBox::critical(nullptr, QObject::tr("modifier un stock "),
                                   QObject::tr("Erreur !.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
                 }
                 }
                 else {
                     QMessageBox::critical(nullptr, QObject::tr("id n'existe pas "),
                                 QObject::tr("veuillez saisir l'id du produit .\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
                }
}

void TabWidget::on_pushButton_8_clicked()
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

void TabWidget::on_pushButton_5_clicked()
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

void TabWidget::on_pushButton_4_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from stock order by id_stock desc ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr(" id_stock"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("categorie"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("nom_materiel"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr(" prix_materiel"));

        ui->tablemateriel->setModel(model);
}

void TabWidget::on_pushButton_clicked()
{

    QSqlQueryModel* model=new QSqlQueryModel();
       model->setQuery("select* from stock order by nom_materiel desc ");
       model->setHeaderData(0,Qt::Horizontal,QObject::tr(" id_stock"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("categorie"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("nom_materiel"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
         model->setHeaderData(4,Qt::Horizontal,QObject::tr(" prix_materiel"));

        ui->tablemateriel->setModel(model);

}


void TabWidget::on_button_verifier_clicked()
{
    stock s;

           if(s.verif())
           {
               A.write_to_arduino("1"); //envoyer 1 à arduino

           }
}

/*void TabWidget::on_pushButton_6_clicked()
{

}*/

void TabWidget::on_pushButton_2_clicked()
{

    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from stock order by prix_materiel desc ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr(" id_stock"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("categorie"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("nom_materiel"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr(" prix_materiel"));

     ui->tablemateriel->setModel(model);
}




  // ////////////////////////////STAFF
void TabWidget::on_pb_ajouter_clicked()
{
    int id_staff=ui->le_id_2->text().toInt();
    QString nom=ui->le_nom_2->text();
    QString prenom=ui->le_prenom->text();
    QString email=ui->le_email->text();
    int nb_heurs=ui->le_nbh->text().toInt();
    int  salaire=ui->le_salaire->text().toInt();
    QString fonction=ui->le_fonction->text();
    QString date_emp=ui->les_jours->text();
    QString uid_c=ui->uid_c->text();


    Staff St(id_staff,nom,prenom,email,nb_heurs,salaire,fonction,date_emp,uid_c);
    bool test=St.ajouter();
    if (test )
    {QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr("ajout effectuer. \n"
                            "click to exit"),QMessageBox::Cancel);
        ui->tabstaff->setModel(St.afficher());

    }
    else
        QMessageBox ::critical(nullptr,QObject::tr("not ok"),
                               QObject::tr ("ajout non effectuer. \n"
                                            "click to exit"),QMessageBox::Cancel);

}

void TabWidget::on_pb_supprimer_2_clicked()
{
    QSqlQuery query2;
           int id= ui->comboBox_id->currentText().toInt();

           /*query2.prepare("select ID_STAFF from SATFF where ID_STAFF=:id");
           query2.bindValue(":id",id);

           query2.exec();
           query2.next();
           int name=query2.value(0).toInt();
           cout<<name;

           if(name==id)
           {
               QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("id existe\n"
                                   "click cancel to exit."),QMessageBox::Cancel);
               }*/

           bool test=St.supprimer(id);

           if(test )
           {
               ui->tabstaff->setModel(St.afficher());
               ui->comboBox_id->setModel(St.afficherValeur("ID_STAFF"));

               QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("suppression effectuée\n"
                                   "click cancel to exit."),QMessageBox::Cancel);
          }
           else{
               QMessageBox::information(nullptr, QObject::tr("not ok"),
                       QObject::tr("suppression non effectuée\n"
                                   "click cancel to exit."),QMessageBox::Cancel);}

           /*else
               QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("id n'existe pas\n"
                                   "click cancel to exit."),QMessageBox::Cancel);*/


}

void TabWidget::on_pb_modifier_2_clicked()
{
    QString nom= ui->le_nommodif->text();
            QString prenom= ui->le_prenommodif->text();
            int nb_heurs = ui->le_nbhmodif->text().toInt();
            int id_staff = ui->le_idmodif->text().toInt();
            int salaire = ui->le_salairemodif->text().toInt();
            QString email= ui->le_emailmodif->text();
            QString fonction= ui->le_fonctionmodif->text();
            QString date_emp=ui->date_emp_modif->text();
            QString uid_c=ui->uid_c_modif->text();


          Staff S2(id_staff,nom,prenom,email,nb_heurs,salaire,fonction,date_emp,uid_c);
          bool test=S2.modifier(id_staff);
          if(test)
         {

              ui->tabstaff->setModel(St.afficher());
         QMessageBox::information(nullptr, QObject::tr("modifier un staff"),
                           QObject::tr("staff modifié.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

         }
           else
               QMessageBox::critical(nullptr, QObject::tr("modifier un staff"),
                           QObject::tr("Erreur !.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
}

void TabWidget::on_tri_3_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from STAFF order by fonction ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id-staff"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("nb_heurs"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("fonction"));


     model->setHeaderData(6, Qt::Horizontal, QObject::tr(""));

     ui->tabstaff->setModel(model);
}

void TabWidget::on_tri_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
       model->setQuery("select* from STAFF order by salaire ");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("id-staff"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("prenom"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("email"));
       model->setHeaderData(7, Qt::Horizontal, QObject::tr("nb_heurs"));
       model->setHeaderData(8, Qt::Horizontal, QObject::tr("salaire"));
       model->setHeaderData(9, Qt::Horizontal, QObject::tr("fonction"));


        ui->tabstaff->setModel(model);
}

void TabWidget::on_tri_2_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from STAFF order by nb_heurs ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id-staff"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("nb_heurs"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("fonction"));


     ui->tabstaff->setModel(model);
}

void TabWidget::on_PDF_clicked()
{
    QSqlDatabase DRY_CLEANER;
                    QTableView tablemateriel;
                    QSqlQueryModel * Modal=new  QSqlQueryModel();

                    QSqlQuery qry;
                     qry.prepare("SELECT * FROM STAFF ");
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

void TabWidget::on_calendarWidget_clicked(const QDate &date)
{
    days=days+date.toString()+"|";
        ui->les_jours->setText(days);
}


void TabWidget::on_geta1_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), "", tr("All Files (*.*)"));

        ui->attach1_3->setText(fileName);
}

void TabWidget::on_geta2_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), "", tr("All Files (*.*)"));

        ui->attach2_3->setText(fileName);
}

void TabWidget::on_geta3_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), "", tr("All Files (*.*)"));

        ui->attach3_3->setText(fileName);
}

void TabWidget::on_geta4_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open File"), "", tr("All Files (*.*)"));

     ui->attach4_3->setText(fileName);
}

void TabWidget::on_envoyer_mail_4_clicked()
{
    if(ui->lineEdit_14->text() != NULL && ui->lineEdit_17->text() !=NULL){
            if(ui->lineEdit_18->text().toInt() != 0 && ui->lineEdit_19->text()!= NULL){
                if(ui->lineEdit_20->text() != NULL && ui->le_toAdd_5->text() != NULL){

                    SmtpClient smtp(ui->lineEdit_19->text(), ui->lineEdit_18->text().toInt(), SmtpClient::SslConnection);

                    smtp.setUser(ui->lineEdit_14->text());
                    smtp.setPassword(ui->lineEdit_17->text());

                    MimeMessage message;

                    EmailAddress sender(ui->lineEdit_20->text(), ui->lineEdit_21->text());
                    message.setSender(&sender);

                    //create list of to
                    QStringList to = getRecipientsAddress(ui->le_toAdd_5->text());
                    QStringList cc = getRecipientsAddress(ui->le_ccAdd_5->text());
                    QStringList bcc = getRecipientsAddress(ui->le_bccAdd_5->text());

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
                    message.setSubject(ui->objet_3->text());

                    MimeText text;
                    text.setText(ui->le_emailContent_3->document()->toPlainText());
                    message.addPart(&text);

                    MimeAttachment attachment1(new QFile(ui->attach1_3->text()));
                    MimeAttachment attachment2(new QFile(ui->attach2_3->text()));
                    MimeAttachment attachment3(new QFile(ui->attach3_3->text()));
                    MimeAttachment attachment4(new QFile(ui->attach4_3->text()));

                    //attachments
                    if(ui->attach1_3->text() != NULL){
                       message.addPart(&attachment1);
                    }

                    if(ui->attach2_3->text() != NULL){
                        message.addPart(&attachment2);
                    }

                    if(ui->attach3_3->text() != NULL){
                        message.addPart(&attachment3);
                    }

                    if(ui->attach4_3->text() != NULL){
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






    //   ///////////////ARTICLES
void TabWidget::on_ajouter_article_clicked()
{
    int id=ui->idajout_article->text().toInt();
              QString type=ui->typeajout_article->text();
              QString nom=ui->nomajout_article->text();
              QString matiere=ui->matiereajout_article->text();
              QString couleur=ui->couleurajout_article->text();

              article tmparticle(id,type,nom,matiere,couleur);

              bool test=tmparticle.ajouter();
              if(test){
                  ui->affichage_article->setModel(tmparticle.afficher());
                  QMessageBox::information(nullptr,"Ajout article","article ajouté avec succés");

              }
              else{
                      QMessageBox::warning(nullptr,"Error","article non ajouté");}

}

void TabWidget::on_supprimer_article_clicked()
{
    int id =ui->id_supprimer_article->text().toInt();
        bool test=tmpartcile.supprimer(id);
        if(test)
           {
            ui->affichage_article->setModel(tmpartcile.afficher());
            ui->tablemateriel->clearSelection();
        QMessageBox::information(nullptr,"suppression article","article supprimé avec succés");}

        else{
                QMessageBox::warning(nullptr,"Error","article non supprimé");}

}

void TabWidget::on_modifier_article_clicked()
{
    int id=ui->id_afficher_article->text().toInt();
           QString type=ui->type_afficher_article->text();
           QString nom=ui->nom_afficher_article->text();
           QString matiere=ui->matiere_afficher_article->text();
           QString couleur=ui->couleur_afficher_article->text();
           article tmparticle(id,type,nom,matiere,couleur);
            bool test=tmparticle.modifier(id);
            if(test)
          {

                ui->affichage_article->setModel(tmparticle.afficher());//refresh
          QMessageBox::information(nullptr, QObject::tr("modifier un article"),
                            QObject::tr("article modifié.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

          }
            else{
                QMessageBox::critical(nullptr, QObject::tr("modifier un article"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

          }
}

void TabWidget::on_tri_type_article_clicked()
{
  ui->affichage_article->setModel( tmpartcile.tri_type());
}

void TabWidget::on_tri_id_article_clicked()
{
ui->affichage_article->setModel( tmpartcile.tri_id());
}

void TabWidget::on_recherche_article_clicked()
{
 ui->affichage_article->setModel( tmpartcile.recherche_id(ui->id_recherche_article->text()));
}

void TabWidget::on_pushButton_3_clicked()
{
    if(ui->affichage_article->currentIndex().row()==-1)
        {
             QMessageBox::information(nullptr, QObject::tr("QrCode"),
                                           QObject::tr("Veuillez Choisir un(e) article(e) du Tableau.\n"
                                                       "Click Ok to exit."), QMessageBox::Ok);
        }

              else
              {
                   int id=ui->affichage_article->model()->data(ui->affichage_article->model()->index(ui->affichage_article->currentIndex().row(),0)).toInt();
                   const QrCode qr = QrCode::encodeText(std::to_string(id).c_str(), QrCode::Ecc::LOW);
                   std::ofstream myfile;
                   myfile.open ("qrcode.svg") ;
                   //myfile << qr.toSvgString(1);
                   myfile.close();
                   QSvgRenderer svgRenderer(QString("qrcode.svg"));
                   QPixmap pix( QSize(90, 90) );
                   QPainter pixPainter( &pix );
                   svgRenderer.render( &pixPainter );
                   ui->label_12->setPixmap(pix);
              }
}

/*void TabWidget::on_Start_clicked()
{

}*/
