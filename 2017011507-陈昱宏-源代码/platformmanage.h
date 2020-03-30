#ifndef PLATFORMMANAGE_H
#define PLATFORMMANAGE_H

#include <QWidget>
#include "hotal.h"
#include "hotalorder.h"
#include "platformuser.h"

class QLabel;
class QPushButton;

class PlatformManage:public QWidget
{
    Q_OBJECT

public:
    PlatformManage(Hotal *h, HotalOrder *o,Message *m, Room *r, QWidget *parent=0);
    void changePlatfoemManage();
    void changePlatformUser(PlatformUser *a){MainAccount3 = a;}
    ~PlatformManage();
signals:
    void back();
private slots:
    void Back();
    void checkHotal();
    void checkOrder();
private:
    QLabel *info;
    QLabel *normalUser1;
    QLabel *hotalUser1;
    QLabel *platformUser1;
    QLabel *hotal1;
    QLabel *Order1;
    QLabel *normalUser2;
    QLabel *hotalUser2;
    QLabel *platformUser2;
    QLabel *hotal2;
    QLabel *Order2;
    QPushButton *BackButton;
    QPushButton *CheckOrderButton;
    QPushButton *CheckHotalButton;
    Hotal *hotal;
    HotalOrder *order;
    Message *message;
    Room *room;
    PlatformUser *MainAccount3;
};

#endif // PLATFORMMANAGE_H
