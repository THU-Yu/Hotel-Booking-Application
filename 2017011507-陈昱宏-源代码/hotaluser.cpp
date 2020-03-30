/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：HotalUser.cpp
 * 内容：实现HotalUser类成员函数
 * 版本：version_1.2
 * 作者：陈昱宏
 * 创建日期：2018/07/20
 */
#include "HotalUser.h"


HotalUser::HotalUser(bank_account *&b, QString a/*='\0'*/, QString p/*='\0'*/, QString number/*='\0'*/, QString email/*='\0'*/)
    :bank(b) //构造函数
{
    change_account(a);
    change_password(p);
    phone_number = number;
    email_address = email;
    UserType = "酒店经理";
}

/* 函数名称：void addHotal(Hotal *newHotal)
 * 函数类型：公有函数
 * 输入参数：Hotal类指针(待插入的房间链表)
 * 函数功能：在头插入新链表，并更新HotalNum
 */
void HotalUser::addHotal(Hotal *newHotal)
{
    Hotal *ptr;
    for (ptr = newHotal; ptr != nullptr; ptr = ptr->getHotalnext())
    {
        HotalNum += 1;
        if (!ptr->getHotalnext())
        {
            break;
        }
    }
    if (Hotalhead == nullptr)
    {
        Hotalhead = newHotal;
        Hotalrear = ptr;
    }
    else
    {
        ptr->changeHotalnext(Hotalhead);
        Hotalhead = newHotal;
    }
}
