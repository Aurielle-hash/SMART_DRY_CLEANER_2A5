#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include "defs.h"
#include "dombase.h"
#include "bilancaisse.h"
#include "historiquecaisse.h"
#include "caisse.h"
#include "iostream"
#include "QtGui"





namespace Ui {
class TabWidget;
}

class TabWidget : public QTabWidget
{
    Q_OBJECT

   public:

       explicit TabWidget(QWidget *parent = 0);
       ~TabWidget();

       void prepareTabCaisse();
       void prepareTabWidget();

      /* void prepareTabStock();
       void prepareTabArticle();
       void prepareTabemploye();
       void prepareTabClient();*/



private slots:
       void sectionClicked(int);

       void on_lineEdit_rechercheCaisse_cursorPositionChanged();

       void on_tableView_Caisse_doubleClicked();

       void on_pushButton_actualiserCaisse_clicked();

       void on_pushButton_newCaisse_clicked();

       void on_pushButton_bilanCaisse_clicked();

       void on_pushButton_historiqueCaisse_clicked();

       void on_tableView_Caisse_clicked();

private:

    QItemSelectionModel* SelectionModel;
    DomCaisse domcaisse;
    Ui::TabWidget *ui;
    QHeaderView* m_pHeaderView;

};

#endif // TABWIDGET_H
