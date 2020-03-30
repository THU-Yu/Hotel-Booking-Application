#ifndef CANCELORDER_H
#define CANCELORDER_H

#include <QMainWindow>
#include "hotalorder.h"
#include "orderdetail.h"
#include "hotaluser.h"
#include "hotal.h"
#include "message.h"

class QLabel;
class QTableWidget;
class QTableWidgetItem;
class QPushButton;

class CancelOrder:public QMainWindow
{
    Q_OBJECT

public:
    CancelOrder(Hotal *hotalhead, HotalOrder *orderhead, Message *messagehead, Room *roomhead, HotalUser *Mainaccount, QWidget *parent=0);
    ~CancelOrder(){}
private slots:
    void ButtonClicked(QTableWidgetItem *item);
private:
    QLabel *info;
    QTableWidget *MainTable;
    QPushButton *BackButton;
    Hotal *Hotalhead;
    HotalOrder *Orderhead;
    Message *Messagehead;
    HotalUser *MainAccount;
    Room *Roomhead;
};

#endif // CANCELORDER_H
