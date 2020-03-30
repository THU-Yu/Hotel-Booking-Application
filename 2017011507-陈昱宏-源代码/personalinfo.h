#ifndef PERSONALINFO_H
#define PERSONALINFO_H

#include <QWidget>
#include "account.h"
#include "normaluser.h"
#include "hotaluser.h"
#include "platformuser.h"

class QPushButton;
class QLabel;
class QLineEdit;

class PersonalInfo:public QWidget
{
    Q_OBJECT

public:
    PersonalInfo(NormalUser *&Mainaccount2, HotalUser *&Mainaccount3, PlatformUser *&Mainaccount1, QWidget *parent=0);
    QLineEdit* getaccout(){return accountLineEdit;}
    QLineEdit* getpassword(){return passwordLineEdit;}
    QLineEdit* getphoneNumber(){return phone_numberLineEdit;}
    QLineEdit* getEmailAddress(){return email_addressLineEdit;}
    QLineEdit* getBankAccount(){return BankAccountLineEdit;}
    QLineEdit* getBankPassword(){return BankPasswordLineEdit;}
    QLineEdit* getMoney(){return moneyLineEdit;}
    QLabel* getUserType(){return userType;} //获得userType标签
    void changePersonalInfo(NormalUser *&MainAccount1, HotalUser *&MainAccount2, PlatformUser *&MainAccount3);
    ~PersonalInfo();
signals:
    void Change(NormalUser*,HotalUser*);
    void back();
private slots:
    void ChangeSaveEnable();
    void ChangeChangeEnable();
    void Save();
    void Back();
    void Reset();
private:
    QLabel *info; //提示信息标签
    QLabel *account; //账户确认标签
    QLabel *password; //密码确认标签
    QLabel *phone_number; //手机号码确认标签
    QLabel *email_address; //电子邮箱确认标签
    QLabel *BankAccount; //银行卡号确认标签
    QLabel *BankPassword; //银行密码确认标签
    QLabel *money; //银行账户余额确认标签
    QLabel *userType; //用户类型标签
    QPushButton *ChangeButton;
    QPushButton *BackButton;
    QPushButton *SaveButton;
    QPushButton *CancelButton;
    QLineEdit *accountLineEdit; //账户输入
    QLineEdit *passwordLineEdit; //密码输入
    QLineEdit *phone_numberLineEdit; //手机号码输入
    QLineEdit *email_addressLineEdit; //电子邮箱输入
    QLineEdit *BankAccountLineEdit; //银行卡号输入
    QLineEdit *BankPasswordLineEdit; //银行密码输入
    QLineEdit *moneyLineEdit; //银行账户余额输入
    NormalUser *MainAccount1;
    HotalUser *MainAccount2;
    PlatformUser *Mainaccount3;
};

#endif // PERSONALINFO_H
