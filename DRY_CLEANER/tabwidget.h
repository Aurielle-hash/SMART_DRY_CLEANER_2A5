#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QTableWidgetItem>
#include "defs.h"
#include "dombase.h"
#include "iostream"
#include "QtGui"
#include "widget.h"





namespace Ui {
class TabWidget;
}

class TabWidget : public QTabWidget
{
    Q_OBJECT

   public:

       explicit TabWidget(QWidget *parent = 0);
       ~TabWidget();

       void prepareTabWidget();

       //PREPARER L'INTERFACE DE LA CAISSE
       void prepareTabCaisse();
       void prepareBilan();
       void prepareCaisse();
       void prepareStats();
       void prepareHistory();

       void prepareTabStock();
       void prepareTabemploye();
       void prepareTabClient();
       void prepareTabArticle();

       //BILAN CAISSE

       QVector <QString>getBilanFromFile();
       void setDateDebutD(QDate datedebut){this->datedebut=datedebut;}
       QDate getDateDebutD(){return this->datedebut;}
       void setDateFinD(QDate datefin){this->datefin=datefin;}
       QDate getDateFinD(){return this->datefin;}
          void prepareTableViewBilan();

          //ENREGISTREMENT CAISSE

          void verifAjout();
          void setCaisse();
          void cleanControlFiche();

          void setAjout(bool ajout){this->ajout=ajout;}
              bool getAjout(){return this->ajout;}
              void setIDtoDisplay(int IDtoDisplay){this->IDtoDisplay=IDtoDisplay;}
              int getIDtoDisplay(){return this->IDtoDisplay;}
              bool VerifDate();
              bool VerifMontant();
              bool VerifType();

              //STATISTIQUES CAISSE

              void setDateDebut(QDate datedebut){this->datedebut = datedebut;}
              QDate getDateDebut(){return this->datedebut;}
              void setDateFin(QDate datefin){this->datefin = datefin;}
              QDate getDateFin(){return this->datefin;}
              void makePlot();

              //HISTORIQUE CAISSE
              QVector <QString>getHistoriqueFromFile();
               void prepareTableViewHistorique();

               //FIN PREPARATION DE LA CAISSE

               //STOCK
               // QSystemTrayIcon *Get_notif(){return mSystemTrayIcon;};



private slots:

               //CAISSE
       void sectionClicked(int);

       void on_lineEdit_rechercheCaisse_cursorPositionChanged();

       void on_tableView_Caisse_doubleClicked();

       void on_pushButton_actualiserCaisse_clicked();

       void on_pushButton_newCaisse_clicked();

       void on_pushButton_bilanCaisse_clicked();

       void on_pushButton_historiqueCaisse_clicked();

       void on_tableView_Caisse_clicked();

       void on_pushButton_validerBilan_clicked();

       void on_pushButton_retour_a_Caisse_b_clicked();

       void on_pushButton_statistique_clicked();

       void on_pushButton_retour_a_Caisse_h_clicked();

       void on_pushButton_retourBilan_clicked();

       void on_pushButton_sauvegarderCaisse_clicked();

       void on_pushButton_supprimerCaisse_clicked();

       void on_pushButton_bloquedCaisse_clicked();

       void on_pushButton_retour_caisse_E_clicked();

       //FIN CAISSE

       //DEBUT CLIENT
       void on_pushButton_Ajouter_clicked();

       void on_pushButton_Modifier_clicked();

       void on_pushButton_Supprimer_clicked();

       void on_pushButton_refresh_clicked();

       void on_checkBoxNM_stateChanged(int arg1);

       void on_checkBoxND_stateChanged(int arg1);

       void on_checkBoxPM_stateChanged(int arg1);

       void on_checkBoxPD_stateChanged(int arg1);

       void on_pushButtonrechercher_clicked();

       void on_pushButton_pdf_clicked();

       void on_pushButton_excel_clicked();

       void on_pushButtoncode_clicked();

       void on_geta1_clicked();

       void on_geta2_clicked();

       void on_geta3_clicked();

       void on_geta4_clicked();

       void on_envoyer_mail_3_clicked();

       QStringList getRecipientsAddress(QString str);
       //FIN CLIENT


       //DEBUT STOCK
       void on_pb_supprimer_clicked();

       void on_pb_ajout_clicked();

       void on_pb_modifier_clicked();

       void on_pushButton_8_clicked();

       void on_pushButton_5_clicked();

       void on_pushButton_4_clicked();

       void on_pushButton_clicked();

       void on_button_verifier_clicked();

       void on_pushButton_2_clicked();
       //void on_pushButton_6_clicked();
       //FIN STOCK


       //DEBUT STAFF
       void on_pb_ajouter_clicked();

       void on_pb_supprimer_2_clicked();

       void on_pb_modifier_2_clicked();

       void on_tri_3_clicked();

       void on_tri_clicked();

       void on_tri_2_clicked();

       void on_PDF_clicked();

       void on_calendarWidget_clicked(const QDate &date);

       void on_geta1_2_clicked();

       void on_geta2_2_clicked();

       void on_geta3_2_clicked();

       void on_geta4_2_clicked();

       void on_envoyer_mail_4_clicked();
       //FIN STAFF

       //DEBUT ARTICLE
       void on_ajouter_article_clicked();

       void on_supprimer_article_clicked();

       void on_modifier_article_clicked();

       void on_tri_type_article_clicked();

       void on_tri_id_article_clicked();

       void on_recherche_article_clicked();

       void on_pushButton_3_clicked();
       //FIN ARTICLE

       //void on_Start_clicked();

private:

       //CAISSE
       QPixmap PixFalseIcon;
       QPixmap PixTrueIcon;
          int IDtoDisplay;
          bool Blocked;
          bool ajout;
    QDate datedebut, datefin;
    QItemSelectionModel* SelectionModel;
    DomCaisse domcaisse;

    //CLIENT
    client C;

     //STOCK
    stock S;
        QSystemTrayIcon *mSystemTrayIcon;
        QByteArray data; // variable contenant les données reçues
        Arduino A;

        //STAFF
         void readdisplaytable();
         Staff St;

         //ARTICLE
         QTimer *timer;
         article tmpartcile;

    Ui::TabWidget *ui;
    QHeaderView* m_pHeaderView;

};

#endif // TABWIDGET_H
