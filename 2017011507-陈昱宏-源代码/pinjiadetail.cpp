#include "pinjiadetail.h"
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

PinJiaDetail::PinJiaDetail(PinJiaMessage *ptr, QWidget *parent)
    :PinJia(ptr),QDialog(parent)
{
    QString Pinjia;

    info = new QLabel(tr("评价详情"));
    info->setAlignment(Qt::AlignCenter);

    user1 = new QLabel(tr("评价用户账户"));
    user1->setAlignment(Qt::AlignLeft);
    user2 = new QLabel("：" + ptr->getmessage()->getsendUser());
    user2->setAlignment(Qt::AlignLeft);

    pinjia1 = new QLabel(tr("评价分数"));
    pinjia1->setAlignment(Qt::AlignLeft);
    pinjia2 = new QLabel("：" + Pinjia.setNum(ptr->getPinJia(),'f',1));
    pinjia2->setAlignment(Qt::AlignLeft);

    message1 = new QLabel(tr("评价内容："));
    message1->setAlignment(Qt::AlignLeft);

    QStringList header;
    header << "内容" << "时间" << " ";

    Message *ptr1;
    int row = 0;
    for (ptr1 = ptr->getmessage();ptr1 != nullptr;ptr1 = ptr1->getnext())
    {
        row += 1;
    }
    message2 = new QTableWidget(row,3,this);
    row = 0;
    for (ptr1 = ptr->getmessage();ptr1 != nullptr;ptr1 = ptr1->getnext())
    {
        message2->setItem(row,0,new QTableWidgetItem(ptr1->getmessage()));
        message2->setItem(row,1,new QTableWidgetItem(ptr1->getdate()->toString("yyyy-MM-dd hh:mm:ss")));
        message2->setItem(row,2,new QTableWidgetItem(tr("详情")));
        row ++;
    }
    message2->setHorizontalHeaderLabels(header);

    OkButton = new QPushButton("Ok");

    connect(message2,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(ButtonClicked(QTableWidgetItem*)));
    connect(OkButton,SIGNAL(clicked()),SLOT(close()));

    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->addWidget(info,0,0,1,5);
    gridlayout->addWidget(user1,1,0,1,2);
    gridlayout->addWidget(user2,1,2,1,3);
    gridlayout->addWidget(pinjia1,2,0,1,2);
    gridlayout->addWidget(pinjia2,2,2,1,3);
    gridlayout->addWidget(message1,3,0,1,2);
    gridlayout->addWidget(message2,4,0,1,5);
    gridlayout->addWidget(OkButton,5,1,1,3);

    QHBoxLayout *hboxlayout = new QHBoxLayout;
    hboxlayout->addLayout(gridlayout);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addLayout(hboxlayout);

    setLayout(mainlayout);
}

void PinJiaDetail::ButtonClicked(QTableWidgetItem *item)
{
    int row;
    int col;
    row = item->row();
    col = item->column();
    if (col == 2)
    {
        Message *ptr;
        for (ptr = PinJia->getmessage();ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss") != message2->item(row,1)->text();ptr = ptr->getnext())
        {}
        messagedetail = new MessageDetail(ptr);
        messagedetail->exec();
    }
}
