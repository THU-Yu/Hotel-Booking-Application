#include "searchorder.h"
#include "orderdetail.h"
#include "sendmessagedialog.h"
#include "writepinjia.h"
#include "CancelOrder.h"
#include "paymoney.h"
#include <QPushButton>
#include <QTableWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDate>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>

void SearchOrder::changeSearchOrder(NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainaccount3)
{
    MainAccount1 = Mainaccount1;
    MainAccount2 = Mainaccount2;
    MainAccount3 = Mainaccount3;
    int row = 0;
    int index = 0;
    QString money;
    if (MainAccount1)
    {
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getUserAccount() == MainAccount1->getaccount())
            {
                row += 1;
            }
        }
    }
    else if (MainAccount2)
    {
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            if ((ptr->getHotalAccount() == MainAccount2->getaccount()) && (ptr->getSuccessFul()))
            {
                row += 1;
            }
        }
    }
    else
    {
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            row += 1;
        }
    }

    QStringList header;
    if (MainAccount1)
    {
        MainTable = new QTableWidget(row,7,this);
        header << "订单编号" << "下单用户账号" << "酒店名" << "酒店经理账户" << "总金额" << " " << " ";
        QDate *date = new QDate(QDate::currentDate());
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getUserAccount() == MainAccount1->getaccount())
            {
                if (!(ptr->getPayOrNot()))
                {
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getOrderNumber()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getUserAccount()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getHotalName()));
                    MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalAccount()));
                    MainTable->setItem(index,4,new QTableWidgetItem(money.setNum(ptr->getTotalmoney(),'f',2)));
                    MainTable->setItem(index,5,new QTableWidgetItem("详情"));
                    if (ptr->getNew())
                    {
                        MainTable->setItem(index,6,new QTableWidgetItem("付款"));
                    }
                    else
                    {
                        MainTable->setItem(index,6,new QTableWidgetItem(" "));
                    }
                    index ++;
                }
            }
        }
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getUserAccount() == MainAccount1->getaccount())
            {
                if (ptr->getPayOrNot())
                {
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getOrderNumber()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getUserAccount()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getHotalName()));
                    MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalAccount()));
                    MainTable->setItem(index,4,new QTableWidgetItem(money.setNum(ptr->getTotalmoney(),'f',2)));
                    MainTable->setItem(index,5,new QTableWidgetItem("详情"));
                    if (ptr->getcheckout())
                    {
                        MainTable->setItem(index,6,new QTableWidgetItem("评价"));
                    }
                    else if ((*date < (ptr->getStart()->addDays(-3))) && (ptr->getSuccessFul()) && (!(ptr->getCancelSuccessful())))
                    {
                        MainTable->setItem(index,6,new QTableWidgetItem("申请退款"));
                    }
                    else
                    {
                        MainTable->setItem(index,6,new QTableWidgetItem(" "));
                    }
                    index ++;
                }
            }
        }
        MainTable->setColumnWidth(6,150);
    }
    else if (MainAccount2)
    {
        MainTable = new QTableWidget(row,8,this);
        header << "订单编号" << "下单用户账号" << "酒店名" << "酒店经理账户" << "总金额" << " " << " " << " ";
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            if ((ptr->getHotalAccount() == MainAccount2->getaccount()) && (ptr->getSuccessFul()))
            {
                MainTable->setItem(index,0,new QTableWidgetItem(ptr->getOrderNumber()));
                MainTable->setItem(index,1,new QTableWidgetItem(ptr->getUserAccount()));
                MainTable->setItem(index,2,new QTableWidgetItem(ptr->getHotalName()));
                MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalAccount()));
                MainTable->setItem(index,4,new QTableWidgetItem(money.setNum(ptr->getTotalmoney(),'f',2)));
                MainTable->setItem(index,5,new QTableWidgetItem("详情"));
                MainTable->setItem(index,6,new QTableWidgetItem("发消息"));
                if (*(ptr->getStart()) <= QDate::currentDate() && !(ptr->getcheckin()))
                {
                    MainTable->setItem(index,7,new QTableWidgetItem("入住"));
                }
                else if (*(ptr->getStart()) <= QDate::currentDate() && !(ptr->getcheckout()))
                {
                    MainTable->setItem(index,7,new QTableWidgetItem("退房"));
                }
                else
                {
                    MainTable->setItem(index,7,new QTableWidgetItem(" "));
                }
                index ++;
            }
        }
        MainTable->setColumnWidth(5,75);
        MainTable->setColumnWidth(6,100);
        MainTable->setColumnWidth(7,75);
    }
    else
    {
        MainTable = new QTableWidget(row,6,this);
        header << "订单编号" << "下单用户账号" << "酒店名" << "酒店经理账户" << "总金额" << " ";
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            MainTable->setItem(index,0,new QTableWidgetItem(ptr->getOrderNumber()));
            MainTable->setItem(index,1,new QTableWidgetItem(ptr->getUserAccount()));
            MainTable->setItem(index,2,new QTableWidgetItem(ptr->getHotalName()));
            MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalAccount()));
            MainTable->setItem(index,4,new QTableWidgetItem(money.setNum(ptr->getTotalmoney(),'f',2)));
            MainTable->setItem(index,5,new QTableWidgetItem("详情"));
            index ++;
        }
    }

    BackButton = new QPushButton(tr("返回"));
    CancelOrderButton = new QPushButton(tr("退款申请"));

    if (MainAccount2)
    {
        CancelOrderButton->setVisible(true);
    }
    else
    {
        CancelOrderButton->setVisible(false);
    }

    connect(MainTable,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(ButtonClicked(QTableWidgetItem*)));
    connect(CancelOrderButton,SIGNAL(clicked()),this,SLOT(CheckCancelOrder()));
    connect(BackButton,SIGNAL(clicked()),this,SLOT(Back()));

    MainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MainTable->setHorizontalHeaderLabels(header);
    MainTable->resizeRowsToContents();
    MainTable->resizeColumnsToContents();

    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->addWidget(MainTable,0,0,1,110);
    gridlayout->addWidget(CancelOrderButton,1,55,1,1);
    gridlayout->addWidget(BackButton,2,55,1,1);

    QHBoxLayout *hboxlayout = new QHBoxLayout;
    hboxlayout->addLayout(gridlayout);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addLayout(hboxlayout);

    setLayout(mainlayout);
}

void SearchOrder::changeTable(NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainaccount3)
{
    MainAccount1 = Mainaccount1;
    MainAccount2 = Mainaccount2;
    MainAccount3 = Mainaccount3;

    int row = 0;
    int index = 0;
    QString money;
    if (MainAccount1)
    {
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getUserAccount() == MainAccount1->getaccount())
            {
                row += 1;
            }
        }
    }
    else if (MainAccount2)
    {
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            if ((ptr->getHotalAccount() == MainAccount2->getaccount()) && (ptr->getSuccessFul()))
            {
                row += 1;
            }
        }
    }
    else
    {
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            row += 1;
        }
    }

    if (MainAccount1)
    {
        MainTable->setRowCount(row);
        MainTable->setColumnCount(7);
        QDate *date = new QDate(QDate::currentDate());
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getUserAccount() == MainAccount1->getaccount())
            {
                if (!(ptr->getPayOrNot()))
                {
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getOrderNumber()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getUserAccount()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getHotalName()));
                    MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalAccount()));
                    MainTable->setItem(index,4,new QTableWidgetItem(money.setNum(ptr->getTotalmoney(),'f',2)));
                    MainTable->setItem(index,5,new QTableWidgetItem("详情"));
                    if (ptr->getNew())
                    {
                        MainTable->setItem(index,6,new QTableWidgetItem("付款"));
                    }
                    else
                    {
                        MainTable->setItem(index,6,new QTableWidgetItem(" "));
                    }
                    index ++;
                }
            }
        }
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getUserAccount() == MainAccount1->getaccount())
            {
                if (ptr->getPayOrNot())
                {
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getOrderNumber()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getUserAccount()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getHotalName()));
                    MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalAccount()));
                    MainTable->setItem(index,4,new QTableWidgetItem(money.setNum(ptr->getTotalmoney(),'f',2)));
                    MainTable->setItem(index,5,new QTableWidgetItem("详情"));
                    if (ptr->getcheckout())
                    {
                        MainTable->setItem(index,6,new QTableWidgetItem("评价"));
                    }
                    else if ((*date < (ptr->getStart()->addDays(-3))) && (ptr->getSuccessFul()) && (!(ptr->getCancelSuccessful())))
                    {
                        MainTable->setItem(index,6,new QTableWidgetItem("申请退款"));
                    }
                    else
                    {
                        MainTable->setItem(index,6,new QTableWidgetItem(" "));
                    }
                    index ++;
                }
            }
        }
        CancelOrderButton->setVisible(false);
    }
    else if (MainAccount2)
    {
        MainTable->setRowCount(row);
        MainTable->setColumnCount(8);
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            if ((ptr->getHotalAccount() == MainAccount2->getaccount()) && (ptr->getSuccessFul()))
            {
                MainTable->setItem(index,0,new QTableWidgetItem(ptr->getOrderNumber()));
                MainTable->setItem(index,1,new QTableWidgetItem(ptr->getUserAccount()));
                MainTable->setItem(index,2,new QTableWidgetItem(ptr->getHotalName()));
                MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalAccount()));
                MainTable->setItem(index,4,new QTableWidgetItem(money.setNum(ptr->getTotalmoney(),'f',2)));
                MainTable->setItem(index,5,new QTableWidgetItem("详情"));
                MainTable->setItem(index,6,new QTableWidgetItem("发消息"));
                if (*(ptr->getStart()) <= QDate::currentDate() && !(ptr->getcheckin()))
                {
                    MainTable->setItem(index,7,new QTableWidgetItem("入住"));
                }
                else if (*(ptr->getStart()) <= QDate::currentDate() && !(ptr->getcheckout()))
                {
                    MainTable->setItem(index,7,new QTableWidgetItem("退房"));
                }
                else
                {
                    MainTable->setItem(index,7,new QTableWidgetItem(" "));
                }
                index ++;
            }
            MainTable->setColumnWidth(5,75);
            MainTable->setColumnWidth(6,100);
            MainTable->setColumnWidth(7,75);
        }
        CancelOrderButton->setVisible(true);
    }
    else
    {
        MainTable->setRowCount(row);
        MainTable->setColumnCount(6);
        for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
        {
            MainTable->setItem(index,0,new QTableWidgetItem(ptr->getOrderNumber()));
            MainTable->setItem(index,1,new QTableWidgetItem(ptr->getUserAccount()));
            MainTable->setItem(index,2,new QTableWidgetItem(ptr->getHotalName()));
            MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalAccount()));
            MainTable->setItem(index,4,new QTableWidgetItem(money.setNum(ptr->getTotalmoney(),'f',2)));
            MainTable->setItem(index,5,new QTableWidgetItem("详情"));
            index ++;
        }
        CancelOrderButton->setVisible(false);
    }
}

void SearchOrder::ButtonClicked(QTableWidgetItem *item)
{
    int row;
    int col;
    row = item->row();
    col = item->column();
    HotalOrder *ptr;
    for (ptr = Orderhead;ptr->getOrderNumber() != MainTable->item(row,0)->text();ptr = ptr->getnext())
    {}
    if (col == 5)
    {
        orderdetail = new OrderDetail(ptr,this);
        orderdetail->exec();
    }
    else if (MainTable->item(row,col)->text() == "评价")
    {
        Hotal *_ptr;
        for (_ptr = Hotalhead;_ptr->getHotalName() != MainTable->item(row,2)->text();_ptr = _ptr->getHotalnext())
        {}
        WritePinJia *pinjia = new WritePinJia(_ptr,Messagehead,PinJiahead,MainTable->item(row,2)->text(),MainAccount1,this);
        pinjia->show();
    }
    else if (MainTable->item(row,col)->text() == "申请退款")
    {
        if (ptr->getCancel())
        {
            QMessageBox::information(NULL,tr("退款"),tr("您已经提交过退款申请，\n请耐心等候！"),QMessageBox::Ok,QMessageBox::Ok);
        }
        else
        {
            if (QMessageBox::information(NULL,tr("退款"),tr("申请退款后不可撤销申请，\n确定要申请吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
            {
                QMessageBox::information(NULL,tr("退款"),tr("退款申请已提交！"),QMessageBox::Ok,QMessageBox::Ok);
                ptr->changeCancel();
                ptr->changeCancelNew();
                Message *newmessage = new Message(ptr->getUserAccount(),ptr->getHotalAccount(),"我已向你提交退款申请，请尽快审核！",nullptr,new QDateTime(QDateTime::currentDateTime()));
                Message *ptr1;
                for (ptr1 = Messagehead;ptr1->getnext() != nullptr;ptr1 = ptr1->getnext())
                {}
                ptr1->changenext(newmessage);
            }
        }
    }
    else if (MainTable->item(row,col)->text() == "发消息")
    {
        SendMessageDialog *message = new SendMessageDialog(Messagehead,MainTable->item(row,1)->text(),MainAccount1,MainAccount2,MainAccount3,this);
        message->show();
    }
    else if (MainTable->item(row,col)->text() == "入住")
    {
        if (QMessageBox::question(NULL,tr("入住登记"),tr("用户确定入住吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes) == QMessageBox::Yes)
        {
            ptr->changecheckin(true);
            changeTable(MainAccount1,MainAccount2,MainAccount3);
        }
    }
    else if (MainTable->item(row,col)->text() == "退房")
    {
        if (QMessageBox::question(NULL,tr("退房登记"),tr("用户确定退房吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes) == QMessageBox::Yes)
        {
            ptr->changecheckout(true);
            changeTable(MainAccount1,MainAccount2,MainAccount3);
        }
    }
    else if (item->text() == "付款")
    {
        PayMoney *pay = new PayMoney(ptr,"订单支付",MainAccount1,MainAccount2,MainAccount3);
        pay->exec();
    }
}

void SearchOrder::CheckCancelOrder()
{
    CancelOrder *cancelorder = new CancelOrder(Hotalhead,Orderhead,Messagehead,Roomhead,MainAccount2);
    cancelorder->show();
}

void SearchOrder::Back()
{
    emit back();
}
