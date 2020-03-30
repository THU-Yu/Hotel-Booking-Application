/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：HotalUser.h
 * 内容：声明HotalUser类
 * 版本：version_1.2
 * 作者：陈昱宏
 * 创建日期：2018/07/20
 */
#ifndef HOTALUSER_H
#define HOTALUSER_H

#include "account.h"
#include "hotal.h"
#include "hotalorder.h"

class HotalUser:public Account //HotalUser类定义，单继承自Account
{
    QString phone_number; //用户手机号码
    QString email_address; //用户电子邮箱
    bank_account *bank; //用户银行账户
    QString UserType; //用户类型(version_1.2)
    int HotalNum; //酒店数目
    Hotal *Hotalhead, *Hotalrear;  //酒店链表的首尾指针
public:
    HotalUser(bank_account *&b, QString a='\0', QString p='\0', QString number='\0', QString email='\0'); //构造函数

    //取得属性的函数
    QString getPhoneNumber(){return phone_number;}
    QString getEmailAddress(){return email_address;}
    QString getUserType(){return UserType;}
    bank_account* getbankAccount(){return bank;}
    QString getBankAccount(){return bank->getaccount();}
    QString getBankPassword(){return bank->getpassword();}
    double getmoney(){return bank->getmoney();}
    int getHotalNum(){return HotalNum;}

    //修改属性的函数
    void changePhoneNumber(const QString &newnumber){phone_number = newnumber;}
    void changeEmailAddress(const QString &newemail){email_address = newemail;}
    void changeHotalhead(Hotal *h){Hotalhead = h;}
    void changeHotalrear(Hotal *h){Hotalrear = h;}
    void changemoney(double m){bank->change_money(m);}

    //增加酒店数目
    void addHotal(Hotal *newHotal);

    //重载不会用到的纯虚函数
    /*int getOrderNum(){return 0;}
    void changeOrderNum(int num){}
    HotalOrder* getorderhead(){return nullptr;}
    HotalOrder* getorderrear(){return nullptr;}
    void changeorderhead(HotalOrder *h){}
    void changeorderrear(HotalOrder *h){}
    void addOrder(HotalOrder *newOrder){}*/
};
#endif // HOTALUSER_H
