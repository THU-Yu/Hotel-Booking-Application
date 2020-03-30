#include "shenheorder.h"
#include "paymoney.h"
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDate>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

ShenHeOrder::ShenHeOrder(Hotal *hotalhead, HotalOrder *orderhead, Message *messagehead, Room *roomhead, PlatformUser *mainaccount3, QWidget *parent)
    :Hotalhead(hotalhead), Orderhead(orderhead), Messagehead(messagehead), Roomhead(roomhead), MainAccount3(mainaccount3),QMainWindow(parent)
{
    info = new QLabel(tr("待审核订单"));
    info->setAlignment(Qt::AlignCenter);

    int row = 0;
    int index = 0;
    for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
    {
        if (ptr->getNew())
        {
            row += 1;
        }
    }
    QString money;
    QStringList header;
    MainTable = new QTableWidget(row,9,this);
    header << "订单编号" << "下单用户" << "酒店名" << "房间类型" << "总金额" << "付钱与否" << " " << " " << " ";
    for (HotalOrder *ptr = Orderhead;ptr != 0;ptr = ptr->getnext())
    {
        if (ptr->getNew())
        {
            MainTable->setItem(index,0,new QTableWidgetItem(ptr->getOrderNumber()));
            MainTable->setItem(index,1,new QTableWidgetItem(ptr->getUserAccount()));
            MainTable->setItem(index,2,new QTableWidgetItem(ptr->getHotalName()));
            MainTable->setItem(index,3,new QTableWidgetItem(ptr->getRoomType()));
            MainTable->setItem(index,4,new QTableWidgetItem(money.setNum(ptr->getTotalmoney(),'f',2)));
            if (ptr->getPayOrNot())
            {
                MainTable->setItem(index,5,new QTableWidgetItem("已付款"));
            }
            else
            {
                MainTable->setItem(index,5,new QTableWidgetItem("未付款"));
            }
            MainTable->setItem(index,6,new QTableWidgetItem("详情"));
            MainTable->setItem(index,7,new QTableWidgetItem("通过"));
            MainTable->setItem(index,8,new QTableWidgetItem("不通过"));
            index ++;
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

void ShenHeOrder::ButtonClicked(QTableWidgetItem *item)
{
    int row;
    int col;
    row = item->row();
    col = item->column();
    if (col == 6)
    {
        HotalOrder *ptr;
        for (ptr = Orderhead;ptr->getOrderNumber() != MainTable->item(row,0)->text();ptr = ptr->getnext())
        {}
        orderdetail = new OrderDetail(ptr);
        orderdetail->show();
    }
    else if (col == 7)
    {
        if (QMessageBox::question(NULL,tr("审核订单"),"确定让编号为" + MainTable->item(row,0)->text() + "\n的订单通过审核？",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes) == QMessageBox::Yes)
        {
            HotalOrder *ptr;
            for (ptr = Orderhead;ptr->getOrderNumber() != MainTable->item(row,0)->text();ptr = ptr->getnext())
            {}
            PayMoney *pay = new PayMoney(ptr,"转钱给酒店",nullptr,nullptr,MainAccount3);
            if (pay->exec() == QDialog::Accepted)
            {
                ptr->changeNew();
                ptr->changeSuccessFul();
                Message *ptr1;
                for (ptr1 = Messagehead;ptr1->getnext() != nullptr;ptr1 = ptr1->getnext())
                {}
                Message *newmessage1 = new Message("2017011507",ptr->getUserAccount(),("恭喜你！你的订单" + ptr->getOrderNumber() + "已经被酒店接单！"),nullptr,new QDateTime(QDateTime::currentDateTime()));
                ptr1->changenext(newmessage1);
                Message *newmessage2 = new Message("2017011507",ptr->getHotalAccount(),("你有新的订单，订单编号为" + ptr->getOrderNumber() + "，对方已付款！"),nullptr,new QDateTime(QDateTime::currentDateTime()));
                newmessage1->changenext(newmessage2);
                Message *newmessage3 = new Message(ptr->getHotalAccount(),ptr->getUserAccount(),("尊敬的客户" + ptr->getUserAccount() + "您好！\n您的订单（编号为" + ptr->getOrderNumber() + "）我已接单，感谢您选择" + ptr->getHotalName() + "!期待您在" + ptr->getStart()->toString("yyyy-MM-dd") + "到" + ptr->getFinal()->toString("yyyy-MM-dd") + "的光临！\n如有任何问题，请回复此条消息与我联系！"),nullptr,new QDateTime(QDateTime::currentDateTime()));
                newmessage2->changenext(newmessage3);
                double money;
                money = ptr->getTotalmoney();

                QSqlQuery query;
                query.exec("select account, bankMoney from User");
                while (query.next())
                {
                    if (query.value(0).toString() == ptr->getHotalAccount())
                    {
                        money += query.value(1).toDouble();
                        break;
                    }
                }

                query.prepare("update User set bankMoney = :money where account = :account");
                query.bindValue(":money",money);
                query.bindValue(":account",ptr->getHotalAccount());
                query.exec();
                query.prepare("select account, bankMoney from User");
                query.exec();
                while (query.next())
                {
                    if (query.value(0).toString() == "2017011507")
                    {
                        money = query.value(1).toDouble() - ptr->getTotalmoney();
                        break;
                    }
                }
                query.prepare("update User set bankMoney = :money where account = :account");
                query.bindValue(":money",money);
                query.bindValue(":account","2017011507");
                query.exec();

                MainAccount3->changemoney(money);

                MainTable->removeRow(row);
            }
        }
    }
    else if (col == 8)
    {
        if (QMessageBox::question(NULL,tr("审核订单"),"确定不让编号为" + MainTable->item(row,0)->text() + "\n的订单通过审核？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
        {
            HotalOrder *ptr;
            for (ptr = Orderhead;ptr->getOrderNumber() != MainTable->item(row,0)->text();ptr = ptr->getnext())
            {}
            PayMoney *pay = new PayMoney(ptr,"退还已付款",nullptr,nullptr,MainAccount3);
            if (pay->exec() == QDialog::Accepted)
            {
                ptr->changeNew();
                Message *ptr1;
                for (ptr1 = Messagehead;ptr1->getnext() != nullptr;ptr1 = ptr1->getnext())
                {}
                Message *newmessage1 = new Message("2017011507",ptr->getUserAccount(),("很遗憾...你的订单" + ptr->getOrderNumber() + "已经被取消！已付款已经退回您的银行账户！\n如有任何问题，回复此条消息联系客服！"),nullptr,new QDateTime(QDateTime::currentDateTime()));
                ptr1->changenext(newmessage1);

                //处理房间数
                Hotal *ptr2;
                for (ptr2 = Hotalhead;ptr2->getHotalName() != MainTable->item(row,2)->text();ptr2 = ptr2->getHotalnext())
                {}

                Room *ptr3;
                for (ptr3 = ptr2->getRoomhead();ptr3->getType() != MainTable->item(row,3)->text();ptr3 = ptr3->getnext())
                {}
                for (;ptr3->getType() == MainTable->item(row,3)->text();ptr3 = ptr3->getnext())
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
                        if (query.value(0).toString() == "2017011507")
                        {
                            money = query.value(1).toDouble() - ptr->getTotalmoney();
                            break;
                        }
                    }
                    query.prepare("update User set bankMoney = :money where account = :account");
                    query.bindValue(":money",money);
                    query.bindValue(":account","2017011507");
                    query.exec();

                    MainAccount3->changemoney(money);
                }

                MainTable->removeRow(row);
            }
        }
    }
}
