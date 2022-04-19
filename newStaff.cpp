#include "newStaff.h"
#include "ui_newStaff.h"

newStaff::newStaff(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newStaff)
{
    ui->setupUi(this);
}

newStaff::~newStaff()
{
    delete ui;
}
