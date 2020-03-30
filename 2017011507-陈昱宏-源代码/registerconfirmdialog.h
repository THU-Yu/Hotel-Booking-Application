/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：RegisterConfirmDialog.h
 * 内容：声明RegisterConfirmDialog类（注册确认界面）
 * 版本：version_1.1
 * 作者：陈昱宏
 * 创建日期：2018/07/19
 */
#ifndef REGISTERCONFIRMDIALOG_H
#define REGISTERCONFIRMDIALOG_H

#include <QDialog>
#include <QString>

class QPushButton;
class QLabel;

class RegisterConfirmDialog:public QDialog //声明RegisterConfirmDialog类，单继承自QDialog类
{
    Q_OBJECT

public:
    RegisterConfirmDialog(QString _account="\0", QString _password="\0", QString _phone_number="\0",
                          QString _emailAddress="\0", QString _bankAccount="\0", QString _bankPassword="\0",
                          QString _money="\0", QString UserType="\0", QWidget *parent=0); //构造函数
    QLabel* getaccout(){return account;} //获得account标签
    QLabel* getpassword(){return password;} //获得password标签
    QLabel* getphoneNumber(){return phone_number;} //获得phone_number标签
    QLabel* getEmailAddress(){return email_address;} //获得email_address标签
    QLabel* getBankAccount(){return BankAccount;} //获得BankAccount标签
    QLabel* getBankPassword(){return BankPassword;} //获得BankPassword标签
    QLabel* getMoney(){return money;} //获得money标签
    QLabel* getUserType(){return userType;} //获得userType标签
    void set_Account(QString s){_Account = s;}
    void set_Password(QString s){_Password = s;}
    void set_Phone_number(QString s){_Phone_number = s;}
    void set_EmailAddress(QString s){_EmailAddress = s;}
    void set_BankAccount(QString s){_BankAccount = s;}
    void set_BankPassword(QString s){_BankPassword = s;}
    void set_Money(QString s){_Money = s;}
    void setUserType(QString s){UserType = s;}
    bool ContinueToClose(); //判定是否确认关闭
    ~RegisterConfirmDialog(); //析构函数
signals:
    void closeRegister(); //关闭Register_Dialog的信号
protected:
    void closeEvent(QCloseEvent *event); //捕捉关闭事件
private slots:
    void CloseRegister(); //接收CorrectButton的clicked()信号
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
    QPushButton *CorrectButton; //正确按钮
    QPushButton *WrongButton; //错误按钮
    QString _Account;
    QString _Password;
    QString _Phone_number;
    QString _EmailAddress;
    QString _BankAccount;
    QString _BankPassword;
    QString _Money;
    QString UserType;
};

#endif // REGISTERCONFIRMDIALOG_H
