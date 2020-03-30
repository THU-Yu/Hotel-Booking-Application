#include "personalinfo.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QRegExp>
#include <QValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPalette>
#include <QFont>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>

PersonalInfo::PersonalInfo(NormalUser *&Mainaccount2, HotalUser *&Mainaccount3, PlatformUser *&Mainaccount1, QWidget *parent)
    :MainAccount1(Mainaccount2), MainAccount2(Mainaccount3), Mainaccount3(Mainaccount1), QWidget(parent)
{
    //部件初始化设定
    //开头信息初始化
    info = new QLabel(tr("个人资料"));
    //文字居中对齐
    info->setAlignment(Qt::AlignCenter);

    //account和accountLineEdit初始化
    account = new QLabel(tr("账户名："));
    account->setAlignment(Qt::AlignLeft); //设定左对齐
    accountLineEdit = new QLineEdit;
    //限定只能由英文和数字组成
    QRegExp regx("^[a-zA-Z0-9]+$");
    QValidator *validator1 = new QRegExpValidator(regx, accountLineEdit);
    accountLineEdit->setValidator(validator1);
    //accountLineEdit初始设为只能读
    accountLineEdit->setReadOnly(true);
    //账户名最多16位
    accountLineEdit->setMaxLength(16);
    //设定提示信息
    accountLineEdit->setPlaceholderText(tr("请输入6-16位以内的英文和数字"));

    //password和passwordLineEdit初始化
    password = new QLabel(tr("密码："));
    password->setAlignment(Qt::AlignLeft); //设定左对齐
    passwordLineEdit = new QLineEdit;
    //限定只能由英文和数字组成
    QValidator *validator2 = new QRegExpValidator(regx, passwordLineEdit);
    passwordLineEdit->setValidator(validator2);
    //passwordLineEdit初始设为只能读
    passwordLineEdit->setReadOnly(true);
    //密码最多16位
    passwordLineEdit->setMaxLength(16);
    //设定提示信息
    passwordLineEdit->setPlaceholderText(tr("请输入6-16位以内的英文和数字"));

    //phone_number和phone_numberLineEdit初始化
    phone_number = new QLabel(tr("手机号码："));
    phone_number->setAlignment(Qt::AlignLeft); //设定左对齐
    phone_numberLineEdit = new QLineEdit;
    //限定只能是1开头后面10位数字
    QRegExp regx1("^1[0-9]{10}$");
    QValidator *validator4 = new QRegExpValidator(regx1, phone_numberLineEdit);
    phone_numberLineEdit->setValidator(validator4);
    //phone_numberLineEdit初始设为只能读
    phone_numberLineEdit->setReadOnly(true);
    //手机号码最多11位
    phone_numberLineEdit->setMaxLength(11);

    //email_address和email_addressLineEdit初始化
    email_address = new QLabel(tr("邮箱地址："));
    email_address->setAlignment(Qt::AlignLeft); //设定左对齐
    email_addressLineEdit = new QLineEdit;
    //email_addressLineEdit初始设为只能读
    email_addressLineEdit->setReadOnly(true);

    //BankAccount和BankAccountLineEdit初始化
    BankAccount = new QLabel(tr("银行卡号："));
    BankAccount->setAlignment(Qt::AlignLeft); //设定左对齐
    BankAccountLineEdit = new QLineEdit;
    //限定只能由数字组成
    QRegExp regx2("^[0-9]{19}$");
    QValidator *validator5 = new QRegExpValidator(regx2, BankAccountLineEdit);
    BankAccountLineEdit->setValidator(validator5);
    //BankAccountLineEdit初始设为只能读
    BankAccountLineEdit->setReadOnly(true);
    //银行卡号最多19位
    BankAccountLineEdit->setMaxLength(19);

    //BankPassword和BankPasswordLineEdit初始化
    BankPassword = new QLabel(tr("银行密码："));
    BankPassword->setAlignment(Qt::AlignLeft); //设定左对齐
    BankPasswordLineEdit = new QLineEdit;
    //限定只能由6位数字组成
    QRegExp regx3("^[0-9]{6}$");
    QValidator *validator6 = new QRegExpValidator(regx3, BankPasswordLineEdit);
    BankPasswordLineEdit->setValidator(validator6);
    //BankPasswordLineEdit初始设为只能读
    BankPasswordLineEdit->setReadOnly(true);

    //money和moneyLineEdit初始化
    money = new QLabel(tr("账户余额："));
    money->setAlignment(Qt::AlignLeft); //设定左对齐
    moneyLineEdit = new QLineEdit;
    //限定由0-100000000000的两位小数组成
    QDoubleValidator *pDfValidator = new QDoubleValidator(0.0, 100000000000.0 , 2, moneyLineEdit);
    pDfValidator->setNotation(QDoubleValidator::StandardNotation);
    moneyLineEdit->setValidator(pDfValidator);
    QString m;
    //moneyLineEdit初始设为只能读
    moneyLineEdit->setReadOnly(true);

    userType = new QLabel(tr("用户类型："));
    userType->setAlignment(Qt::AlignLeft);

    //ChangeButton和CancelButton初始化
    ChangeButton = new QPushButton(tr("更改"));
    BackButton = new QPushButton(tr("返回"));

    SaveButton = new QPushButton(tr("保存"));
    SaveButton->setEnabled(false);
    CancelButton = new QPushButton(tr("取消"));
    CancelButton->setEnabled(false);

    connect(ChangeButton,SIGNAL(clicked()),this,SLOT(ChangeSaveEnable()));
    connect(CancelButton,SIGNAL(clicked()),this,SLOT(ChangeChangeEnable()));
    connect(SaveButton,SIGNAL(clicked()),this,SLOT(Save()));
    connect(BackButton,SIGNAL(clicked()),this,SLOT(Back()));

    QFormLayout *formlayout = new QFormLayout;
    formlayout->addRow(account, accountLineEdit);
    formlayout->addRow(password, passwordLineEdit);
    formlayout->addRow(phone_number, phone_numberLineEdit);
    formlayout->addRow(email_address, email_addressLineEdit);
    formlayout->addRow(BankAccount, BankAccountLineEdit);
    formlayout->addRow(BankPassword, BankPasswordLineEdit);
    formlayout->addRow(money, moneyLineEdit);

    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->addWidget(info,0,0,1,5);
    gridlayout->addLayout(formlayout,1,0,7,5);
    gridlayout->addWidget(userType,8,0,1,5);
    gridlayout->addWidget(ChangeButton,9,1,1,2);
    gridlayout->addWidget(BackButton,9,3,1,2);
    gridlayout->addWidget(SaveButton,10,1,1,2);
    gridlayout->addWidget(CancelButton,10,3,1,2);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addLayout(gridlayout);
    setLayout(mainlayout);
}

PersonalInfo::~PersonalInfo()
{

}

void PersonalInfo::changePersonalInfo(NormalUser *&Account1, HotalUser *&Account2, PlatformUser *&Account3)
{
    MainAccount1 = Account1;
    MainAccount2 = Account2;
    Mainaccount3 = Account3;
    QString m;
    if ((MainAccount1))
    {
        accountLineEdit->setText((MainAccount1)->getaccount());
        passwordLineEdit->setText((MainAccount1)->getpassword());
        phone_numberLineEdit->setText((MainAccount1)->getPhoneNumber());
        email_addressLineEdit->setText((MainAccount1)->getEmailAddress());
        BankAccountLineEdit->setText((MainAccount1)->getBankAccount());
        BankPasswordLineEdit->setText((MainAccount1)->getBankPassword());
        moneyLineEdit->setText(m.setNum((MainAccount1)->getmoney(),'f',2));
        userType->setText("用户类型： " + (MainAccount1)->getUserType());
    }
    else if ((MainAccount2))
    {
        accountLineEdit->setText((MainAccount2)->getaccount());
        passwordLineEdit->setText((MainAccount2)->getpassword());
        phone_numberLineEdit->setText((MainAccount2)->getPhoneNumber());
        email_addressLineEdit->setText((MainAccount2)->getEmailAddress());
        BankAccountLineEdit->setText((MainAccount2)->getBankAccount());
        BankPasswordLineEdit->setText((MainAccount2)->getBankPassword());
        moneyLineEdit->setText(m.setNum((MainAccount2)->getmoney(),'f',2));
        userType->setText("用户类型： " + (MainAccount2)->getUserType());
    }
    else
    {
        accountLineEdit->setText((Mainaccount3)->getaccount());
        passwordLineEdit->setText((Mainaccount3)->getpassword());
        phone_numberLineEdit->setText((Mainaccount3)->getPhoneNumber());
        email_addressLineEdit->setText((Mainaccount3)->getEmailAddress());
        BankAccountLineEdit->setText((Mainaccount3)->getBankAccount());
        BankPasswordLineEdit->setText((Mainaccount3)->getBankPassword());
        moneyLineEdit->setText(m.setNum((Mainaccount3)->getmoney(),'f',2));
        userType->setText("用户类型： " + (Mainaccount3)->getUserType());
    }
}


void PersonalInfo::ChangeSaveEnable()
{
    ChangeButton->setEnabled(false);
    BackButton->setEnabled(false);
    SaveButton->setEnabled(true);
    CancelButton->setEnabled(true);
    passwordLineEdit->setReadOnly(false);
    phone_numberLineEdit->setReadOnly(false);
    email_addressLineEdit->setReadOnly(false);
}

void PersonalInfo::ChangeChangeEnable()
{
    if (QMessageBox::warning(NULL,tr("警告"),tr("现在返回未保存资料不会被修改，\n确定要返回吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        ChangeButton->setEnabled(true);
        BackButton->setEnabled(true);
        SaveButton->setEnabled(false);
        CancelButton->setEnabled(false);
        passwordLineEdit->setReadOnly(true);
        phone_numberLineEdit->setReadOnly(true);
        email_addressLineEdit->setReadOnly(true);
        if ((MainAccount1))
        {
            passwordLineEdit->setText((MainAccount1)->getpassword());
            phone_numberLineEdit->setText((MainAccount1)->getPhoneNumber());
            email_addressLineEdit->setText((MainAccount1)->getEmailAddress());
        }
        else if ((MainAccount2))
        {
            passwordLineEdit->setText((MainAccount2)->getpassword());
            phone_numberLineEdit->setText((MainAccount2)->getPhoneNumber());
            email_addressLineEdit->setText((MainAccount2)->getEmailAddress());
        }
        else
        {
            passwordLineEdit->setText((Mainaccount3)->getpassword());
            phone_numberLineEdit->setText((Mainaccount3)->getPhoneNumber());
            email_addressLineEdit->setText((Mainaccount3)->getEmailAddress());
        }
    }
}

void PersonalInfo::Save()
{
    if (passwordLineEdit->text().isEmpty() || passwordLineEdit->text().length() < 6)
    {
        if (passwordLineEdit->text().isEmpty())
        {
            QMessageBox::critical(NULL,tr("错误"),tr("密码未填!\n所有项目都是必填！"),QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(NULL,tr("错误"),tr("密码过短!\n为了账户安全请重新填写！"),QMessageBox::Ok);
        }
        return;
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
        return;
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
        return;
    }
    QMessageBox::information(NULL,tr("保存"),tr("保存成功！"),QMessageBox::Ok,QMessageBox::Ok);
    if ((MainAccount1))
    {
        (MainAccount1)->change_password(passwordLineEdit->text());
        (MainAccount1)->changePhoneNumber(phone_numberLineEdit->text());
        (MainAccount1)->changeEmailAddress(email_addressLineEdit->text());
    }
    else if ((MainAccount2))
    {
        (MainAccount2)->change_password(passwordLineEdit->text());
        (MainAccount2)->changePhoneNumber(phone_numberLineEdit->text());
        (MainAccount2)->changeEmailAddress(email_addressLineEdit->text());
    }
    else
    {
        (Mainaccount3)->change_password(passwordLineEdit->text());
        (Mainaccount3)->changePhoneNumber(phone_numberLineEdit->text());
        (Mainaccount3)->changeEmailAddress(email_addressLineEdit->text());
    }
    QSqlQuery query;
    query.prepare("update User set password = :password, phone_number = :phone_number, email_address = :email_address where account = :account");
    if ((MainAccount1))
    {
        query.bindValue(":password",(MainAccount1)->getpassword());
        query.bindValue(":phone_number",(MainAccount1)->getPhoneNumber());
        query.bindValue(":email_address",(MainAccount1)->getEmailAddress());
        query.bindValue(":account",(MainAccount1)->getaccount());

    }
    else if ((MainAccount2))
    {
        query.bindValue(":password",(MainAccount2)->getpassword());
        query.bindValue(":phone_number",(MainAccount2)->getPhoneNumber());
        query.bindValue(":email_address",(MainAccount2)->getEmailAddress());
        query.bindValue(":account",(MainAccount2)->getaccount());
    }
    else
    {
        query.bindValue(":password",(Mainaccount3)->getpassword());
        query.bindValue(":phone_number",(Mainaccount3)->getPhoneNumber());
        query.bindValue(":email_address",(Mainaccount3)->getEmailAddress());
        query.bindValue(":account",(Mainaccount3)->getaccount());
    }
    query.exec();
    ChangeButton->setEnabled(true);
    BackButton->setEnabled(true);
    SaveButton->setEnabled(false);
    CancelButton->setEnabled(false);
    passwordLineEdit->setReadOnly(true);
    phone_numberLineEdit->setReadOnly(true);
    email_addressLineEdit->setReadOnly(true);
}

void PersonalInfo::Back()
{
    emit back();
}

void PersonalInfo::Reset()
{
    accountLineEdit->setText('\0');
    passwordLineEdit->setText('\0');
    phone_numberLineEdit->setText('\0');
    email_addressLineEdit->setText('\0');
    BankAccountLineEdit->setText('\0');
    BankPasswordLineEdit->setText('\0');
    moneyLineEdit->setText('\0');
    userType->setText("用户类型：");
}
