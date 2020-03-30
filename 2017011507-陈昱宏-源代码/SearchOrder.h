#ifndef SEARCHORDER_H
#define SEARCHORDER_H

#include "normaluser.h"
#include "hotaluser.h"
#include "platformuser.h"
#include "hotalorder.h"
#include "orderdetail.h"
#include "PinJiaMessage.h"
#include "hotal.h"
#include <QWidget>

class QTableWidget;
class QTableWidgetItem;

class SearchOrder:public QWidget
{
    Q_OBJECT

public:
    SearchOrder(Hotal *hotalhead,Message *Messagehead, PinJiaMessage *pinjiahead,Room *roomhead, HotalOrder *Orderhead,NormalUser *MainAccount1,HotalUser *MainAccount2,PlatformUser *MainAccount3,QWidget *parent=0)
        :Hotalhead(hotalhead),Messagehead(Messagehead),PinJiahead(pinjiahead),Roomhead(roomhead),Orderhead(Orderhead),MainAccount1(MainAccount1),MainAccount2(MainAccount2),MainAccount3(MainAccount3),QWidget(parent){}
    void changeSearchOrder(NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainccount3);
    void changeTable(NormalUser *Mainaccount1,HotalUser *Mainaccount2,PlatformUser *Mainaccount3);
    ~SearchOrder(){}
signals:
    void back();
private slots:
    void ButtonClicked(QTableWidgetItem *item);
    void CheckCancelOrder();
    void Back();
private:
    QTableWidget *MainTable;
    Hotal *Hotalhead;
    HotalOrder *Orderhead;
    Message *Messagehead;
    Room *Roomhead;
    PinJiaMessage *PinJiahead;
    NormalUser *MainAccount1;
    HotalUser *MainAccount2;
    PlatformUser *MainAccount3;
    OrderDetail *orderdetail;
    QPushButton *BackButton;
    QPushButton *CancelOrderButton;
};

#endif // SEARCHORDER_H
