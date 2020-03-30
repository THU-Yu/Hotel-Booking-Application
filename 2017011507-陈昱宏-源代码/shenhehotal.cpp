#include "shenhehotal.h"
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDateTime>

ShenHeHotal::ShenHeHotal(Hotal *hotalhead, Message *messagehead, QWidget *parent)
    :Hotalhead(hotalhead), Messagehead(messagehead),QMainWindow(parent)
{
    info = new QLabel(tr("待审核酒店"));
    info->setAlignment(Qt::AlignCenter);

    int row = 0;
    int index = 0;
    for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
    {
        if (ptr->getNew())
        {
            row += 1;
        }
    }
    QStringList header;
    MainTable = new QTableWidget(row,7,this);
    header << "酒店名" << "酒店经理账户" << "所在地" << "酒店信息" << " " << " " << " ";
    for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
    {
        if (ptr->getNew())
        {
            MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
            MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
            MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
            MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
            MainTable->setItem(index,4,new QTableWidgetItem("详情"));
            MainTable->setItem(index,5,new QTableWidgetItem("通过"));
            MainTable->setItem(index,6,new QTableWidgetItem("不通过"));
            index ++;
        }
    }

    MainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MainTable->setColumnWidth(1,150);
    MainTable->setHorizontalHeaderLabels(header);

    BackButton = new QPushButton(tr("返回"));

    connect(MainTable,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(ButtonClicked(QTableWidgetItem*)));
    connect(BackButton,SIGNAL(clicked()),this,SLOT(close()));

    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->addWidget(info,0,55,1,1);
    gridlayout->addWidget(MainTable,1,0,1,110);
    gridlayout->addWidget(BackButton,2,55,1,1);

    QHBoxLayout *hboxlayout = new QHBoxLayout;
    hboxlayout->addLayout(gridlayout);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addLayout(hboxlayout);

    QWidget *widget = new QWidget;
    widget->setLayout(mainlayout);
    setCentralWidget(widget);
}

void ShenHeHotal::ButtonClicked(QTableWidgetItem *item)
{
    int row;
    int col;
    row = item->row();
    col = item->column();
    if (col == 4)
    {
        Hotal *ptr;
        for (ptr = Hotalhead;ptr->getHotalName() != MainTable->item(row,0)->text();ptr = ptr->getHotalnext())
        {}
        hotaldetail = new HotalDetail(ptr);
        hotaldetail->show();
    }
    else if (col == 5)
    {
        if (QMessageBox::question(NULL,tr("审核酒店"),"确定让酒店名为" + MainTable->item(row,0)->text() + "\n的酒店通过审核？",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes) == QMessageBox::Yes)
        {
            Hotal *ptr;
            for (ptr = Hotalhead;ptr->getHotalName() != MainTable->item(row,0)->text();ptr = ptr->getHotalnext())
            {}
            ptr->changeNew(false);
            ptr->changeSuccessful(true);
            MainTable->removeRow(row);
            Message *ptr1;
            for (ptr1 = Messagehead;ptr1->getnext() != nullptr;ptr1 = ptr1->getnext())
            {}
            Message *newmessage = new Message("2017011507",ptr->getHotalManagerAccount(),("恭喜你！你的酒店" + ptr->getHotalName() + "已经审核通过！"),nullptr,new QDateTime(QDateTime::currentDateTime()));
            ptr1->changenext(newmessage);
       }
    }
    else if (col == 6)
    {
        if (QMessageBox::question(NULL,tr("审核酒店"),"确定不让酒店名为" + MainTable->item(row,0)->text() + "\n的酒店通过审核？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
        {
            Hotal *ptr;
            for (ptr = Hotalhead;ptr->getHotalName() != MainTable->item(row,0)->text();ptr = ptr->getHotalnext())
            {}
            ptr->changeNew(false);
            ptr->changeSuccessful(false);
            MainTable->removeRow(row);
            Message *ptr1;
            for (ptr1 = Messagehead;ptr1->getnext() != nullptr;ptr1 = ptr1->getnext())
            {}
            Message *newmessage = new Message("2017011507",ptr->getHotalManagerAccount(),("很遗憾的告诉你...你的酒店" + ptr->getHotalName() + "没有通过审核..."),nullptr,new QDateTime(QDateTime::currentDateTime()));
            ptr1->changenext(newmessage);
       }
    }
}
