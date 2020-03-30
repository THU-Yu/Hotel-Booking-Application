#ifndef RECEIVEMESSAGE_H
#define RECEIVEMESSAGE_H

#include "normaluser.h"
#include "hotaluser.h"
#include "platformuser.h"
#include "message.h"
#include "messagedetail.h"
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class QTableWidget;
class QTableWidgetItem;
class QPushButton;

class ReceiveMessage:public QWidget
{
    Q_OBJECT

public:
    ReceiveMessage(Message *messagehead,NormalUser *MainAccount1,HotalUser *MainAccount2,PlatformUser *MainAccount3,QWidget *parent=0)
        :Messagehead(messagehead),MainAccount1(MainAccount1),MainAccount2(MainAccount2),MainAccount3(MainAccount3),QWidget(parent){}
    void changeReceiveMessage(NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainaccount3);
    void changeMainTable(NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainaccount3);
    ~ReceiveMessage(){}
signals:
    void back();
private slots:
    void ButtonClicked(QTableWidgetItem *item);
    void Back();
private:
    QTableWidget *MainTable;
    Message *Messagehead;
    NormalUser *MainAccount1;
    HotalUser *MainAccount2;
    PlatformUser *MainAccount3;
    MessageDetail *messagedetail;
    QPushButton *BackButton;
    QGridLayout *gridlayout;
    QHBoxLayout *hboxlayout;
    QVBoxLayout *mainlayout;
};

#endif // RECEIVEMESSAGE_H
