#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Ajouter_clicked();

    void on_pushButton_Supprimer_clicked();

    void on_pushButton_Modifier_clicked();

    void on_pushButton_refresh_clicked();

    void on_checkBoxNM_stateChanged(int arg1);

    void on_checkBoxND_stateChanged(int arg1);

    void on_checkBoxPM_stateChanged(int arg1);

    void on_checkBoxPD_stateChanged(int arg1);

    void on_pushButtonrechercher_clicked();

    void on_pushButton_pdf_clicked();

    void on_pushButton_excel_clicked();

    void on_pushButtoncode_clicked();

    void on_geta1_clicked();

    void on_geta2_clicked();

    void on_geta3_clicked();

    void on_geta4_clicked();

    void on_envoyer_mail_3_clicked();

    QStringList getRecipientsAddress(QString str);

private:
    Ui::MainWindow *ui;
    client C;
};

#endif // MAINWINDOW_H
