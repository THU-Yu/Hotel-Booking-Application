#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H

#include "hotalorder.h"
#include <QDialog>
#include <QGridLayout>

class QPushButton;
class QLabel;

class OrderDetail:public QDialog
{
    Q_OBJECT

public:
    OrderDetail(HotalOrder *ptr,QWidget *parent=0);
    ~OrderDetail(){}
private:
    QLabel *info;
    QLabel *ordernumber1;
    QLabel *useraccount1;
    QLabel *hotalaccount1;
    QLabel *hotalname1;
    QLabel *totalmoney1;
    QLabel *roomtype1;
    QLabel *startdate1;
    QLabel *finaldate1;
    QLabel *successful1;
    QLabel *ordernumber2;
    QLabel *useraccount2;
    QLabel *hotalaccount2;
    QLabel *hotalname2;
    QLabel *totalmoney2;
    QLabel *roomtype2;
    QLabel *startdate2;
    QLabel *finaldate2;
    QLabel *successful2;
    QPushButton *OkButton;
    QGridLayout *mainlayout;
};

#endif // ORDERDETAIL_H
