#include "createorder.h"
#include "paymoney.h"
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QtGlobal>
#include <QTime>
#include <QGridLayout>
#include <QSpinBox>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>

CreateOrder::CreateOrder(Hotal *hotalhead, Room *roomhead, Message *messagehead, HotalOrder *orderhead, Hotal *hotal,NormalUser *Mainaccount, QWidget *parent)
    :Hotalhead(hotalhead),Roomhead(roomhead),Messagehead(messagehead),Orderhead(orderhead),thishotal(hotal),MainAccount(Mainaccount),successful(false),QDialog(parent)
{
    info = new QLabel(tr("订单"));
    info->setAlignment(Qt::AlignCenter);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    bool same = false;
    for (int i = 0;i >= 0;i ++)
    {
        Ordernum2 = '\0';
        QString s;
        Ordernum2 = Ordernum2 + s.setNum(double(qrand()%10),'f',0);
        for (int j = 0;j < 12;j ++)
        {
            Ordernum2 = Ordernum2 + s.setNum(double(qrand()%10),'f',0);
        }
        HotalOrder *ptr;
        for (ptr = Orderhead;ptr != nullptr;ptr = ptr->getnext())
        {
            if (Ordernum2 == ptr->getOrderNumber())
            {
                same = true;
                break;
            }
        }
        if (!same)
        {
            break;
        }
        else
        {
            same = false;
        }
    }
    Ordernum1 = new QLabel("订单编号：" + Ordernum2);
    Ordernum1->setAlignment(Qt::AlignLeft);

    HotalName = new QLabel("酒店名称：" + thishotal->getHotalName());
    HotalName->setAlignment(Qt::AlignLeft);

    RoomType1 = new QLabel(tr("房间类型："));
    RoomType1->setAlignment(Qt::AlignLeft);

    RoomType2 = new QComboBox;
    RoomType2->addItem("\0");

    Room *ptr1,*ptr2;
    for (ptr1 = thishotal->getRoomhead();ptr1 != nullptr;ptr1 = ptr1->getnext())
    {
        if (ptr1 == hotal->getRoomhead())
        {
            RoomType2->addItem(ptr1->getType());
            ptr2 = ptr1;
        }
        else
        {
            if (ptr2->getType() != ptr1->getType())
            {
                RoomType2->addItem(ptr1->getType());
                ptr2 = ptr1;
            }
        }
    }

    Start1 = new QLabel(tr("起始时间："));
    Start1->setAlignment(Qt::AlignLeft);

    Start2 = new QDateTimeEdit(QDate::currentDate());
    Start2->setMinimumDate(QDate::currentDate());
    Start2->setMaximumDate(QDate::currentDate().addDays(30));
    Start2->setCalendarPopup(true);
    Start2->setDisplayFormat("yyyy-MM-dd");

    Final1 = new QLabel(tr("结束时间："));
    Final1->setAlignment(Qt::AlignLeft);

    Final2 = new QDateTimeEdit(Start2->date().addDays(1));
    Final2->setMinimumDate(Start2->date().addDays(1));
    Final2->setMaximumDate(QDate::currentDate().addDays(31));
    Final2->setCalendarPopup(true);
    Final2->setDisplayFormat("yyyy-MM-dd");

    money1 = new QLabel(tr("总金额："));
    money1->setAlignment(Qt::AlignLeft);
    money2 = new QLineEdit;
    money2->setText("0.00");
    money2->setReadOnly(true);

    RoomNum1 = new QLabel(tr("订购间数："));
    RoomNum1->setAlignment(Qt::AlignLeft);
    RoomNum2 = new QSpinBox;
    RoomNum2->setRange(0,0);
    RoomNum2->setValue(0);

    CreateButton = new QPushButton(tr("提交"));
    CreateButton->setEnabled(false);
    CancelButton = new QPushButton(tr("取消"));

    connect(money2,SIGNAL(textChanged(QString)),this,SLOT(EnableClick()));
    connect(RoomType2,SIGNAL(currentIndexChanged(QString)),this,SLOT(MoneyChange(QString)));
    connect(Start2,SIGNAL(dateChanged(QDate)),this,SLOT(moneychange()));
    connect(Final2,SIGNAL(dateChanged(QDate)),this,SLOT(moneychange()));
    connect(Start2,SIGNAL(dateChanged(QDate)),this,SLOT(ChangeFinalDay()));
    connect(RoomType2,SIGNAL(currentIndexChanged(QString)),this,SLOT(ChangeSpinBoxRange()));
    connect(Start2,SIGNAL(dateChanged(QDate)),this,SLOT(ChangeSpinBoxRange()));
    connect(Final2,SIGNAL(dateChanged(QDate)),this,SLOT(ChangeSpinBoxRange()));
    connect(RoomNum2,SIGNAL(valueChanged(int)),this,SLOT(moneychange()));
    connect(CreateButton,SIGNAL(clicked()),this,SLOT(Create()));
    connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));

    QGridLayout *mainlayout = new QGridLayout;
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->addWidget(info,0,0,1,5);
    mainlayout->addWidget(Ordernum1,1,0,1,5);
    mainlayout->addWidget(HotalName,2,0,1,5);
    mainlayout->addWidget(RoomType1,3,0,1,2);
    mainlayout->addWidget(RoomType2,3,2,1,3);
    mainlayout->addWidget(RoomNum1,4,0,1,2);
    mainlayout->addWidget(RoomNum2,4,2,1,3);
    mainlayout->addWidget(Start1,5,0,1,2);
    mainlayout->addWidget(Start2,5,2,1,3);
    mainlayout->addWidget(Final1,6,0,1,2);
    mainlayout->addWidget(Final2,6,2,1,3);
    mainlayout->addWidget(money1,7,0,1,2);
    mainlayout->addWidget(money2,7,2,1,3);
    mainlayout->addWidget(CreateButton,8,0,1,2);
    mainlayout->addWidget(CancelButton,8,3,1,2);

    setLayout(mainlayout);
}

bool CreateOrder::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("取消？"),tr("现在退出订单将不会完成，\n确定要退出吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CreateOrder::EnableClick()
{
    if (money2->text() != "0.00")
    {
        CreateButton->setEnabled(true);
    }
    else
    {
        CreateButton->setEnabled(false);;
    }
}

void CreateOrder::MoneyChange(QString r)
{
    if (r == '\0')
    {
        money2->setText("0.00");
        return;
    }
    Room *ptr;
    for (ptr = thishotal->getRoomhead();ptr != nullptr;ptr = ptr->getnext())
    {
        if (ptr->getType() == r)
        {
            double m;
            QString s;
            int day = 0;
            for (QDate date = Start2->date();date < Final2->date();date = date.addDays(1))
            {
                day ++;
            }
            m = ptr->getmoneyPerNight() * day * RoomNum2->value();
            money2->setText(s.setNum(m,'f',2));
            break;
        }
    }
}

void CreateOrder::moneychange()
{
    Room *ptr;
    for (ptr = thishotal->getRoomhead();ptr != nullptr;ptr = ptr->getnext())
    {
        if (ptr->getType() == RoomType2->currentText())
        {
            double m;
            QString s;
            int day = 0;
            for (QDate date = Start2->date();date < Final2->date();date = date.addDays(1))
            {
                day ++;
            }
            m = ptr->getmoneyPerNight() * day * RoomNum2->value();
            money2->setText(s.setNum(m,'f',2));
            break;
        }
    }
}

void CreateOrder::ChangeFinalDay()
{
    if (Start2->date() >= Final2->date())
    {
        Final2->setDate(Start2->date().addDays(1));
    }
}

void CreateOrder::ChangeSpinBoxRange()
{
    Room *ptr;
    int minroomnum = 1000000;
    for (ptr = thishotal->getRoomhead();ptr != nullptr;ptr = ptr->getnext())
    {
        if ((ptr->getType() == RoomType2->currentText()) && (*(ptr->getDate()) < Final2->date()) && (*(ptr->getDate()) >= Start2->date()))
        {
            if (ptr->getRoomNum() < minroomnum)
            {
                minroomnum = ptr->getRoomNum();
            }
        }
    }
    RoomNum2->setMaximum(minroomnum);
    RoomNum2->setValue(0);
}

void CreateOrder::Create()
{
    if (QMessageBox::question(NULL,tr("订购"),tr("下单前请检查资料是否正确！\n确定要订购吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        HotalOrder *neworder = new HotalOrder(MainAccount->getaccount(),thishotal->getHotalName(),thishotal->getHotalManagerAccount(),RoomType2->currentText(),Ordernum2,money2->text().toDouble(),new QDate(Start2->date()),new QDate(Final2->date()));
        HotalOrder *ptr;
        for (ptr = Orderhead;ptr->getnext() != nullptr;ptr = ptr->getnext())
        {}
        ptr->changenext(neworder);
        Room *ptr1;
        for (ptr1 = thishotal->getRoomhead();ptr1 != nullptr;ptr1 = ptr1->getnext())
        {
            if ((ptr1->getType() == RoomType2->currentText()) && (*(ptr1->getDate()) < Final2->date()) && (*(ptr1->getDate()) >= Start2->date()))
            {
                ptr1->ChangeRoomNum(ptr1->getRoomNum() - RoomNum2->value());
            }
        }

        for (ptr1 = Roomhead;ptr1 != nullptr;ptr1 = ptr1->getnext())
        {
            if ((ptr1->getType() == RoomType2->currentText()) && (ptr1->getHotalName() == thishotal->getHotalName()) && (*(ptr1->getDate()) < Final2->date()) && (*(ptr1->getDate()) >= Start2->date()))
            {
                ptr1->ChangeRoomNum(ptr1->getRoomNum() - RoomNum2->value());
            }
        }
        successful = true;
        PayMoney *pay = new PayMoney(neworder,"订单支付",MainAccount,nullptr,nullptr);
        pay->exec();
        close();
    }
}

void CreateOrder::closeEvent(QCloseEvent *event)
{
    if (successful)
    {
        event->accept();
    }
    else if (ContinueToClose())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
