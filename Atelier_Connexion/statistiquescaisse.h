#ifndef STATISTIQUESCAISSE_H
#define STATISTIQUESCAISSE_H


#include <QDialog>
#include "dombase.h"
#include "defs.h"
#include "iostream"
#include "QtGui"

namespace Ui {
class statistiquescaisse;
}

class statistiquescaisse : public QDialog
{
    Q_OBJECT

public:
    explicit statistiquescaisse(QWidget *parent = 0);
    ~statistiquescaisse();

    void setDateDebut(QDate datedebut){
        this->datedebut = datedebut;
    }
    QDate getDateDebut(){
        return this->datedebut;
    }

    void setDateFin(QDate datefin){
        this->datefin = datefin;
    }
    QDate getDateFin(){
        return this->datefin;
    }

     void makePlot();

private slots:

    void on_pushButton_capturerCustomPlot_clicked();

private:
    QDate datedebut, datefin;
    DomCaisse domCaisse;
    Ui::statistiquescaisse *ui;
};


#endif // STATISTIQUESCAISSE_H
