/*
 * 无特别标注版本的功能为Account.h的version_1.0所添加
 *
 * 档案名：NormalUser.h
 * 内容：移植自Account.h的client类，更名为NormalUser类
 * 版本：version_1.2
 * 作者：陈昱宏
 * 创建日期：2018/07/20
 */

#ifndef NORMALUSER_H
#define NORMALUSER_H

#include "account.h"
#include "hotalorder.h"

class NormalUser:public Account  //NormalUser类定义，单继承自Account
{
    QString phone_number; //用户手机号码
    QString email_address; //用户电子邮箱
    bank_account *bank; //用户银行账户
    QString UserType; //用户类型(version_1.2)
    int OrderNum; //酒店订单数
    HotalOrder *orderhead, *orderrear;  //酒店订单链表的首尾指针
public:
    NormalUser(bank_account *b, QString a='\0', QString p='\0', QString number='\0', QString email='\0'); //构造函数

     //取得属性的函数
    QString getPhoneNumber(){return phone_number;}
    QString getEmailAddress(){return email_address;}
    QString getUserType(){return UserType;}
    bank_account* getbankAccount(){return bank;}
    QString getBankAccount(){return bank->getaccount();}
    QString getBankPassword(){return bank->getpassword();}
    double getmoney(){return bank->getmoney();}
    int getOrderNum(){return OrderNum;}
    HotalOrder* getorderhead(){return orderhead;}
    HotalOrder* getorderrear(){return orderrear;}

    //修改属性的函数
    void changePhoneNumber(const QString &newnumber){phone_number = newnumber;}
    void changeEmailAddress(const QString &newemail){email_address = newemail;}
    void changeOrderNum(int num){OrderNum = num;}
    void changeorderhead(HotalOrder *h){orderhead = h;}
    void changeorderrear(HotalOrder *h){orderrear = h;}
    void changemoney(double m){bank->change_money(m);}

    //增加酒店订单数目
    void addOrder(HotalOrder *newOrder);

    //重载不会用到的纯虚函数
    /*int getHotalNum(){return 0;}
    void changeHotalhead(Hotal *h){}
    void changeHotalrear(Hotal *h){}
    void addHotal(Hotal *newHotal){}*/
};
#endif // NORMALUSER_H
