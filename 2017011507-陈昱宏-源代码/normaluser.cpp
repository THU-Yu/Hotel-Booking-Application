/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：NormalUser.cpp
 * 内容：实现NormalUser类成员函数
 * 版本：version_1.2
 * 作者：陈昱宏
 * 创建日期：2018/07/20
 */
#include "NormalUser.h"

NormalUser::NormalUser(bank_account *b, QString a/*='\0'*/, QString p/*='\0'*/, QString number/*='\0'*/, QString email/*='\0'*/)
    :bank(b) //构造函数
{
    change_account(a);
    change_password(p);
    phone_number = number;
    email_address = email;
    UserType = "一般用户";
    orderhead = nullptr;
    OrderNum = 0;
}

/* 函数名称：void addOrder(HotalOrder *newOrder)
 * 函数类型：公有函数
 * 输入参数：HotalOrder类指针(待插入的订单链表)
 * 函数功能：在头插入新链表，并更新OrderNum
 */
void NormalUser::addOrder(HotalOrder *newOrder)
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
