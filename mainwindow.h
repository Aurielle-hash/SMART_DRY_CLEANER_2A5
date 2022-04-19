#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <materiel.h>
#include<QSystemTrayIcon>
#include "arduino.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;
    class  QSystemTrayIcon;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     QSystemTrayIcon *Get_notif(){return mSystemTrayIcon;};

private slots:


    void on_pb_supprimer_clicked();

    void on_pb_ajout_clicked();

    void on_pb_modifier_clicked();

    void on_tri_clicked();



    void on_groupBox_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();


    void on_start_c_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pb_server_clicked();

    void on_button_verifier_clicked();

private:
    Ui::MainWindow *ui;
    stock S;
     QSystemTrayIcon *mSystemTrayIcon;

     QByteArray data; // variable contenant les données reçues

     Arduino A; // objet temporaire

};
#endif // MAINWINDOW_H
