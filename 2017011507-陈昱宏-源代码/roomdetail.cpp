#include "roomdetail.h"
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QDate>
#include <QGridLayout>
#include <QDebug>

RoomDetail::RoomDetail(Hotal *ptr, QString roomtype, QWidget *parent)
    :thishotal(ptr),Roomtype(roomtype),QDialog(parent)
{
    picture = new QLabel(this);
    picture->setGeometry(0,0,30,22.5);
    QPixmap Image(":/Room.jpg");
    QPixmap newImage = Image.scaled(600,450).scaled(300,225,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    picture->setScaledContents(false);
    picture->setPixmap(newImage);
    picture->setAlignment(Qt::AlignCenter);

    info = new QLabel(tr("房间资讯"));
    info->setAlignment(Qt::AlignCenter);

    hotalname1 = new QLabel(tr("酒店名称："));
    hotalname1->setAlignment(Qt::AlignLeft);
    hotalname2 = new QLabel(ptr->getHotalName());
    hotalname2->setAlignment(Qt::AlignLeft);

    RoomType1 = new QLabel(tr("房间种类："));
    RoomType1->setAlignment(Qt::AlignLeft);
    RoomType2 = new QLabel(Roomtype);
    RoomType2->setAlignment(Qt::AlignLeft);

    text2 = new QLabel(tr("查询房间总数："));
    text2->setAlignment(Qt::AlignLeft);

    date_1 = new QLabel(tr("查询时间："));
    date_1->setAlignment(Qt::AlignLeft);

    date_2 = new QDateTimeEdit(QDate::currentDate());
    date_2->setMinimumDate(QDate::currentDate());
    date_2->setMaximumDate(QDate::currentDate().addDays(31));
    date_2->setCalendarPopup(true);
    date_2->setDisplayFormat("yyyy-MM-dd");

    TotalNum1 = new QLabel(tr("房间总数："));
    TotalNum1->setAlignment(Qt::AlignLeft);
    TotalNum2 = new QLabel;
    Room *ptr1;
    QString number;
    for (ptr1 = thishotal->getRoomhead();ptr1->getType() != Roomtype;ptr1 = ptr1->getnext())
    {}
    for (;ptr1->getType() == Roomtype;ptr1 = ptr1->getnext())
    {
        if (*(ptr1->getDate()) == QDate::currentDate())
        {
            TotalNum2->setText(number.setNum(double(ptr1->getTotalNum()),'f',0));
            break;
        }
    }


    text1 = new QLabel(tr("查询房间价格："));
    text1->setAlignment(Qt::AlignLeft);

    Date1 = new QLabel(tr("查询时间："));
    Date1->setAlignment(Qt::AlignLeft);

    Date2 = new QDateTimeEdit(QDate::currentDate());
    Date2->setMinimumDate(QDate::currentDate());
    Date2->setMaximumDate(QDate::currentDate().addDays(31));
    Date2->setCalendarPopup(true);
    Date2->setDisplayFormat("yyyy-MM-dd");

    MoneyPerNight1 = new QLabel(tr("每晚价格："));
    MoneyPerNight1->setAlignment(Qt::AlignLeft);
    MoneyPerNight2 = new QLabel;
    MoneyPerNight2->setAlignment(Qt::AlignLeft);
    for (ptr1 = thishotal->getRoomhead();ptr1->getType() != Roomtype;ptr1 = ptr1->getnext())
    {}
    for (;ptr1->getType() == Roomtype;ptr1 = ptr1->getnext())
    {
        if (*(ptr1->getDate()) == QDate::currentDate())
        {
            MoneyPerNight2->setText(number.setNum(double(ptr1->getmoneyPerNight()),'f',2));
            break;
        }
    }
    text = new QLabel(tr("查询房间剩余："));
    text->setAlignment(Qt::AlignLeft);

    date1 = new QLabel(tr("查询时间："));
    date1->setAlignment(Qt::AlignLeft);

    date2 = new QDateTimeEdit(QDate::currentDate());
    date2->setMinimumDate(QDate::currentDate());
    date2->setMaximumDate(QDate::currentDate().addDays(31));
    date2->setCalendarPopup(true);
    date2->setDisplayFormat("yyyy-MM-dd");

    RoomNum1 = new QLabel(tr("剩余数量："));
    RoomNum1->setAlignment(Qt::AlignLeft);
    RoomNum2 = new QLabel;
    RoomNum2->setAlignment(Qt::AlignLeft);
    for (ptr1 = thishotal->getRoomhead();ptr1->getType() != Roomtype;ptr1 = ptr1->getnext())
    {}
    for (;ptr1->getType() == Roomtype;ptr1 = ptr1->getnext())
    {
        if (*(ptr1->getDate()) == QDate::currentDate())
        {
            RoomNum2->setText(number.setNum(double(ptr1->getRoomNum()),'f',0));
            break;
        }
    }

    OkButton = new QPushButton("Ok");

    connect(OkButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(date_2,SIGNAL(dateChanged(QDate)),this,SLOT(changeTotalNum()));
    connect(date2,SIGNAL(dateChanged(QDate)),this,SLOT(changeRoomNum()));
    connect(Date2,SIGNAL(dateChanged(QDate)),this,SLOT(changemoney()));

    QGridLayout *mainlayout = new QGridLayout;
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->addWidget(info,0,0,1,10);
    mainlayout->addWidget(picture,1,0,1,5);
    mainlayout->addWidget(hotalname1,2,0,1,2);
    mainlayout->addWidget(hotalname2,2,2,1,3);
    mainlayout->addWidget(RoomType1,3,0,1,2);
    mainlayout->addWidget(RoomType2,3,2,1,3);
    mainlayout->addWidget(text2,4,0,1,3);
    mainlayout->addWidget(date_1,5,0,1,2);
    mainlayout->addWidget(date_2,5,2,1,3);
    mainlayout->addWidget(TotalNum1,6,0,1,2);
    mainlayout->addWidget(TotalNum2,6,2,1,3);
    mainlayout->addWidget(text1,7,0,1,3);
    mainlayout->addWidget(Date1,8,0,1,2);
    mainlayout->addWidget(Date2,8,2,1,3);
    mainlayout->addWidget(MoneyPerNight1,9,0,1,2);
    mainlayout->addWidget(MoneyPerNight2,9,2,1,3);
    mainlayout->addWidget(text,10,0,1,3);
    mainlayout->addWidget(date1,11,0,1,2);
    mainlayout->addWidget(date2,11,2,1,3);
    mainlayout->addWidget(RoomNum1,12,0,1,2);
    mainlayout->addWidget(RoomNum2,12,2,1,3);
    mainlayout->addWidget(OkButton,13,1,1,3);

    setLayout(mainlayout);
}

void RoomDetail::changeTotalNum()
{
    Room *ptr1;
    QString number;
    for (ptr1 = thishotal->getRoomhead();ptr1->getType() != Roomtype;ptr1 = ptr1->getnext())
    {}
    for (;ptr1->getType() == Roomtype;ptr1 = ptr1->getnext())
    {
        if (*(ptr1->getDate()) == date_2->date())
        {
            TotalNum2->setText(number.setNum(double(ptr1->getTotalNum()),'f',0));
            break;
        }
    }
}

void RoomDetail::changeRoomNum()
{
    Room *ptr1;
    QString number;
    for (ptr1 = thishotal->getRoomhead();ptr1->getType() != Roomtype;ptr1 = ptr1->getnext())
    {}
    for (;ptr1->getType() == Roomtype;ptr1 = ptr1->getnext())
    {
        if (*(ptr1->getDate()) == date2->date())
        {
            RoomNum2->setText(number.setNum(double(ptr1->getRoomNum()),'f',0));
            break;
        }
    }
}

void RoomDetail::changemoney()
{
    Room *ptr1;
    QString number;
    for (ptr1 = thishotal->getRoomhead();ptr1->getType() != Roomtype;ptr1 = ptr1->getnext())
    {}
    for (;ptr1->getType() == Roomtype;ptr1 = ptr1->getnext())
    {
        if (*(ptr1->getDate()) == Date2->date())
        {
            MoneyPerNight2->setText(number.setNum(double(ptr1->getmoneyPerNight()),'f',2));
            break;
        }
    }
}
