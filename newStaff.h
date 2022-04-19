#ifndef NEWSTAFF_H
#define NEWSTAFF_H

#include <QDialog>

namespace Ui {
class newStaff;
}

class newStaff : public QDialog
{
    Q_OBJECT

public:
    explicit newStaff(QWidget *parent = nullptr);
    ~newStaff();

private:
    Ui::newStaff *ui;
};
#endif // NEWSTAFF_H
