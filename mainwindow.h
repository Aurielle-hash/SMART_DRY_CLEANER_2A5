#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <materiel.h>
#include<QSystemTrayIcon>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pb_supprimer_clicked();

    void on_pb_ajout_clicked();

    void on_pb_modifier_clicked();

    void on_tri_clicked();



    void on_groupBox_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_notifier_lina_clicked();

private:
    Ui::MainWindow *ui;
    stock S;
};
#endif // MAINWINDOW_H
