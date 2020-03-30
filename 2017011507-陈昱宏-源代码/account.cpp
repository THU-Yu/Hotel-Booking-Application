/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：Account.cpp
 * 内容：实现基类Account类（账户信息）及其派生类的功能
 * 版本：version_1.0
 * 作者：陈昱宏
 * 创建日期：2018/07/18
 *
 * 版本：version_1.2
 * 修改部分：移除client类
 * 修改者：陈昱宏（上版本作者：陈昱宏）
 * 修改日期：2018/07/20
 */
#include <iostream>
#include <QString>
#include "Account.h"

//Account类成员函数的实现
/*函数功能：判定密码是否一样
* 输入参数：string类待判定的密码
* 输出参数：bool型，true代表相同
*/
bool Account::password_same(QString p) const
{
    if (password == p)
    {
        return true;
    }

    return false;
}

/*函数功能：得到Account类对象的account值
* 输出参数：string类account值
*/
QString Account::getaccount() const
{
    return this->account;
}

/*函数功能：得到Account类对象的password值
* 输出参数：string类password值
*/
QString Account::getpassword() const
{
    return this->password;
}

//bank_account类成员函数实现
/*构造函数*/
bank_account::bank_account(double m, QString a/*='\0'*/, QString p/*='\0'*/):money(m)
{
    change_account(a);
    change_password(p);
}

/*复制构造函数*/
bank_account::bank_account(bank_account &bank)
{
    money = bank.getmoney();
    change_account(bank.getaccount());
    change_password(bank.getpassword());
}
