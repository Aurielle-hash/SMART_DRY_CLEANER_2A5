#include "statistiquescaisse.h"
#include "ui_statistiquescaisse.h"

statistiquescaisse::statistiquescaisse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistiquescaisse)
{
    ui->setupUi(this);
    this->setWindowTitle("Statistiques caisse");
    //this->datedebut=QDate::fromString("03/03/1998","dd/MM/yyyy");
    //this->datefin=QDate::fromString("05/06/2000","dd/MM/yyyy");
    statistiquescaisse::makePlot();

}

statistiquescaisse::~statistiquescaisse()
{
    delete ui;
}


void statistiquescaisse::makePlot()
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
                    QVector<QString> labels=domCaisse.getListDate(getDateDebut(),getDateFin());
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

                             depense_Data << domCaisse.getMontantTotalFraisParDate(date,"depense");
                             versementData << domCaisse.getMontantTotalFraisParDate(date,"versement");

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




void statistiquescaisse::on_pushButton_capturerCustomPlot_clicked()
{
    QPixmap pixmap(ui->customPlot->size());
    ui->customPlot->render(&pixmap, QPoint(), QRegion());
    pixmap.save("captureStat.png");
}
