#include "CancelOrder.h"
#include "paymoney.h"
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QStringList>
#include <QMessageBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

CancelOrder::CancelOrder(Hotal *hotalhead, HotalOrder *orderhead, Message *messagehead, Room *roomhead, HotalUser *Mainaccount, QWidget *parent)
    :Hotalhead(hotalhead), Orderhead(orderhead), Messagehead(messagehead),Roomhead(roomhead), MainAccount(Mainaccount), QMainWindow(parent)
{
    info = new QLabel(tr("退款申请"));
    info->setAlignment(Qt::AlignCenter);

    int row = 0;
    int index = 0;
    for (HotalOrder *head = orderhead;head != nullptr;head = head->getnext())
    {
        if (head->getHotalAccount() == MainAccount->getaccount())
        {
            if (head->getCancelNew())
            {
                row ++;
            }
        }
    }

    QString money;
    QStringList header;
    header << "订单编号" << "下单用户" << "房间类型" << "总金额" << " " << " " << " ";
    MainTable = new QTableWidget(row,7);
    for (HotalOrder *head = orderhead;head != nullptr;head = head->getnext())
    {
        if (head->getHotalAccount() == MainAccount->getaccount())
        {
            if (head->getCancelNew())
            {
                MainTable->setItem(index,0,new QTableWidgetItem(head->getOrderNumber()));
                MainTable->setItem(index,1,new QTableWidgetItem(head->getUserAccount()));
                MainTable->setItem(index,2,new QTableWidgetItem(head->getRoomType()));
                MainTable->setItem(index,3,new QTableWidgetItem(money.setNum(head->getTotalmoney(),'f',2)));
                MainTable->setItem(index,4,new QTableWidgetItem("详情"));
                MainTable->setItem(index,5,new QTableWidgetItem("通过"));
                MainTable->setItem(index,6,new QTableWidgetItem("不通过"));
                index ++;
            }
        }
    }

    MainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

void CancelOrder::ButtonClicked(QTableWidgetItem *item)
{
    int row = item->row();
    int col = item->column();
    if (item->text() == "通过")
    {
        if (QMessageBox::question(NULL,tr("退款申请"),"确定通过编号为" + MainTable->item(row,0)->text() + "\n的订单的退款申请？",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes) == QMessageBox::Yes)
        {
            HotalOrder *ptr;
            for (ptr = Orderhead;ptr->getOrderNumber() != MainTable->item(row,0)->text();ptr = ptr->getnext())
            {}
            PayMoney *pay = new PayMoney(ptr,"退还已付款",nullptr,MainAccount,nullptr);
            if (pay->exec() == QDialog::Accepted)
            {
                ptr->changeCancelNew();
                ptr->changeCancelSuccessful();
                Message *ptr1;
                for (ptr1 = Messagehead;ptr1->getnext() != nullptr;ptr1 = ptr1->getnext())
                {}
                Message *newmessage1 = new Message(MainAccount->getaccount(),MainTable->item(row,1)->text(),("你提交订单编号为" + ptr->getOrderNumber() + "的退款申请已经通过！\n已付款已经退回您的银行账户！"),nullptr,new QDateTime(QDateTime::currentDateTime()));
                ptr1->changenext(newmessage1);

                //处理房间数
                Hotal *ptr2;
                for (ptr2 = Hotalhead;ptr2->getHotalName() != ptr->getHotalName();ptr2 = ptr2->getHotalnext())
                {}

                Room *ptr3;
                for (ptr3 = ptr2->getRoomhead();ptr3->getType() != MainTable->item(row,2)->text();ptr3 = ptr3->getnext())
                {}
                for (;ptr3->getType() == MainTable->item(row,2)->text();ptr3 = ptr3->getnext())
                {
                    if ((*(ptr3->getDate()) >= *(ptr->getStart())) && (*(ptr3->getDate()) < *(ptr->getFinal())))
                    {
                        if (ptr3->getTotalNum() != 0)
                        {
                            int days = 0;
                            QDate date = *(ptr->getStart());
                            for (;date < *(ptr->getFinal());date = date.addDays(1))
                            {
                                days ++;
                            }
                            ptr3->ChangeRoomNum(ptr3->getRoomNum() + (ptr->getTotalmoney() / (days * ptr3->getmoneyPerNight())));
                        }
                        else
                        {
                            ptr3->ChangeRoomNum(0);
                        }
                    }
                    if (ptr3->getnext() == nullptr)
                    {
                        break;
                    }
                }
                for (ptr3 = Roomhead;(ptr3->getHotalName() != ptr2->getHotalName()) || (ptr3->getType() != ptr->getRoomType());ptr3 = ptr3->getnext())
                {}
                for (;(ptr3->getHotalName() == ptr2->getHotalName()) && (ptr3->getType() == ptr->getRoomType());ptr3 = ptr3->getnext())
                {
                    if ((*(ptr3->getDate()) >= *(ptr->getStart())) && (*(ptr3->getDate()) < *(ptr->getFinal())))
                    {
                        if (ptr3->getTotalNum() != 0)
                        {
                            int days = 0;
                            QDate date = *(ptr->getStart());
                            for (;date < *(ptr->getFinal());date = date.addDays(1))
                            {
                                days ++;
                            }
                            ptr3->ChangeRoomNum(ptr3->getRoomNum() + (ptr->getTotalmoney() / (days * ptr3->getmoneyPerNight())));
                        }
                        else
                        {
                            ptr3->ChangeRoomNum(0);
                        }
                    }
                    if (ptr3->getnext() == nullptr)
                    {
                        break;
                    }
                }
                //处理还款
                if (ptr->getPayOrNot())
                {
                    double money;
                    money = ptr->getTotalmoney();

                    QSqlQuery query;
                    query.prepare("select account, bankMoney from User");
                    query.exec();
                    while (query.next())
                    {
                        if (query.value(0).toString() == ptr->getUserAccount())
                        {
                            money += query.value(1).toDouble();
                            break;
                        }
                    }

                    query.prepare("update User set bankMoney = :money where account = :account");
                    query.bindValue(":money",money);
                    query.bindValue(":account",ptr->getUserAccount());
                    query.exec();

                    query.prepare("select account, bankMoney from User");
                    query.exec();
                    while (query.next())
                    {
                        if (query.value(0).toString() == ptr->getHotalAccount())
                        {
                            money = query.value(1).toDouble() - ptr->getTotalmoney();
                            break;
                        }
                    }
                    query.prepare("update User set bankMoney = :money where account = :account");
                    query.bindValue(":money",money);
                    query.bindValue(":account",ptr->getHotalAccount());
                    query.exec();

                    MainAccount->changemoney(money);
                }

                MainTable->removeRow(row);
            }
        }
    }
    else if (item->text() == "不通过")
    {
        if (QMessageBox::question(NULL,tr("退款申请"),"确定不通过编号为" + MainTable->item(row,0)->text() + "\n的订单的退款申请？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
        {
            HotalOrder *ptr;
            for (ptr = Orderhead;ptr->getOrderNumber() != MainTable->item(row,0)->text();ptr = ptr->getnext())
            {}
            ptr->changeCancelNew();
            ptr->changeCancel();
            Message *ptr1;
            for (ptr1 = Messagehead;ptr1->getnext() != nullptr;ptr1 = ptr1->getnext())
            {}
            Message *newmessage1 = new Message(ptr->getHotalAccount(),ptr->getUserAccount(),("很抱歉！\n你提交订单编号为" + ptr->getOrderNumber() + "订单的退款申请没有通过！\n如有任何问题可以直接回复询问！"),nullptr,new QDateTime(QDateTime::currentDateTime()));
            ptr1->changenext(newmessage1);

            MainTable->removeRow(row);
        }
    }
}
