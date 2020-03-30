#ifndef SHENHEORDER_H
#define SHENHEORDER_H

#include <QMainWindow>
#include "platformuser.h"
#include "hotal.h"
#include "hotalorder.h"
#include "orderdetail.h"
#include "message.h"

class QTableWidget;
class QTableWidgetItem;
class QPushButton;

class ShenHeOrder:public QMainWindow
{
    Q_OBJECT

public:
    ShenHeOrder(Hotal *hotalhead,HotalOrder *orderhead, Message *messagehead, Room *roomhead,PlatformUser *mainaccount3, QWidget *parent=0);
    ~ShenHeOrder(){}
private slots:
    void ButtonClicked(QTableWidgetItem *item);
private:
    QLabel *info;
    QTableWidget *MainTable;
    Hotal *Hotalhead;
    HotalOrder *Orderhead;
    Message *Messagehead;
    OrderDetail *orderdetail;
    QPushButton *BackButton;
    PlatformUser *MainAccount3;
    Room *Roomhead;
};
#endif // SHENHEORDER_H
