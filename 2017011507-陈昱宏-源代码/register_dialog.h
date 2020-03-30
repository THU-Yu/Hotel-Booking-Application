/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：Register_Dialog.h
 * 内容：声明Register_Dialog类（登入界面）
 * 版本：version_1.0
 * 作者：陈昱宏
 * 创建日期：2018/07/18
 *
 * 版本：version_1.1
 * 修改部分：增加新信号槽、增加关闭提示、增加注册信息确认窗口
 * 修改者：陈昱宏（上版本作者：陈昱宏）
 * 修改日期：2018/07/19
 */

#ifndef REGISTER_DIALOG_H
#define REGISTER_DIALOG_H

#include <QDialog>
#include <QString>

class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class RegisterConfirmDialog;

class Register_Dialog:public QDialog //声明Register_Dialog类，单继承自QDialog类
{
    Q_OBJECT

public:
    Register_Dialog(RegisterConfirmDialog *confirm, QWidget *parent=0); //构造函数；增加RegisterConfirmDialog *参数(version_1.1)
    bool ContinueToClose(); //判定是否确认关闭(version_1.1)
    ~Register_Dialog(); //析构函数
signals:
    void ShowWelcome(); //返回Welcome界面的信号
protected:
    void closeEvent(QCloseEvent *event); //捕捉关闭事件(version_1.1)
private slots:
    void BackToWelcome(); //接收CancelButton的clicked()信号
    void enableClick(const QString &s); //接收accountLineEdit的textChanged(const QString&)信号
    void enableWrite(const QString &s); //接收BankAccountLineEdit的textChanged(const QString&)信号
    void Register(); //接收RegisterButton的clicked()信号(version_1.1)
    void SuccessfulRegister(); //接收ConfirmDialog的closeRegister()信号(version_1.1)
private:
    QLabel *info; //开头信息标签
    QLabel *account; //账户标签
    QLabel *password; //密码标签
    QLabel *checkpassword; //确认密码标签
    QLabel *phone_number; //手机号码标签
    QLabel *email_address; //电子邮箱标签
    QLabel *BankAccount; //银行卡号标签
    QLabel *BankPassword; //银行密码标签
    QLabel *money; //银行账户余额标签
    QLineEdit *accountLineEdit; //账户输入
    QLineEdit *passwordLineEdit; //密码输入
    QLineEdit *checkpasswordLineEdit; //确认密码输入
    QLineEdit *phone_numberLineEdit; //手机号码输入
    QLineEdit *email_addressLineEdit; //电子邮箱输入
    QLineEdit *BankAccountLineEdit; //银行卡号输入
    QLineEdit *BankPasswordLineEdit; //银行密码输入
    QLineEdit *moneyLineEdit; //银行账户余额输入
    QPushButton *CancelButton; //取消按钮
    QPushButton *RegisterButton; //注册按钮
    QRadioButton *UserType1; //一般用户单选框
    QRadioButton *UserType2; //酒店管理单选框
    RegisterConfirmDialog *ConfirmDialog; //注册信息确认窗口(version_1.1)
};

#endif // REGISTER_DIALOG_H
