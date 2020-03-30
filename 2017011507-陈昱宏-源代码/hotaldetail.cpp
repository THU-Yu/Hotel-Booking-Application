#include "hotaldetail.h"
#include "pinjiadetail.h"
#include "roomdetail.h"
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDebug>

HotalDetail::HotalDetail(Hotal *ptr, QWidget *parent)
    :hotal(ptr),QDialog(parent)
{
    picture = new QLabel(this);
    picture->setGeometry(0,0,30,24);
    QPixmap Image(":/Hotal.jpg");
    QPixmap newImage = Image.scaled(600,480).scaled(300,240,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    picture->setScaledContents(false);
    picture->setPixmap(newImage);
    picture->setAlignment(Qt::AlignCenter);

    info = new QLabel(tr("酒店资讯"));
    info->setAlignment(Qt::AlignCenter);

    hotalname1 = new QLabel(tr("酒店名"));
    hotalname1->setAlignment(Qt::AlignLeft);
    hotalname2 = new QLabel("：" + ptr->getHotalName());
    hotalname2->setAlignment(Qt::AlignLeft);

    hotalaccount1 = new QLabel(tr("酒店经理账户"));
    hotalaccount1->setAlignment(Qt::AlignLeft);
    hotalaccount2 = new QLabel("：" + ptr->getHotalManagerAccount());
    hotalaccount2->setAlignment(Qt::AlignLeft);

    hotalinfo = new QLabel(tr("酒店信息："));
    hotalinfo->setAlignment(Qt::AlignLeft);
    HotalInfo = new QTextEdit;
    HotalInfo->setText(ptr->getHotalInfo());
    HotalInfo->setWordWrapMode(QTextOption::WrapAnywhere);
    HotalInfo->setReadOnly(true);

    hotaltel = new QLabel(tr("酒店电话"));
    hotaltel->setAlignment(Qt::AlignLeft);
    HotalTel = new QLabel("：" + ptr->getHotalTel());
    HotalTel->setAlignment(Qt::AlignLeft);

    RoomType = new QLabel(tr("房间种类："));
    RoomType->setAlignment(Qt::AlignLeft);
    QStringList header;
    header << "房间种类" << "今日总数量" << "今日剩余数量" << "今晚价钱" << " ";
    int row = 0;
    Room *roomptr,*ptr2;
    for (roomptr = ptr->getRoomhead();roomptr != nullptr;roomptr = roomptr->getnext())
    {
        if (roomptr == ptr->getRoomhead())
        {
            row = 1;
            ptr2 = roomptr;
        }
        else if (ptr2->getType() != roomptr->getType())
        {
            row += 1;
            ptr2 = roomptr;
        }
    }
    room = new QTableWidget(row,5,this);
    row = 0;
    QString num;
    for (roomptr = ptr->getRoomhead();roomptr != nullptr;roomptr = roomptr->getnext())
    {
        if (roomptr == ptr->getRoomhead())
        {
            room->setItem(row,0,new QTableWidgetItem(roomptr->getType()));
            room->setItem(row,4,new QTableWidgetItem("详情"));
            ptr2 = roomptr;
        }
        else if (ptr2->getType() != roomptr->getType())
        {
            row ++;
            room->setItem(row,0,new QTableWidgetItem(roomptr->getType()));
            room->setItem(row,4,new QTableWidgetItem("详情"));
            ptr2 = roomptr;
        }
        if (*(roomptr->getDate()) == QDate::currentDate())
        {
            room->setItem(row,1,new QTableWidgetItem(num.setNum(double(roomptr->getTotalNum()),'f',0)));
            room->setItem(row,2,new QTableWidgetItem(num.setNum(double(roomptr->getRoomNum()),'f',0)));
            room->setItem(row,3,new QTableWidgetItem(num.setNum(double(roomptr->getmoneyPerNight()),'f',2)));
        }
    }
    room->setEditTriggers(QAbstractItemView::NoEditTriggers);
    room->setHorizontalHeaderLabels(header);
    room->setColumnWidth(2,150);

    PinJia = new QLabel(tr("评价："));
    PinJia->setAlignment(Qt::AlignLeft);
    QStringList header1;
    header1 << "用户账户" << "评价内容" << "评价分数" << "此用户评价信息数" << " ";
    row = 0;
    PinJiaMessage *ptr_1;
    for (ptr_1 = ptr->getPMhead();ptr_1 != nullptr;ptr_1 = ptr_1->getnext())
    {
        row += 1;
    }
    pinjia = new QTableWidget(row,5,this);
    row = 0;
    double number = 0;
    for (ptr_1 = ptr->getPMhead();ptr_1 != nullptr;ptr_1 = ptr_1->getnext())
    {
        pinjia->setItem(row,0,new QTableWidgetItem(ptr_1->getmessage()->getsendUser()));
        pinjia->setItem(row,1,new QTableWidgetItem(ptr_1->getmessage()->getmessage()));
        pinjia->setItem(row,2,new QTableWidgetItem(num.setNum(ptr_1->getPinJia(),'f',2)));
        for (Message *head = ptr_1->getmessage();head != nullptr;head = head->getnext())
        {
            number += 1;
        }
        pinjia->setItem(row,3,new QTableWidgetItem(num.setNum(number,'f',0)));
        pinjia->setItem(row,4,new QTableWidgetItem(tr("详情")));
        row ++;
        number = 0;
    }
    pinjia->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pinjia->setHorizontalHeaderLabels(header1);
    pinjia->setColumnWidth(3,200);

    Successful1 = new QLabel(tr("审核状态"));
    Successful1->setAlignment(Qt::AlignLeft);
    if (ptr->getSuccessful())
    {
        Successful2 = new QLabel(tr("：通过审核"));
    }
    else if (ptr->getNew())
    {
        Successful2 = new QLabel(tr("：等待审核中..."));
    }
    else
    {
        Successful2 = new QLabel(tr("：酒店未通过审核"));
    }
    Successful2->setAlignment(Qt::AlignLeft);

    OkButton = new QPushButton("Ok");

    connect(OkButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(pinjia,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(ButtonClicked(QTableWidgetItem*)));
    connect(room,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(buttonclicked(QTableWidgetItem*)));

    gridlayout = new QGridLayout;
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->addWidget(info,0,0,1,10);
    gridlayout->addWidget(picture,1,0,6,5);
    gridlayout->addWidget(hotalname1,1,5,1,2);
    gridlayout->addWidget(hotalname2,1,7,1,3);
    gridlayout->addWidget(hotalaccount1,2,5,1,2);
    gridlayout->addWidget(hotalaccount2,2,7,1,3);
    gridlayout->addWidget(hotaltel,3,5,1,2);
    gridlayout->addWidget(HotalTel,3,7,1,3);
    gridlayout->addWidget(hotalinfo,4,5,1,2);
    gridlayout->addWidget(HotalInfo,5,5,1,5);
    gridlayout->addWidget(Successful1,6,5,1,2);
    gridlayout->addWidget(Successful2,6,7,1,3);
    gridlayout->addWidget(RoomType,7,0,1,2);
    gridlayout->addWidget(room,8,0,1,10);
    gridlayout->addWidget(PinJia,9,0,1,2);
    gridlayout->addWidget(pinjia,10,0,1,10);
    gridlayout->addWidget(OkButton,11,4,1,3);

    mainlayout = new QVBoxLayout;
    mainlayout->addLayout(gridlayout);

    setLayout(mainlayout);
}

void HotalDetail::ButtonClicked(QTableWidgetItem *item)
{
    int row;
    int col;
    row = item->row();
    col = item->column();
    if (col == 4)
    {
        PinJiaMessage *ptr;
        for (ptr = hotal->getPMhead();ptr->getmessage()->getsendUser() != pinjia->item(row,0)->text();ptr = ptr->getnext())
        {}
        PinJiaDetail *pinjiadetail = new PinJiaDetail(ptr,this);
        pinjiadetail->exec();
    }
}

void HotalDetail::buttonclicked(QTableWidgetItem *item)
{
    int row;
    int col;
    row = item->row();
    col = item->column();
    if (col == 4)
    {
        RoomDetail *roomdetail = new RoomDetail(hotal,room->item(row,0)->text(),this);
        roomdetail->exec();
    }
}
