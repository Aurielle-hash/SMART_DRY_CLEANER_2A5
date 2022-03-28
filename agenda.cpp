#include "agenda.h"
#include <QLineEdit>
#include <QTableWidget>


 QTableWidget* agenda::emplois()
 {
emplois = new QTableWidget(7, 2, this);
 }
void agenda::setCellWidget(int, int, QTableWidget)
 { int row ; int column;
     setCellWidget(row, column, new QLineEdit);
 }
