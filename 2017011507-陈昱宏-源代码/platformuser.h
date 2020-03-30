#ifndef PLATFORMUSER_H
#define PLATFORMUSER_H

#include "account.h"

class PlatformUser:public Account
{
    QString phone_number; //用户手机号码
    QString email_address; //用户电子邮箱
    bank_account *bank; //用户银行账户
    QString UserType; //用户类型
public:
    PlatformUser(bank_account *b, QString a='\0', QString p='\0', QString number='\0', QString email='\0'); //构造函数
    PlatformUser(){}

    //取得属性的函数
    QString getPhoneNumber(){return phone_number;}
    QString getEmailAddress(){return email_address;}
    QString getUserType(){return UserType;}
    bank_account* getbankAccount(){return bank;}
    QString getBankAccount(){return bank->getaccount();}
    QString getBankPassword(){return bank->getpassword();}
    double getmoney(){return bank->getmoney();}

    void changePhoneNumber(const QString &newnumber){phone_number = newnumber;}
    void changeEmailAddress(const QString &newemail){email_address = newemail;}
    void changemoney(double m){bank->change_money(m);}
};

#endif // PLATFORMUSER_H
