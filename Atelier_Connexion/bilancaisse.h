#ifndef BILANCAISSE_H
#define BILANCAISSE_H

#include <QDialog>
#include "dombase.h"
#include "defs.h"
#include "statistiquescaisse.h"
#include "iostream"
#include "QtGui"

namespace Ui {
class bilancaisse;
}

class bilancaisse : public QDialog
{
    Q_OBJECT

public:
    explicit bilancaisse(QWidget *parent = 0);
    ~bilancaisse();
    QVector <QString>getBilanFromFile();

    void setDateDebut(QDate datedebut){
        this->datedebut=datedebut;
    }
    QDate getDateDebut(){
        return this->datedebut;
    }

    void setDateFin(QDate datefin){
        this->datefin=datefin;
    }
    QDate getDateFin(){
        return this->datefin;
    }


       void prepareTableViewBilan();


private slots:

    void on_pushButton_statistique_clicked();


    void on_pushButton_clicked();

private:
    QDate datedebut, datefin;
    DomCaisse domCaisse;
    Ui::bilancaisse *ui;
};

#endif // BILANCAISSE_H
