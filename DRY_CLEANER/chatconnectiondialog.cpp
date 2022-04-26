#include "chatconnectiondialog.h"
#include "ui_chatconnectiondialog.h"
namespace DuarteCorporation {

ChatConnectionDialog::ChatConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatConnectionDialog)
{
    ui->setupUi(this);
}

ChatConnectionDialog::~ChatConnectionDialog()
{
    delete ui;
}

void ChatConnectionDialog::on_ok_clicked()
{
   mHostname = ui->hostname->text();
   mPort = ui->port->value();
   accept();
}

void ChatConnectionDialog::on_cancel_clicked()
{
    reject();
}
}
