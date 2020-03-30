#ifndef HOTALMANAGE_H
#define HOTALMANAGE_H

#include "normaluser.h"
#include "hotaluser.h"
#include "platformuser.h"
#include "hotal.h"
#include "hotaldetail.h"
#include "message.h"
#include "room.h"
#include "hotalorder.h"
#include "sendmessagedialog.h"
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>

class QTableWidget;
class QTableWidgetItem;
class QPushButton;

class HotalManage:public QWidget
{
    Q_OBJECT

public:
    HotalManage(Hotal *hotalhead,Message *messagehead,Room *roomhead,HotalOrder *orderhead,NormalUser *MainAccount1,HotalUser *MainAccount2,PlatformUser *MainAccount3,QWidget *parent=0)
        :Hotalhead(hotalhead),Messagehead(messagehead),Roomhead(roomhead),Orderhead(orderhead),MainAccount1(MainAccount1),MainAccount2(MainAccount2),MainAccount3(MainAccount3),Start(nullptr),Final(nullptr),Area("\0"),QWidget(parent){}
    void changeHotalManage(NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainaccount3, QDate *start=nullptr, QDate *final=nullptr, QString area='\0');
    void changeMainTable(NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainaccount3, QDate *start=nullptr, QDate *final=nullptr, QString area='\0');
    void Reset(){likebox->setCurrentIndex(0);}
    ~HotalManage(){}
signals:
    void back();
private slots:
    void ButtonClicked(QTableWidgetItem *item);
    void Back();
    void ChangeLike(int);
    void createhotal();
private:
    QLabel *empty;
    QTableWidget *MainTable;
    Hotal *Hotalhead;
    Message *Messagehead;
    Room *Roomhead;
    HotalOrder *Orderhead;
    NormalUser *MainAccount1;
    HotalUser *MainAccount2;
    PlatformUser *MainAccount3;
    HotalDetail *hotaldetail;
    QPushButton *CreatButton;
    QPushButton *BackButton;
    QGridLayout *gridlayout;
    QHBoxLayout *hboxlayout;
    QVBoxLayout *mainlayout;
    QComboBox *likebox;
    QDate *Start;
    QDate *Final;
    QString Area;
    int row;
};

#endif // HOTALMANAGE_H
