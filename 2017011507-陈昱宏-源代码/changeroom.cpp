#include "changeroom.h"
#include <QLabel>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QDate>
#include <QComboBox>
#include <QGridLayout>
#include <QCloseEvent>
#include <QMessageBox>
#include <QCheckBox>
#include <QRegExp>
#include <QValidator>

ChangeRoom::ChangeRoom(Hotal *hotel, Room *roomhead, QWidget *parent)
    :thishotel(hotel),Roomhead(roomhead),QDialog(parent)
{
    QRegExp regx("^[0-9\.]+$");

    info = new QLabel(tr("修改房间资讯"));
    info->setAlignment(Qt::AlignCenter);

    RoomType1 = new QLabel(tr("房间类型："));
    RoomType1->setAlignment(Qt::AlignLeft);
    RoomType2 = new QComboBox;
    RoomType2->addItem(" ");

    Room *ptr1,*ptr2;
    for (ptr1 = thishotel->getRoomhead();ptr1 != nullptr;ptr1 = ptr1->getnext())
    {
        if (ptr1 == thishotel->getRoomhead())
        {
            RoomType2->addItem(ptr1->getType());
            ptr2 = ptr1;
        }
        else if (ptr2->getType() != ptr1->getType())
        {
            RoomType2->addItem(ptr1->getType());
            ptr2 = ptr1;
        }
    }

    TotalNumInfo = new QLabel(tr("更改房间总数："));
    TotalNumInfo->setAlignment(Qt::AlignLeft);
    TotalNum1 = new QLabel(tr("房间总数："));
    TotalNum1->setAlignment(Qt::AlignLeft);
    TotalNum2 = new QLineEdit;
    QValidator *validator1 = new QRegExpValidator(regx, TotalNum2);
    TotalNum2->setValidator(validator1);
    TotalNum2->setText("0");

    date1 = new QLabel(tr("从何时更改："));
    date1->setAlignment(Qt::AlignLeft);

    date2 = new QDateTimeEdit(QDate::currentDate());
    date2->setMinimumDate(QDate::currentDate());
    date2->setMaximumDate(QDate::currentDate().addDays(31));
    date2->setCalendarPopup(true);
    date2->setDisplayFormat("yyyy-MM-dd");

    RoomNumInfo = new QLabel(tr("更改房间余量："));
    RoomNumInfo->setAlignment(Qt::AlignLeft);
    RoomNum1 = new QLabel(tr("房间余量："));
    RoomNum1->setAlignment(Qt::AlignLeft);
    RoomNum2 = new QLineEdit;
    QValidator *validator2 = new QRegExpValidator(regx, RoomNum2);
    RoomNum2->setValidator(validator2);
    RoomNum2->setText("0");

    Date1 = new QLabel(tr("更改哪天的余量："));
    Date1->setAlignment(Qt::AlignLeft);

    Date2 = new QDateTimeEdit(QDate::currentDate());
    Date2->setMinimumDate(QDate::currentDate());
    Date2->setMaximumDate(QDate::currentDate().addDays(31));
    Date2->setCalendarPopup(true);
    Date2->setDisplayFormat("yyyy-MM-dd");

    MoneyPerNightInfo = new QLabel(tr("更改房间价格："));
    MoneyPerNightInfo->setAlignment(Qt::AlignLeft);
    MoneyPerNight1 = new QLabel(tr("房间价格："));
    MoneyPerNight1->setAlignment(Qt::AlignLeft);
    MoneyPerNight2 = new QLineEdit;
    QValidator *validator3 = new QRegExpValidator(regx, MoneyPerNight2);
    MoneyPerNight2->setValidator(validator3);
    MoneyPerNight2->setText("0");

    Date3 = new QLabel(tr("更改哪天的价格："));
    Date3->setAlignment(Qt::AlignLeft);

    Date4 = new QDateTimeEdit(QDate::currentDate());
    Date4->setMinimumDate(QDate::currentDate());
    Date4->setMaximumDate(QDate::currentDate().addDays(31));
    Date4->setCalendarPopup(true);
    Date4->setDisplayFormat("yyyy-MM-dd");

    totalchange = new QCheckBox;
    totalchange->setText(tr("修改总数量"));
    roomnumchange = new QCheckBox;
    roomnumchange->setText(tr("修改剩余数量"));
    moneychange = new QCheckBox;
    moneychange->setText(tr("修改房间价格"));

    ChangeButton = new QPushButton(tr("更改"));
    ChangeButton->setEnabled(false);
    CancelButton = new QPushButton(tr("取消"));

    connect(RoomType2,SIGNAL(currentIndexChanged(int)),this,SLOT(EnableChange()));
    connect(RoomType2,SIGNAL(currentIndexChanged(int)),this,SLOT(ChangeTotalNum()));
    connect(RoomType2,SIGNAL(currentIndexChanged(int)),this,SLOT(ChangeRoomNum()));
    connect(RoomType2,SIGNAL(currentIndexChanged(int)),this,SLOT(ChangeMoney()));
    connect(date2,SIGNAL(dateChanged(QDate)),this,SLOT(ChangeTotalNum()));
    connect(Date2,SIGNAL(dateChanged(QDate)),this,SLOT(ChangeRoomNum()));
    connect(Date4,SIGNAL(dateChanged(QDate)),this,SLOT(ChangeMoney()));
    connect(totalchange,SIGNAL(stateChanged(int)),this,SLOT(EnableChange()));
    connect(roomnumchange,SIGNAL(stateChanged(int)),this,SLOT(EnableChange()));
    connect(moneychange,SIGNAL(stateChanged(int)),this,SLOT(EnableChange()));
    connect(ChangeButton,SIGNAL(clicked()),this,SLOT(Change()));
    connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));

    QGridLayout *mainlayout = new QGridLayout;
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->addWidget(info,0,0,1,5);
    mainlayout->addWidget(RoomType1,1,0,1,2);
    mainlayout->addWidget(RoomType2,1,2,1,3);
    mainlayout->addWidget(TotalNumInfo,2,0,1,2);
    mainlayout->addWidget(TotalNum1,3,0,1,2);
    mainlayout->addWidget(TotalNum2,3,2,1,3);
    mainlayout->addWidget(date1,4,0,1,2);
    mainlayout->addWidget(date2,4,2,1,3);
    mainlayout->addWidget(RoomNumInfo,5,0,1,2);
    mainlayout->addWidget(RoomNum1,6,0,1,2);
    mainlayout->addWidget(RoomNum2,6,2,1,3);
    mainlayout->addWidget(Date1,7,0,1,2);
    mainlayout->addWidget(Date2,7,2,1,3);
    mainlayout->addWidget(MoneyPerNight1,8,0,1,2);
    mainlayout->addWidget(MoneyPerNight2,8,2,1,3);
    mainlayout->addWidget(Date3,9,0,1,2);
    mainlayout->addWidget(Date4,9,2,1,3);
    mainlayout->addWidget(totalchange,10,0,1,1);
    mainlayout->addWidget(roomnumchange,10,2,1,1);
    mainlayout->addWidget(moneychange,10,4,1,1);
    mainlayout->addWidget(ChangeButton,11,0,1,1);
    mainlayout->addWidget(CancelButton,11,3,1,2);

    setLayout(mainlayout);
}

bool ChangeRoom::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("取消？"),tr("确定要取消修改吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ChangeRoom::ChangeTotalNum()
{
    Room *ptr;
    if (RoomType2->currentText() != " ")
    {
        for (ptr = thishotel->getRoomhead();ptr != nullptr;ptr = ptr->getnext())
        {
            if ((ptr->getType() == RoomType2->currentText()) && (*(ptr->getDate()) == date2->date()))
            {
                QString number;
                TotalNum2->setText(number.setNum(double(ptr->getTotalNum()),'f',0));
                break;
            }
        }
    }
    else
    {
        TotalNum2->setText("0");
    }
}

void ChangeRoom::ChangeRoomNum()
{
    Room *ptr;
    if (RoomType2->currentIndex() != 0)
    {
        for (ptr = thishotel->getRoomhead();ptr != nullptr;ptr = ptr->getnext())
        {
            if ((ptr->getType() == RoomType2->currentText()) && (*(ptr->getDate()) == Date2->date()))
            {
                QString number;
                RoomNum2->setText(number.setNum(double(ptr->getRoomNum()),'f',0));
                break;
            }
        }
    }
    else
    {
        RoomNum2->setText("0");
    }
}

void ChangeRoom::ChangeMoney()
{
    Room *ptr;
    if (RoomType2->currentIndex() != 0)
    {
        for (ptr = thishotel->getRoomhead();ptr != nullptr;ptr = ptr->getnext())
        {
            if ((ptr->getType() == RoomType2->currentText()) && (*(ptr->getDate()) == Date4->date()))
            {
                QString number;
                MoneyPerNight2->setText(number.setNum(double(ptr->getmoneyPerNight()),'f',2));
                break;
            }
        }
    }
    else
    {
        MoneyPerNight2->setText("0");
    }
}

void ChangeRoom::EnableChange()
{
    if ((RoomType2->currentIndex() != 0) && ((totalchange->isChecked() || (roomnumchange->isChecked()) || (moneychange->isChecked()))))
    {
        ChangeButton->setEnabled(true);
    }
}

void ChangeRoom::Change()
{
    Room *ptr;
    if (totalchange->isChecked())
    {
        for (ptr = thishotel->getRoomhead();ptr != nullptr;ptr = ptr->getnext())
        {
            if ((ptr->getType() == RoomType2->currentText()) && (*(ptr->getDate()) == date2->date()))
            {
                break;
            }
        }
        for (;(ptr->getType() == RoomType2->currentText()) && (ptr != nullptr);ptr = ptr->getnext())
        {
            int changenum = int(TotalNum2->text().toFloat()) -  ptr->getTotalNum();
            ptr->ChangeTotalNum(int(TotalNum2->text().toFloat()));
            ptr->ChangeRoomNum(ptr->getRoomNum() + changenum);
            if (ptr->getnext() == nullptr)
            {
                break;
            }
        }
        for (ptr = Roomhead;ptr != nullptr;ptr = ptr->getnext())
        {
            if ((ptr->getHotalName() == thishotel->getHotalName()) && (ptr->getType() == RoomType2->currentText()) && (*(ptr->getDate()) == date2->date()))
            {
                break;
            }
        }
        for (;(ptr->getHotalName() == thishotel->getHotalName()) && (ptr->getType() == RoomType2->currentText()) && (ptr != nullptr);ptr = ptr->getnext())
        {
            int changenum = int(TotalNum2->text().toFloat()) -  ptr->getTotalNum();
            ptr->ChangeTotalNum(int(TotalNum2->text().toFloat()));
            ptr->ChangeRoomNum(ptr->getRoomNum() + changenum);
            if (ptr->getnext() == nullptr)
            {
                break;
            }
        }
    }

    if (roomnumchange->isChecked())
    {
        for (ptr = thishotel->getRoomhead();ptr != nullptr;ptr = ptr->getnext())
        {
            if ((ptr->getType() == RoomType2->currentText()) && (*(ptr->getDate()) == Date2->date()))
            {
                break;
            }
        }
        if (int(RoomNum2->text().toFloat()) > ptr->getTotalNum())
        {
            QMessageBox::warning(NULL,tr("错误"),tr("余量修改失败！\n房间剩余数量大于总数量！"),QMessageBox::Ok,QMessageBox::Ok);
            successful = true;
            close();
        }
        else
        {
            ptr->ChangeRoomNum(int(RoomNum2->text().toFloat()));
            for (ptr = Roomhead;ptr != nullptr;ptr = ptr->getnext())
            {
                if ((ptr->getHotalName() == thishotel->getHotalName()) && (ptr->getType() == RoomType2->currentText()) && (*(ptr->getDate()) == Date2->date()))
                {
                    break;
                }
            }
            ptr->ChangeRoomNum(int(RoomNum2->text().toFloat()));
        }
    }

    if (moneychange->isChecked())
    {
        for (ptr = thishotel->getRoomhead();ptr != nullptr;ptr = ptr->getnext())
        {
            if ((ptr->getType() == RoomType2->currentText()) && (*(ptr->getDate()) == Date4->date()))
            {
                break;
            }
        }
        ptr->ChangemoneyPerNight(MoneyPerNight2->text().toFloat());
        for (ptr = Roomhead;ptr != nullptr;ptr = ptr->getnext())
        {
            if ((ptr->getHotalName() == thishotel->getHotalName()) && (ptr->getType() == RoomType2->currentText()) && (*(ptr->getDate()) == Date4->date()))
            {
                break;
            }
        }
        ptr->ChangemoneyPerNight(MoneyPerNight2->text().toFloat());

        if (MoneyPerNight2->text().toFloat() < thishotel->getminMoney())
        {
            thishotel->changeminMoney(MoneyPerNight2->text().toFloat());
        }
    }
    successful = true;
    close();
}

void ChangeRoom::closeEvent(QCloseEvent *event)
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
