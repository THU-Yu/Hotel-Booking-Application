/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：RegisterConfirmDialog.cpp
 * 内容：实现RegisterConfirmDialog类（注册确认界面）
 * 版本：version_1.1
 * 作者：陈昱宏
 * 创建日期：2018/07/19
 */
#include "registerconfirmdialog.h"
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCloseEvent>

RegisterConfirmDialog::RegisterConfirmDialog(QString _account/*='\0'*/, QString _password/*='\0'*/,
                                             QString _phone_number/*='\0'*/, QString _emailAddress/*='\0'*/,
                                             QString _bankAccount/*='\0'*/, QString _bankPassword/*='\0'*/,
                                             QString _money/*='\0'*/, QString _userType/*='\0'*/, QWidget *parent/*=0*/)
    :_Account(_account), _Password(_password), _Phone_number(_phone_number), _EmailAddress(_emailAddress)
    , _BankAccount(_bankAccount), _BankPassword(_bankPassword), _Money(_money), UserType(_userType), QDialog(parent) //构造函数实现
{
    //界面大小规定
    resize(640,400);

    //部件初始化设定
    info = new QLabel("个人资料确认");
    info->setAlignment(Qt::AlignCenter);

    //account初始化
    account = new QLabel("账户名：" + _account, this);
    account->setAlignment(Qt::AlignLeft); //设定左对齐

    //password初始化
    password = new QLabel("密码：" + _password, this);
    password->setAlignment(Qt::AlignLeft); //设定左对齐

    //phone_number初始化
    phone_number = new QLabel("手机号码：" + _phone_number, this);
    phone_number->setAlignment(Qt::AlignLeft); //设定左对齐

    //email_address初始化
    email_address = new QLabel("邮箱地址：" + _emailAddress, this);
    email_address->setAlignment(Qt::AlignLeft); //设定左对齐

    //BankAccount初始化
    BankAccount = new QLabel("银行卡号：" + _bankAccount, this);
    BankAccount->setAlignment(Qt::AlignLeft); //设定左对齐

    //BankPassword初始化
    BankPassword = new QLabel("银行密码：" + _bankPassword, this);
    BankPassword->setAlignment(Qt::AlignLeft); //设定左对齐

    //money初始化
    money = new QLabel("账户余额：" + _money, this);
    money->setAlignment(Qt::AlignLeft); //设定左对齐

    //userType初始化
    userType = new QLabel("用户类型：" + UserType, this);
    userType->setAlignment(Qt::AlignLeft); //设定左对齐

    //CorrectButton和WrongButton初始化
    CorrectButton = new QPushButton(tr("正确"), this);
    //CorrectButton按Enter键可以代替点击，边框出现蓝边
    CorrectButton->setDefault(true);
    WrongButton = new QPushButton(tr("有错"), this);
    //WrongButton按Enter键可以代替点击，边框出现蓝边
    WrongButton->setDefault(true);

    //连接信号槽
    connect(WrongButton,SIGNAL(clicked()),this,SLOT(hide()));
    connect(CorrectButton,SIGNAL(clicked()),this,SLOT(CloseRegister()));

    //水平加垂直布局
    QHBoxLayout *lastlayout = new QHBoxLayout;
    lastlayout->addStretch(3);
    lastlayout->addWidget(CorrectButton);
    lastlayout->addStretch(1);
    lastlayout->addWidget(WrongButton);
    lastlayout->addStretch(3);

    QVBoxLayout *Centerlayout = new QVBoxLayout;
    Centerlayout->setAlignment(Qt::AlignCenter);
    Centerlayout->addStretch(2);
    Centerlayout->addWidget(info);
    Centerlayout->addWidget(account);
    Centerlayout->addWidget(password);
    Centerlayout->addWidget(phone_number);
    Centerlayout->addWidget(email_address);
    Centerlayout->addWidget(BankAccount);
    Centerlayout->addWidget(BankPassword);
    Centerlayout->addWidget(money);
    Centerlayout->addWidget(userType);
    Centerlayout->addStretch(1);
    Centerlayout->addLayout(lastlayout);
    Centerlayout->addStretch(2);

    QHBoxLayout *mainlayout = new QHBoxLayout;
    mainlayout->addStretch();
    mainlayout->addLayout(Centerlayout);
    mainlayout->addStretch();

    //设定窗口的Layout
    setLayout(mainlayout);
    //设定窗口的标题
    setWindowTitle(tr("资料确认"));
}

/* 函数名称：bool ContinueToClose()
 * 函数类型：公有函数
 * 函数功能：显示关闭提示讯息，返回是否关闭
 * 输出参数：bool值
 */
bool RegisterConfirmDialog::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("返回"),tr("亲，你还没确认资料\n确定要关闭吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

RegisterConfirmDialog::~RegisterConfirmDialog() //析构函数实现
{

}

/* 函数名称：void CloseRegister()
 * 函数类型：槽函数
 * 函数功能：显示注册成功窗口，发送closeRegister()信号
 */
void RegisterConfirmDialog::CloseRegister()
{
    if (QMessageBox::information(NULL,tr("恭喜~"),tr("成功注册~"),QMessageBox::Ok) == QMessageBox::Ok)
    {
        QSqlQuery query;
        query.prepare("insert into User values (?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(_Account);
        query.addBindValue(_Password);
        query.addBindValue(_Phone_number);
        query.addBindValue(_EmailAddress);
        query.addBindValue(_BankAccount);
        query.addBindValue(_BankPassword);
        query.addBindValue(_Money);
        query.addBindValue(UserType);
        query.exec();
        this->hide();
        emit closeRegister();
    }
}

/* 函数名称：void closeEvent(QCloseEvent *event)
 * 函数类型：保护函数
 * 函数功能：捕捉关闭事件，调用ContinueToClose()，决定是否接收事件
 */
void RegisterConfirmDialog::closeEvent(QCloseEvent *event)
{
    if (ContinueToClose())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
