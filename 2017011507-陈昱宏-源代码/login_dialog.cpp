/*
 * 档案名：Login_Dialog.cpp
 * 内容：实现Login_Dialog类（登入界面）
 * 版本：version_1.0
 * 作者：陈昱宏
 * 创建日期：2018/07/18
 *
 * 版本：version_1.1
 * 修改部分：增加新信号槽、增加关闭提示
 * 修改者：陈昱宏（上版本作者：陈昱宏）
 * 修改日期：2018/07/19
 */

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QRegExp>
#include <QValidator>
#include <QGridLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "Login_Dialog.h"
#include "NormalUser.h"
#include "hotaluser.h"
#include "platformuser.h"

Login_Dialog::Login_Dialog(NormalUser *&Mainaccount2, HotalUser *&Mainaccount3, PlatformUser *&Mainaccount1, QWidget *parent/*=0*/) //构造函数实现
    :MainAccount1(Mainaccount2), MainAccount2(Mainaccount3), MainAccount3(Mainaccount1), QDialog(parent)
{
    //界面大小规定
    resize(640,400);

    //部件初始化设定
    //account和accountLineEdit初始化
    account = new QLabel(tr("账户："), this);
    account->setAlignment(Qt::AlignLeft); //设定左对齐
    accountLineEdit = new QLineEdit(this);
    //限定只能由英文和数字组成
    QRegExp regx("^[a-zA-Z0-9]+$");
    QValidator *validator1 = new QRegExpValidator(regx, accountLineEdit);
    accountLineEdit->setValidator(validator1);
    //账户名最多16位
    accountLineEdit->setMaxLength(16);

    //password和passwordLineEdit初始化
    password = new QLabel(tr("密码："), this);
    password->setAlignment(Qt::AlignLeft); //设定左对齐
    passwordLineEdit = new QLineEdit(this);
    //限定只能由英文和数字组成
    QValidator *validator2 = new QRegExpValidator(regx, passwordLineEdit);
    passwordLineEdit->setValidator(validator2);
    //密码最多16位
    passwordLineEdit->setMaxLength(16);
    //输入时加密显示
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    //LoginButton和CancelButton初始化
    LoginButton = new QPushButton(tr("登入"), this);
    //LoginButton按Enter键可以代替点击，边框出现蓝边
    LoginButton->setDefault(true);
    //LoginButton初始设为不可点击
    LoginButton->setEnabled(false);
    CancelButton = new QPushButton(tr("取消"), this);
    //CancelButton按Enter键可以代替点击，边框出现蓝边
    CancelButton->setDefault(true);

    //单选框初始化
    UserType1 = new QRadioButton(tr("一般用户"), this);
    UserType1->setChecked(true);
    UserType2 = new QRadioButton(tr("酒店经理"), this);
    UserType3 = new QRadioButton(tr("平台管理"), this);

    //连接信号槽
    connect(CancelButton,SIGNAL(clicked()),this,SLOT(BackToWelcome()));
    connect(accountLineEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enablelogin(const QString&)));
    //连接信号槽(version_1.1)
    connect(LoginButton,SIGNAL(clicked()),this,SLOT(Login()));

    //网格布局
    QGridLayout *gridlayout = new QGridLayout(this);
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->addWidget(account,0,0,1,1);
    gridlayout->addWidget(accountLineEdit,0,1,1,4);
    gridlayout->addWidget(password,1,0,1,1);
    gridlayout->addWidget(passwordLineEdit,1,1,1,4);
    gridlayout->addWidget(UserType1,2,0,1,2);
    gridlayout->addWidget(UserType2,2,2,1,2);
    gridlayout->addWidget(UserType3,2,4,1,2);
    gridlayout->addWidget(LoginButton,3,0,1,2);
    gridlayout->addWidget(CancelButton,3,3,1,2);

    //设定Login_Dialog的Layout
    setLayout(gridlayout);
    //设定窗口标题
    setWindowTitle(tr("登入"));
}

/* 函数名称：bool ContinueToClose()
 * 函数类型：公有函数
 * 函数功能：显示关闭提示讯息，返回是否关闭
 * 输出参数：bool值
 * (version_1.1)
 */
bool Login_Dialog::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("返回Welcome？"),tr("亲，你还没完成登入\n确定要返回吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Login_Dialog::~Login_Dialog() //析构函数定义
{

}

/* 函数名称：void BackToWelcome()
 * 函数类型：槽函数
 * 函数功能：关闭Login_Dialog，发送ShowWelcome()信号
 */
void Login_Dialog::BackToWelcome()
{
    this->close();
}

/* 函数名称：void enablelogin(const QString &text)
 * 函数类型：槽函数
 * 输入参数：QString类常引用
 * 函数功能：若传入参数不为空，则将LoginButton设为可点击
 */
void Login_Dialog::enablelogin(const QString &text)
{
    LoginButton->setEnabled(!text.isEmpty());
}

/* 函数名称：void Login()
 * 函数类型：槽函数
 * 函数功能：判定是否有填写密码，若填写了密码，则发出successful()信号
 * (version_1.1)
 */
void Login_Dialog::Login()
{
    if (passwordLineEdit->text().isEmpty())
    {
        QMessageBox::critical(NULL,tr("错误"),tr("密码未填！\n请重新登入！"),QMessageBox::Ok);
        return;
    }

    bool exist = false;
    bool rightpassword = false;
    bool righttype = false;
    QSqlQuery query;
    query.exec("select * from User");
    while (query.next())
    {
        if (query.value(0).toString() == accountLineEdit->text())
        {
            if (query.value(1).toString() == passwordLineEdit->text())
            {
                if (UserType1->isChecked())
                {
                    if (query.value(7).toString() == UserType1->text())
                    {
                        bank_account *b = new bank_account(query.value(6).toDouble(), query.value(4).toString(), query.value(5).toString());
                        NormalUser *User = new NormalUser(b,query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),
                                                          query.value(3).toString());
                        MainAccount1 = User;
                        emit successful(User);
                        righttype = true;
                    }
                }
                else if (UserType2->isChecked())
                {
                    if (query.value(7).toString() == UserType2->text())
                    {
                        bank_account *b = new bank_account(query.value(6).toDouble(), query.value(4).toString(), query.value(5).toString());
                        HotalUser *User = new HotalUser(b,query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),
                                                          query.value(3).toString());
                        MainAccount2 = User;
                        emit successful(User);
                        righttype = true;
                    }
                }
                else
                {
                    if (query.value(7).toString() == UserType3->text())
                    {
                        bank_account *b = new bank_account(query.value(6).toDouble(), query.value(4).toString(), query.value(5).toString());
                        PlatformUser *User = new PlatformUser(b,query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),
                                                          query.value(3).toString());
                        MainAccount3 = User;
                        emit successful(User);
                        righttype = true;
                    }
                }
                rightpassword = true;
            }
            exist = true;
        }
    }
    if (!exist)
    {
        QMessageBox::warning(NULL,"登入失败","账户不存在！\n请先注册",QMessageBox::Yes,QMessageBox::Yes);
        accountLineEdit->setText("\0");
        passwordLineEdit->setText("\0");
        UserType1->setChecked(true);
        UserType2->setChecked(false);
        UserType3->setChecked(false);
    }
    else if (!rightpassword)
    {
        QMessageBox::warning(NULL,"登入失败","密码错误！\n请重新登入",QMessageBox::Yes,QMessageBox::Yes);
        accountLineEdit->setText("\0");
        passwordLineEdit->setText("\0");
        UserType1->setChecked(true);
        UserType2->setChecked(false);
        UserType3->setChecked(false);
    }
    else if (!righttype)
    {
        QMessageBox::warning(NULL,"登入失败","用户类型错误！\n请重新登入",QMessageBox::Yes,QMessageBox::Yes);
        accountLineEdit->setText("\0");
        passwordLineEdit->setText("\0");
        UserType1->setChecked(true);
        UserType2->setChecked(false);
        UserType3->setChecked(false);
    }
    else
    {
        this->hide();
        accountLineEdit->setText("\0");
        passwordLineEdit->setText("\0");
        UserType1->setChecked(true);
        UserType2->setChecked(false);
        UserType3->setChecked(false);
    }
}

/* 函数名称：void closeEvent(QCloseEvent *event)
 * 函数类型：保护函数
 * 函数功能：捕捉关闭事件，调用ContinueToClose()，决定是否接收事件
 * (version_1.1)
 */
void Login_Dialog::closeEvent(QCloseEvent *event)
{
    if (ContinueToClose())
    {
        event->accept();
        emit ShowWelcome();
        accountLineEdit->setText("\0");
        passwordLineEdit->setText("\0");
        UserType1->setChecked(true);
        UserType2->setChecked(false);
        UserType3->setChecked(false);
    }
    else
    {
        event->ignore();
    }
}
