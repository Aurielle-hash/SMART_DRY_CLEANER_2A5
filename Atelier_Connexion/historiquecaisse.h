#ifndef HISTORIQUECAISSE_H
#define HISTORIQUECAISSE_H

#include <QDialog>
#include "dombase.h"
#include "defs.h"
#include "iostream"
#include "QtGui"

namespace Ui {
class historiquecaisse;
}

class historiquecaisse : public QDialog
{
    Q_OBJECT

public:
       explicit historiquecaisse(QWidget *parent = 0);
       ~historiquecaisse();
       QVector <QString>getHistoriqueFromFile();

    void prepareTableViewHistorique();

private:
       DomCaisse domcaisse;
       Ui::historiquecaisse *ui;
};

#endif // HISTORIQUECAISSE_H
