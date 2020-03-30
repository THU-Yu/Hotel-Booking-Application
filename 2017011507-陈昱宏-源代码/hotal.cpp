/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：Hotal.cpp
 * 内容：实现Hotal类成员函数
 * 版本：version_1.2
 * 作者：陈昱宏
 * 创建日期：2018/07/20
 */
#include "hotal.h"
#include <QDebug>

Hotal::Hotal(QString HotalName, QString HotalInfo, QString HotalManagerAccount, QString tel, QString Area)
    :HotalName(HotalName), HotalInfo(HotalInfo), HotalManagerAccount(HotalManagerAccount), HotalTel(tel), Area(Area)  //构造函数实现
{
    roomTypeNum = 0;
    OrderNum = 0;
    PinJia = 0;
    PinJiaNum = 0;
    minMoney = 10000000;
    head = nullptr;
    rear = nullptr;
    orderhead = nullptr;
    orderrear = nullptr;
    next = nullptr;
    PMhead = nullptr;
    PMrear = nullptr;
    Successful = false;
    New = true;
}

Hotal::Hotal(Hotal &h)
{
    HotalName = h.getHotalName();
    HotalInfo = h.getHotalInfo();
    HotalManagerAccount = h.getHotalManagerAccount();
    HotalTel = h.getHotalTel();
    Area = h.getArea();
    roomTypeNum = h.getroomTypeNum();
    OrderNum = h.getOrderNum();
    minMoney = h.getminMoney();
    PinJia = h.getPinJia();
    PinJiaNum = h.getPinJiaNum();
    head = h.getRoomhead();
    rear = h.getRoomrear();
    orderhead = h.getorderhead();
    orderrear = h.getorderrear();
    PMhead = h.getPMhead();
    PMrear = h.getPMrear();
    New = h.getNew();
    next = nullptr;
}

/* 函数名称：void addRoomType(Room *newType)
 * 函数类型：公有函数
 * 输入参数：Room类指针(待插入的房间链表)
 * 函数功能：在尾巴插入新链表，并更新roomTypeNum
 */
void Hotal::addRoomType(Room *newType)
{
    Room *ptr;
    int min;
    if (head)
    {
        min = minMoney;
    }
    else
    {
        min = newType->getmoneyPerNight();
    }
    for (ptr = newType; ptr != nullptr; ptr = ptr->getnext())
    {
        if (ptr->getmoneyPerNight() < minMoney)
        {
            min = ptr->getmoneyPerNight();
        }
        roomTypeNum += 1;
    }
    for (ptr = newType; ptr->getnext() != nullptr; ptr = ptr->getnext())
    {}
    if (head == nullptr)
    {
        head = newType;
        rear = ptr;
    }
    else
    {
        rear->Changenext(newType);
        rear = ptr;
    }
    minMoney = min;
}

/* 函数名称：void addOrder(HotalOrder *newOrder)
 * 函数类型：公有函数
 * 输入参数：HotalOrder类指针(待插入的订单链表)
 * 函数功能：在头插入新链表，并更新OrderNum
 */
void Hotal::addOrder(HotalOrder *newOrder)
{
    HotalOrder *ptr;
    for (ptr = newOrder; ptr != nullptr; ptr = ptr->getnext())
    {
        OrderNum += 1;
        if (!ptr->getnext())
        {
            break;
        }
    }
    if (orderhead == nullptr)
    {
        orderhead = newOrder;
        orderrear = ptr;
    }
    else
    {
        ptr->changenext(orderhead);
        orderhead = newOrder;
    }
}

void Hotal::addPinJiaMessage(PinJiaMessage *newPinjia)
{
    PinJiaMessage *ptr;
    float Total = PinJia * PinJiaNum;
    for (ptr = newPinjia; ptr != nullptr; ptr = ptr->getnext())
    {
        Total += ptr->getPinJia();
        PinJiaNum += 1;
        if (!ptr->getnext())
        {
            break;
        }
    }
    PinJia = Total / PinJiaNum;
    if (PMhead == nullptr)
    {
        PMhead = newPinjia;
        PMrear = ptr;
    }
    else
    {
        ptr->changenext(PMhead);
        PMhead = newPinjia;
    }
}
