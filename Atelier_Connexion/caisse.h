#ifndef CAISSE_H
#define CAISSE_H

#include <QDialog>
#include "dombase.h"
#include "defs.h"
#include "iostream"
#include "QtGui"

namespace Ui {
class Caisse;
}

class Caisse : public QDialog
{
    Q_OBJECT

public:
    explicit Caisse(QWidget *parent = 0);
    ~Caisse();

    void verifAjout();
    void setCaisse();
    void cleanControlFiche();

    void setAjout(bool ajout){
            this->ajout=ajout;
        }
        bool getAjout(){
            return this->ajout;
        }


        void setIDtoDisplay(int IDtoDisplay){
            this->IDtoDisplay=IDtoDisplay;
        }
        int getIDtoDisplay(){
            return this->IDtoDisplay;
        }


        bool VerifDate();
        bool VerifMontant();
        bool VerifType();




private slots:
        void on_pushButton_sauvegarderCaisse_clicked();

        void on_pushButton_supprimerCaisse_clicked();

        void on_pushButton_bloquedCaisse_clicked();

private:

        QPixmap PixFalseIcon;
        QPixmap PixTrueIcon;
           int IDtoDisplay;
           bool Blocked;
           bool ajout;
           DomCaisse domcaisse;
           Ui::Caisse *ui;

};



#endif // CAISSE_H
