#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <materiel.h>
#include<QSystemTrayIcon>


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


private:
    Ui::MainWindow *ui;
    stock S;
     QSystemTrayIcon *mSystemTrayIcon;
};
#endif // MAINWINDOW_H
