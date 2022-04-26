#ifndef CHATCONNECTIONDIALOG_H
#define CHATCONNECTIONDIALOG_H
#include "defs.h"
#include <QDialog>

namespace Ui {
class ChatConnectionDialog;
}
namespace DuarteCorporation
{
class ChatConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatConnectionDialog(QWidget *parent = nullptr);
    ~ChatConnectionDialog();
    QString hostname() const ;
    quint16 port() const;
private slots:
    void on_ok_clicked();
    
    void on_cancel_clicked();
    
private:
    Ui::ChatConnectionDialog *ui;
    QString mHostname;
    quint16 mPort;
};

inline QString ChatConnectionDialog::hostname() const
{
    return mHostname;
}

inline quint16 ChatConnectionDialog::port() const
{
    return mPort;
}
}
#endif // CHATCONNECTIONDIALOG_H
