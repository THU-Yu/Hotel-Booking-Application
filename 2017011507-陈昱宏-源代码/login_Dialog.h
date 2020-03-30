/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：Login_Dialog.h
 * 内容：声明Login_Dialog类（登入界面）
 * 版本：version_1.0
 * 作者：陈昱宏
 * 创建日期：2018/07/18
 *
 * 版本：version_1.1
 * 修改部分：增加新信号槽、增加关闭提示
 * 修改者：陈昱宏（上版本作者：陈昱宏）
 * 修改日期：2018/07/19
 */

#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include "Account.h"
#include "normaluser.h"
#include "hotaluser.h"
#include "platformuser.h"
#include <QDialog>

class QLabel;
class QPushButton;
class QLineEdit;
class QRadioButton;

class Login_Dialog:public QDialog //Login_Dialog类声明，单继承自QDialog类
{
    Q_OBJECT

public:
    Login_Dialog(NormalUser *&Mainaccount2, HotalUser *&Mainaccount3, PlatformUser *&Mainaccount1, QWidget *parent = 0); //构造函数
    bool ContinueToClose(); //判定是否确认关闭(version_1.1)
    ~Login_Dialog(); //析构函数
signals:
    void ShowWelcome(); //返回Welcome界面的信号
    void successful(NormalUser*&); //成功登入的信号(version_1.1)
    void successful(HotalUser*&);
    void successful(PlatformUser*&);
protected:
    void closeEvent(QCloseEvent *event); //捕捉关闭事件(version_1.1)
private slots:
    void BackToWelcome(); //接收CancelButton的clicked()信号
    void enablelogin(const QString &s); //接收accountLineEdit的textChanged(QString)信号
    void Login(); //接收LoginButton的clicked()信号(version_1.1)
private:
    QLabel *account; //账号标签
    QLabel *password; //密码标签
    QPushButton *LoginButton; //登入按钮
    QPushButton *CancelButton; //取消按钮
    QLineEdit *accountLineEdit; //账号输入
    QLineEdit *passwordLineEdit; //密码输入
    QRadioButton *UserType1; //一般用户单选框
    QRadioButton *UserType2; //酒店经理单选框
    QRadioButton *UserType3; //平台管理单选框
    NormalUser *MainAccount1;
    HotalUser *MainAccount2;
    PlatformUser *MainAccount3;
};

#endif // LOGIN_DIALOG_H
