#include "orderdetail.h"
#include <QLabel>
#include <QPushButton>
#include <QDebug>

OrderDetail::OrderDetail(HotalOrder *ptr, QWidget *parent)
    :QDialog(parent)
{
    info = new QLabel(tr("订单详情"));
    info->setAlignment(Qt::AlignCenter);

    ordernumber1 = new QLabel(tr("订单编号："));
    ordernumber1->setAlignment(Qt::AlignRight);
    ordernumber2 = new QLabel(ptr->getOrderNumber());
    ordernumber2->setAlignment(Qt::AlignLeft);

    useraccount1 = new QLabel(tr("下单用户账户："));
    useraccount1->setAlignment(Qt::AlignRight);
    useraccount2 = new QLabel(ptr->getUserAccount());
    useraccount2->setAlignment(Qt::AlignLeft);

    hotalname1 = new QLabel(tr("酒店名："));
    hotalname1->setAlignment(Qt::AlignRight);
    hotalname2 = new QLabel(ptr->getHotalName());
    hotalname2->setAlignment(Qt::AlignLeft);

    hotalaccount1 = new QLabel(tr("酒店经理账户："));
    hotalaccount1->setAlignment(Qt::AlignRight);
    hotalaccount2 = new QLabel(ptr->getHotalAccount());
    hotalaccount2->setAlignment(Qt::AlignLeft);

    QString money;
    totalmoney1 = new QLabel(tr("总金额："));
    totalmoney1->setAlignment(Qt::AlignRight);
    totalmoney2 = new QLabel(money.setNum(ptr->getTotalmoney(),'f',2));
    totalmoney2->setAlignment(Qt::AlignLeft);

    roomtype1 = new QLabel(tr("房间类型："));
    roomtype1->setAlignment(Qt::AlignRight);
    roomtype2 = new QLabel(ptr->getRoomType());
    roomtype2->setAlignment(Qt::AlignLeft);

    startdate1 = new QLabel(tr("起始时间："));
    startdate1->setAlignment(Qt::AlignRight);
    startdate2 = new QLabel(ptr->getStart()->toString("yyyy-MM-dd"));
    startdate2->setAlignment(Qt::AlignLeft);

    finaldate1 = new QLabel(tr("结束时间："));
    finaldate1->setAlignment(Qt::AlignRight);
    finaldate2 = new QLabel(ptr->getFinal()->toString("yyyy-MM-dd"));
    finaldate2->setAlignment(Qt::AlignLeft);

    successful1 = new QLabel(tr("订单状态："));
    successful1->setAlignment(Qt::AlignRight);
    if (ptr->getSuccessFul())
    {
        if (ptr->getCancelNew())
        {
            successful2 = new QLabel(tr("退款申请中..."));
        }
        else if (ptr->getCancelSuccessful())
        {
            successful2 = new QLabel(tr("退款申请成功！"));
        }
        else if (QDate::currentDate() < *(ptr->getStart()))
        {
            successful2 = new QLabel(tr("酒店已接单！"));
        }
        else if ((QDate::currentDate() >= *(ptr->getStart())) && ptr->getcheckin() && !(ptr->getcheckout()))
        {
            successful2 = new QLabel(tr("客户入住中..."));
        }
        else if ((QDate::currentDate() >= *(ptr->getStart())) && !(ptr->getcheckin()) && !(ptr->getcheckout()))
        {
            successful2 = new QLabel(tr("酒店已接单！"));
        }
        else
        {
            successful2 = new QLabel(tr("订单已完成！"));
        }
    }
    else if (ptr->getNew())
    {
        if (ptr->getPayOrNot())
        {
            successful2 = new QLabel(tr("订单待确认..."));
        }
        else
        {
            successful2 = new QLabel(tr("待付款"));
        }
    }
    else
    {
        successful2 = new QLabel(tr("订单被取消！"));
    }
    successful2->setAlignment(Qt::AlignLeft);

    OkButton = new QPushButton(tr("Ok"));

    connect(OkButton,SIGNAL(clicked()),this,SLOT(close()));

    mainlayout = new QGridLayout;
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->addWidget(info,0,0,1,5);
    mainlayout->addWidget(ordernumber1,1,0,1,2);
    mainlayout->addWidget(ordernumber2,1,2,1,3);
    mainlayout->addWidget(useraccount1,2,0,1,2);
    mainlayout->addWidget(useraccount2,2,2,1,3);
    mainlayout->addWidget(hotalname1,3,0,1,2);
    mainlayout->addWidget(hotalname2,3,2,1,3);
    mainlayout->addWidget(hotalaccount1,4,0,1,2);
    mainlayout->addWidget(hotalaccount2,4,2,1,3);
    mainlayout->addWidget(roomtype1,5,0,1,2);
    mainlayout->addWidget(roomtype2,5,2,1,3);
    mainlayout->addWidget(startdate1,6,0,1,2);
    mainlayout->addWidget(startdate2,6,2,1,3);
    mainlayout->addWidget(finaldate1,7,0,1,2);
    mainlayout->addWidget(finaldate2,7,2,1,3);
    mainlayout->addWidget(totalmoney1,8,0,1,2);
    mainlayout->addWidget(totalmoney2,8,2,1,3);
    mainlayout->addWidget(successful1,9,0,1,2);
    mainlayout->addWidget(successful2,9,2,1,3);
    mainlayout->addWidget(OkButton,10,1,1,3);

    setLayout(mainlayout);
}
