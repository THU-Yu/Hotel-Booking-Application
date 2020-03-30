/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：Account.h
 * 内容：声明基类Account类（账户信息）及其派生类bank_account类
 * 版本：version_1.0
 * 作者：陈昱宏
 * 创建日期：2018/07/18
 *
 * 版本：version_1.2
 * 修改部分：移除client类、声明纯虚函数
 * 修改者：陈昱宏（上版本作者：陈昱宏）
 * 修改日期：2018/07/20
 */
#ifndef ACCOUNT_H
#define ACCOUNT_H

//Account类定义
#include <iostream>
#include <QString>
#include "hotalorder.h"
#include "hotal.h"

class bank_account;

class Account //账户类定义
{
    QString account; //账户账号
    QString password; //账户密码
public:
    Account(QString a='\0', QString p='\0') :account(a), password(p) {} //构造函数
    Account(Account &a):account(a.account), password(a.password){} //复制构造函数
    void change_account(QString a){account = a;} //修改账号
    void change_password(QString p){password = p;} //修改密码
    bool password_same(QString p) const; //判定密码是否正确
    QString getaccount() const; //得到账户账号
    QString getpassword() const; //得到账户密码

    //声明纯虚函数(version_1.2)
    virtual double getmoney(){return 0;}
    virtual void change_money(double f){}
    virtual QString getPhoneNumber(){}
    virtual QString getEmailAddress(){return '\0';}
    virtual bank_account* getbank_account(){return nullptr;}
    QString getBankAccount(){return '\0';}
    QString getBankPassword(){return '\0';}
    virtual QString getUserType(){return '\0';}
    virtual int getOrderNum(){return 0;}
    virtual int getHotalNum(){return 0;}
    virtual HotalOrder* getorderhead(){return nullptr;}
    virtual HotalOrder* getorderrear(){return nullptr;}
    virtual void changePhoneNumber(const QString &newnumber){}
    virtual void changeEmailAddress(const QString &newemail){}
    virtual void changeOrderNum(int num){}
    virtual void changeorderhead(HotalOrder *h){}
    virtual void changeorderrear(HotalOrder *h){}
    virtual void changeHotalhead(Hotal *h){}
    virtual void changeHotalrear(Hotal *h){}
    virtual void addOrder(HotalOrder *newOrder){}
    virtual void addHotal(Hotal *newHotal){}
};

class bank_account :public Account //银行账户类定义，单继承自Account（公有继承）
{
    double money; //账户余额
public:
    bank_account(double m, QString a='\0', QString p='\0'); //构造函数
    bank_account(bank_account &bank); //复制构造函数
    double getmoney(){return money;} //取得余额
    void change_money(double f){money = f;} //修改余额
    void pay_money(float f, bank_account bank) //付钱给另一个账户
    {
        money -= f;
        bank.change_money(bank.getmoney() + f);
    }

    //重载不会用到的纯虚函数(version_1.2)
    QString getPhoneNumber(){return '\0';}
    QString getEmailAddress(){return '\0';}
    QString getUserType(){return '\0';}
    int getOrderNum(){return 0;}
    int getHotalNum(){return 0;}
    HotalOrder* getorderhead(){return nullptr;}
    HotalOrder* getorderrear(){return nullptr;}
    void changePhoneNumber(const QString &newnumber){}
    void changeEmailAddress(const QString &newemail){}
    void changeOrderNum(int num){}
    void changeorderhead(HotalOrder *h){}
    void changeorderrear(HotalOrder *h){}
    void changeHotalhead(Hotal *h){}
    void changeHotalrear(Hotal *h){}
    void addOrder(HotalOrder *newOrder){}
    void addHotal(Hotal *newHotal){}
};

#endif // ACCOUNT_H
