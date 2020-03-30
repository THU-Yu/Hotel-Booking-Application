#include "platformmanage.h"
#include "shenhehotal.h"
#include "shenheorder.h"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QVariant>

PlatformManage::PlatformManage(Hotal *h, HotalOrder *o, Message *m, Room *r, QWidget *parent)
    :hotal(h), order(o), message(m), room(r), QWidget(parent)
{
    info = new QLabel(tr("C&W酒店预订平台信息"));
    info->setAlignment(Qt::AlignCenter);

    normalUser1 = new QLabel(tr("一般用户数量："));
    normalUser1->setAlignment(Qt::AlignRight);
    normalUser2 = new QLabel(tr("0"));
    normalUser2->setAlignment(Qt::AlignLeft);
    hotalUser1 = new QLabel(tr("酒店用户数量："));
    hotalUser1->setAlignment(Qt::AlignRight);
    hotalUser2 = new QLabel(tr("0"));
    hotalUser2->setAlignment(Qt::AlignLeft);
    platformUser1 = new QLabel(tr("平台管理员数量："));
    platformUser1->setAlignment(Qt::AlignRight);
    platformUser2 = new QLabel(tr("0"));
    platformUser2->setAlignment(Qt::AlignLeft);
    hotal1 = new QLabel(tr("登记酒店数量："));
    hotal1->setAlignment(Qt::AlignRight);
    hotal2 = new QLabel(tr("0"));
    hotal2->setAlignment(Qt::AlignLeft);
    Order1 = new QLabel(tr("产生订单数量："));
    Order1->setAlignment(Qt::AlignRight);
    Order2 = new QLabel(tr("0"));
    Order2->setAlignment(Qt::AlignLeft);

    BackButton = new QPushButton(tr("返回"));
    CheckHotalButton = new QPushButton(tr("审核酒店"));
    CheckOrderButton = new QPushButton(tr("审核订单"));

    connect(BackButton,SIGNAL(clicked()),this,SLOT(Back()));
    connect(CheckHotalButton,SIGNAL(clicked()),this,SLOT(checkHotal()));
    connect(CheckOrderButton,SIGNAL(clicked()),this,SLOT(checkOrder()));

    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->addWidget(info,0,0,1,5);
    gridlayout->addWidget(normalUser1,1,0,1,2);
    gridlayout->addWidget(hotalUser1,2,0,1,2);
    gridlayout->addWidget(platformUser1,3,0,1,2);
    gridlayout->addWidget(hotal1,4,0,1,2);
    gridlayout->addWidget(Order1,5,0,1,2);
    gridlayout->addWidget(normalUser2,1,2,1,3);
    gridlayout->addWidget(hotalUser2,2,2,1,3);
    gridlayout->addWidget(platformUser2,3,2,1,3);
    gridlayout->addWidget(hotal2,4,2,1,3);
    gridlayout->addWidget(Order2,5,2,1,3);
    gridlayout->addWidget(CheckHotalButton,6,0,1,5);
    gridlayout->addWidget(CheckOrderButton,7,0,1,5);
    gridlayout->addWidget(BackButton,8,0,1,5);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addLayout(gridlayout);

    setLayout(mainlayout);
}

PlatformManage::~PlatformManage()
{

}

void PlatformManage::changePlatfoemManage()
{
    double normalusernum = 0;
    double hotalusernum = 0;
    double platformusernum = 0;
    double hotalnum = 0;
    double ordernum = 0;
    QSqlQuery query;
    query.prepare("select UserType from User");
    if (query.exec())
    {
        while (query.next())
        {
            if (query.value(0).toString() == "一般用户")
            {
                normalusernum += 1;
            }
            else if (query.value(0).toString() == "酒店经理")
            {
                hotalusernum += 1;
            }
            else if (query.value(0).toString() == "平台管理")
            {
                platformusernum += 1;
            }
        }
    }

    for (Hotal *ptr = hotal;ptr != nullptr;ptr = ptr->getHotalnext())
    {
        if (ptr->getSuccessful())
        {
            hotalnum += 1;
        }
    }

    for (HotalOrder *ptr = order;ptr != nullptr;ptr = ptr->getnext())
    {
        if (ptr->getSuccessFul())
        {
            ordernum += 1;
        }
    }

    QString m;
    normalUser2->setText(m.setNum(normalusernum,'f',0));
    hotalUser2->setText(m.setNum(hotalusernum,'f',0));
    platformUser2->setText(m.setNum(platformusernum,'f',0));
    hotal2->setText(m.setNum(hotalnum,'f',0));
    Order2->setText(m.setNum(ordernum,'f',0));

}

void PlatformManage::Back()
{
    emit back();
}

void PlatformManage::checkHotal()
{
    ShenHeHotal *page = new ShenHeHotal(hotal,message);
    page->show();
}

void PlatformManage::checkOrder()
{
    ShenHeOrder *page = new ShenHeOrder(hotal,order,message,room,MainAccount3);
    page->show();
}
