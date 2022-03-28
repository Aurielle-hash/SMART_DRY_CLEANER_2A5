#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "staff.h"
#include "agenda.h"
#include <QMainWindow>
#include <QPrinter>

namespace Ui {
class MainWindow;
} QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void MainWindow::on_tri_3_clicked();

    void MainWindow::on_tri_clicked();

    void MainWindow::on_tri_2_clicked();

    void on_PDF_clicked();
private:
    Ui::MainWindow *ui;
     Staff S;
};

#endif // MAINWINDOW_H
