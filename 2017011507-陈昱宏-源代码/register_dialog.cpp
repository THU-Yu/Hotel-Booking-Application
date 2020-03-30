/*
 * 档案名：Register_Dialog.cpp
 * 内容：实现Register_Dialog类（注册界面）
 * 版本：version_1.0
 * 作者：陈昱宏
 * 创建日期：2018/07/18
 *
 * 版本：version_1.1
 * 修改部分：增加新信号槽、增加关闭提示、增加注册信息确认窗口
 * 修改者：陈昱宏（上版本作者：陈昱宏）
 * 修改日期：2018/07/19
 */

#include "Register_Dialog.h"
#include "registerconfirmdialog.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QRegExp>
#include <QValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QGridLayout>
#include <QMessageBox>
#include <QPalette>
#include <QFont>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCloseEvent>

Register_Dialog::Register_Dialog(RegisterConfirmDialog *confirm, QWidget *parent/*=0*/) //构造函数实现
    :ConfirmDialog(confirm), QDialog(parent) //增加RegisterConfirmDialog *参数(version_1.1)
{
    //界面大小规定
    resize(640,400);

    //部件初始化设定
    //开头信息初始化
    info = new QLabel(tr("注册新用户"), this);
    //文字居中对齐
    info->setAlignment(Qt::AlignCenter);

    //account和accountLineEdit初始化
    account = new QLabel(tr("<font color = red><font size=8mm>*</font></font>账户名："), this);
    account->setAlignment(Qt::AlignLeft); //设定左对齐
    accountLineEdit = new QLineEdit(this);
    //限定只能由英文和数字组成
    QRegExp regx("^[a-zA-Z0-9]+$");
    QValidator *validator1 = new QRegExpValidator(regx, accountLineEdit);
    accountLineEdit->setValidator(validator1);
    //账户名最多16位
    accountLineEdit->setMaxLength(16);
    //设定提示信息
    accountLineEdit->setPlaceholderText(tr("请输入6-16位以内的英文和数字"));

    //password和passwordLineEdit初始化
    password = new QLabel(tr("<font color = red><font size=8mm>*</font></font>密码："), this);
    password->setAlignment(Qt::AlignLeft); //设定左对齐
    passwordLineEdit = new QLineEdit(this);
    //限定只能由英文和数字组成
    QValidator *validator2 = new QRegExpValidator(regx, passwordLineEdit);
    passwordLineEdit->setValidator(validator2);
    //密码最多16位
    passwordLineEdit->setMaxLength(16);
    //输入时加密显示
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    //设定提示信息
    passwordLineEdit->setPlaceholderText(tr("请输入6-16位以内的英文和数字"));

    //checkpassword和checkpasswordLineEdit初始化（与password一样的设定）
    checkpassword = new QLabel(tr("<font color = red><font size=8mm>*</font></font>确认密码："), this);
    checkpassword->setAlignment(Qt::AlignLeft);
    checkpasswordLineEdit = new QLineEdit(this);
    QValidator *validator3 = new QRegExpValidator(regx, checkpasswordLineEdit);
    checkpasswordLineEdit->setValidator(validator3);
    checkpasswordLineEdit->setMaxLength(16);
    checkpasswordLineEdit->setEchoMode(QLineEdit::Password);

    //phone_number和phone_numberLineEdit初始化
    phone_number = new QLabel(tr("<font color = red><font size=8mm>*</font></font>手机号码："), this);
    phone_number->setAlignment(Qt::AlignLeft); //设定左对齐
    phone_numberLineEdit = new QLineEdit(this);
    //限定只能是1开头后面10位数字
    QRegExp regx1("^1[0-9]{10}$");
    QValidator *validator4 = new QRegExpValidator(regx1, phone_numberLineEdit);
    phone_numberLineEdit->setValidator(validator4);
    //手机号码最多11位
    phone_numberLineEdit->setMaxLength(11);

    //email_address和email_addressLineEdit初始化
    email_address = new QLabel(tr("<font color = red><font size=8mm>*</font></font>邮箱地址："), this);
    email_address->setAlignment(Qt::AlignLeft); //设定左对齐
    email_addressLineEdit = new QLineEdit(this);

    //BankAccount和BankAccountLineEdit初始化
    BankAccount = new QLabel(tr("<font color = red><font size=8mm>*</font></font>银行卡号："), this);
    BankAccount->setAlignment(Qt::AlignLeft); //设定左对齐
    BankAccountLineEdit = new QLineEdit(this);
    //限定只能由数字组成
    QRegExp regx2("^[0-9]{19}$");
    QValidator *validator5 = new QRegExpValidator(regx2, BankAccountLineEdit);
    BankAccountLineEdit->setValidator(validator5);
    //银行卡号最多19位
    BankAccountLineEdit->setMaxLength(19);

    //BankPassword和BankPasswordLineEdit初始化
    BankPassword = new QLabel(tr("<font color = red><font size=8mm>*</font></font>银行密码："), this);
    BankPassword->setAlignment(Qt::AlignLeft); //设定左对齐
    BankPasswordLineEdit = new QLineEdit(this);
    //限定只能由6位数字组成
    QRegExp regx3("^[0-9]{6}$");
    QValidator *validator6 = new QRegExpValidator(regx3, BankPasswordLineEdit);
    BankPasswordLineEdit->setValidator(validator6);
    //输入时加密显示
    BankPasswordLineEdit->setEchoMode(QLineEdit::Password);

    //money和moneyLineEdit初始化
    money = new QLabel(tr("<font color = red><font size=8mm>*</font></font>账户余额："), this);
    money->setAlignment(Qt::AlignLeft); //设定左对齐
    moneyLineEdit = new QLineEdit(this);
    //限定由0-100000000000的两位小数组成
    QDoubleValidator *pDfValidator = new QDoubleValidator(0.0, 100000000000.0 , 2, moneyLineEdit);
    pDfValidator->setNotation(QDoubleValidator::StandardNotation);
    moneyLineEdit->setValidator(pDfValidator);
    //moneyLineEdit初始设为只能读
    moneyLineEdit->setReadOnly(true);
    //设定提示信息
    moneyLineEdit->setPlaceholderText(tr("请先输入银行卡号"));

    //单选框初始化
    UserType1 = new QRadioButton(tr("一般用户"), this);
    UserType1->setChecked(true);
    UserType2 = new QRadioButton(tr("酒店经理"), this);

    //RegisterButton和CancelButton初始化
    RegisterButton = new QPushButton(tr("注册"), this);
    //RegisterButton按Enter键可以代替点击，边框出现蓝边
    RegisterButton->setDefault(true);
    //RegisterButton初始设为不可点击
    RegisterButton->setEnabled(false);
    CancelButton = new QPushButton(tr("取消"), this);
    //CancelButton按Enter键可以代替点击，边框出现蓝边
    CancelButton->setDefault(true);

    //连接信号槽
    connect(CancelButton,SIGNAL(clicked()),this,SLOT(BackToWelcome()));
    connect(accountLineEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enableClick(const QString&)));
    connect(BankAccountLineEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enableWrite(const QString&)));
    //连接信号槽(version_1.1)
    connect(RegisterButton,SIGNAL(clicked()),this,SLOT(Register()));
    connect(ConfirmDialog,SIGNAL(closeRegister()),this,SLOT(SuccessfulRegister()));

    //网格布局
    QGridLayout *gridlayout = new QGridLayout(this);
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->addWidget(info,0,0,1,5);
    gridlayout->addWidget(account,1,0,1,1);
    gridlayout->addWidget(accountLineEdit,1,1,1,3);
    gridlayout->addWidget(password,2,0,1,1);
    gridlayout->addWidget(passwordLineEdit,2,1,1,3);
    gridlayout->addWidget(checkpassword,3,0,1,1);
    gridlayout->addWidget(checkpasswordLineEdit,3,1,1,3);
    gridlayout->addWidget(phone_number,4,0,1,1);
    gridlayout->addWidget(phone_numberLineEdit,4,1,1,3);
    gridlayout->addWidget(email_address,5,0,1,1);
    gridlayout->addWidget(email_addressLineEdit,5,1,1,3);
    gridlayout->addWidget(BankAccount,6,0,1,1);
    gridlayout->addWidget(BankAccountLineEdit,6,1,1,3);
    gridlayout->addWidget(BankPassword,7,0,1,1);
    gridlayout->addWidget(BankPasswordLineEdit,7,1,1,3);
    gridlayout->addWidget(money,8,0,1,1);
    gridlayout->addWidget(moneyLineEdit,8,1,1,3);
    gridlayout->addWidget(UserType1,9,0,1,2);
    gridlayout->addWidget(UserType2,9,2,1,2);
    gridlayout->addWidget(RegisterButton,10,0,1,1);
    gridlayout->addWidget(CancelButton,10,2,1,1);

    //设定窗口的Layout
    setLayout(gridlayout);
    //设定窗口的标题
    setWindowTitle(tr("注册"));
}

/* 函数名称：bool ContinueToClose()
 * 函数类型：公有函数
 * 函数功能：显示关闭提示讯息，返回是否关闭
 * 输出参数：bool值
 * (version_1.1)
 */
bool Register_Dialog::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("退出？"),tr("亲，真的不注册一个账号吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Register_Dialog::~Register_Dialog() //析构函数实现
{

}

/* 函数名称：void BackToWelcome()
 * 函数类型：槽函数
 * 函数功能：开启一个QMessageBox，若点击Yes，则关闭Register_Dialog，发送ShowWelcome()信号
 *
 * 修改内容：直接关闭，由void closeEvent(QCloseEvent *event)去执行原功能
 * (version_1.1)
 */
void Register_Dialog::BackToWelcome()
{
    this->close();
}

/* 函数名称：void enableclick(const QString &text)
 * 函数类型：槽函数
 * 输入参数：QString类常引用
 * 函数功能：若传入参数不为空，则将RegisterButton设为可点击
 */
void Register_Dialog::enableClick(const QString &s)
{
    RegisterButton->setEnabled(!s.isEmpty());
}

/* 函数名称：void enableWrite(const QString &text)
 * 函数类型：槽函数
 * 输入参数：QString类常引用
 * 函数功能：若传入参数不为空，则将moneyLineEdit设为可写
 */
void Register_Dialog::enableWrite(const QString &s)
{
    moneyLineEdit->setReadOnly(s.isEmpty());
}

/* 函数名称：void SuccessfulRegister()
 * 函数类型：槽函数
 * 函数功能：将窗口隐藏，还原LineEdit和RadioButton的初值，并发出ShowWelcome()
 * (version_1.1)
 */
void Register_Dialog::SuccessfulRegister()
{

    this->hide();
    accountLineEdit->setText("\0");
    passwordLineEdit->setText("");
    checkpasswordLineEdit->setText("");
    phone_numberLineEdit->setText("\0");
    email_addressLineEdit->setText("\0");
    BankAccountLineEdit->setText("\0");
    BankPasswordLineEdit->setText("\0");
    moneyLineEdit->setText("\0");
    UserType1->setChecked(true);
    UserType2->setChecked(false);
    emit ShowWelcome();
}

/* 函数名称：void Register()
 * 函数类型：槽函数
 * 函数功能：判定是否填写正确资料，若正确，则将所填内容传给ConfirmDialog，并显示ConfirmDialog
 * (version_1.1)
 */
void Register_Dialog::Register()
{
    bool Same = false;
    QSqlQuery query;
    query.prepare("select account from User");
    if (query.exec())
    {
        while(query.next())
        {
            if (accountLineEdit->text() == query.value(0))
            {
                Same = true;
            }
        }
    }

    if (accountLineEdit->text().length() < 6)
    {
        QMessageBox::critical(NULL,tr("错误"),tr("账号过短!\n请重新填写！"),QMessageBox::Ok);
    }
    else if (Same)
    {
        QMessageBox::critical(NULL,tr("错误"),tr("账号重复!\n请重新填写！"),QMessageBox::Ok);
    }
    else if (passwordLineEdit->text().isEmpty() || passwordLineEdit->text().length() < 6)
    {
        if (passwordLineEdit->text().isEmpty())
        {
            QMessageBox::critical(NULL,tr("错误"),tr("密码未填!\n所有项目都是必填！"),QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(NULL,tr("错误"),tr("密码过短!\n为了账户安全请重新填写！"),QMessageBox::Ok);
        }
    }
    else if (checkpasswordLineEdit->text().isEmpty())
    {
        QMessageBox::critical(NULL,tr("错误"),tr("请确认密码!\n"),QMessageBox::Ok);
    }
    else if (checkpasswordLineEdit->text() != passwordLineEdit->text())
    {
        QMessageBox::critical(NULL,tr("错误"),tr("密码不符!"),QMessageBox::Ok);
    }
    else if (phone_numberLineEdit->text().isEmpty() || phone_numberLineEdit->text().length() < 11)
    {
        if (phone_numberLineEdit->text().isEmpty())
        {
            QMessageBox::critical(NULL,tr("错误"),tr("手机号未填!\n所有项目都是必填！"),QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(NULL,tr("错误"),tr("手机号长度不足!\n请填写正确资料！"),QMessageBox::Ok);
        }
    }
    else if (email_addressLineEdit->text().isEmpty()
             || !email_addressLineEdit->text().endsWith(".com") //是否为.com结尾
             || email_addressLineEdit->text().indexOf("@") == -1) //"@"是否为email_address的子串
    {
        if (email_addressLineEdit->text().isEmpty())
        {
            QMessageBox::critical(NULL,tr("错误"),tr("电子邮箱未填!\n所有项目都是必填！"),QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(NULL,tr("错误"),tr("电子邮箱格式不正确!\n请填写正确资料！"),QMessageBox::Ok);
        }
    }
    else if (BankAccountLineEdit->text().isEmpty())
    {
        QMessageBox::critical(NULL,tr("错误"),tr("银行卡号未填!\n所有项目都是必填！"),QMessageBox::Ok);
    }
    else if (BankPasswordLineEdit->text().isEmpty() || BankPasswordLineEdit->text().length() < 6)
    {
        if (BankPasswordLineEdit->text().isEmpty())
        {
            QMessageBox::critical(NULL,tr("错误"),tr("银行密码未填!\n所有项目都是必填！"),QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(NULL,tr("错误"),tr("银行密码格式不正确!\n请填写正确资料！"),QMessageBox::Ok);
        }
    }
    else if (moneyLineEdit->text().isEmpty())
    {
        QMessageBox::critical(NULL,tr("错误"),tr("账户余额不得为空!\n所有项目都是必填！"),QMessageBox::Ok);
    }
    else if(moneyLineEdit->text() == "0"
            || moneyLineEdit->text() == "0.0"
            || moneyLineEdit->text() == "0.00" )
    {
        QMessageBox::critical(NULL,tr("错误"),tr("账户余额不足!"),QMessageBox::Ok);
    }
    else
    {
        QString UserType;

        if (UserType1->isChecked())
        {
            UserType = UserType1->text();
        }
        else
        {
            UserType = UserType2->text();
        }
        ConfirmDialog->getaccout()->setText("账户名：" + accountLineEdit->text());
        ConfirmDialog->getpassword()->setText("密码：" + passwordLineEdit->text());
        ConfirmDialog->getphoneNumber()->setText("手机号码：" + phone_numberLineEdit->text());
        ConfirmDialog->getEmailAddress()->setText("邮箱地址：" + email_addressLineEdit->text());
        ConfirmDialog->getBankAccount()->setText("银行卡号：" + BankAccountLineEdit->text());
        ConfirmDialog->getBankPassword()->setText("银行密码：" + BankPasswordLineEdit->text());
        ConfirmDialog->getMoney()->setText("账户余额：" + moneyLineEdit->text());
        ConfirmDialog->getUserType()->setText("用户类型：" + UserType);
        ConfirmDialog->set_Account(accountLineEdit->text());
        ConfirmDialog->set_Password(passwordLineEdit->text());
        ConfirmDialog->set_Phone_number(phone_numberLineEdit->text());
        ConfirmDialog->set_EmailAddress(email_addressLineEdit->text());
        ConfirmDialog->set_BankAccount(BankAccountLineEdit->text());
        ConfirmDialog->set_BankPassword(BankPasswordLineEdit->text());
        ConfirmDialog->set_Money(moneyLineEdit->text());
        ConfirmDialog->setUserType(UserType);
        ConfirmDialog->exec();
    }
}

/* 函数名称：void closeEvent(QCloseEvent *event)
 * 函数类型：保护函数
 * 函数功能：捕捉关闭事件，调用ContinueToClose()，决定是否接收事件和重置初值
 * (version_1.1)
 */
void Register_Dialog::closeEvent(QCloseEvent *event)
{
    if (ContinueToClose())
    {
        event->accept();
        emit ShowWelcome();
        accountLineEdit->setText("\0");
        passwordLineEdit->setText("");
        checkpasswordLineEdit->setText("");
        phone_numberLineEdit->setText("\0");
        email_addressLineEdit->setText("\0");
        BankAccountLineEdit->setText("\0");
        BankPasswordLineEdit->setText("\0");
        moneyLineEdit->setText("\0");
        UserType1->setChecked(true);
        UserType2->setChecked(false);
    }
    else
    {
        event->ignore();
    }
}
