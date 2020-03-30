#include "paymoney.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>

PayMoney::PayMoney(HotalOrder *order,QString Paytype,NormalUser *Mainaccount1,HotalUser *Mainaccount2,PlatformUser *Mainaccount3,QWidget *parent)
    :Order(order),MainAccount1(Mainaccount1),MainAccount2(Mainaccount2),MainAccount3(Mainaccount3),successful(false),QDialog(parent)
{
    info = new QLabel(tr("支付"));
    info->setAlignment(Qt::AlignCenter);

    PayType = new QLabel("支付类型：" + Paytype);
    PayType->setAlignment(Qt::AlignLeft);

    QString money;
    if (MainAccount3 && (!Order->getPayOrNot()))
    {
        money1 = new QLabel("总金额：0元");
    }
    else
    {
        money1 = new QLabel("总金额：" + money.setNum(Order->getTotalmoney(),'f',2) + "元");
    }
    money1->setAlignment(Qt::AlignLeft);

    BankAccount1 = new QLabel(tr("银行账户："));
    BankAccount1->setAlignment(Qt::AlignLeft);
    BankAccount2 = new QLineEdit;
    if (MainAccount1)
    {
        BankAccount2->setText(MainAccount1->getBankAccount());
    }
    else if (MainAccount2)
    {
        BankAccount2->setText(MainAccount2->getBankAccount());
    }
    else if (MainAccount3)
    {
        BankAccount2->setText(MainAccount3->getBankAccount());
    }
    BankAccount2->setReadOnly(true);

    BankPassword1 = new QLabel(tr("银行密码"));
    BankPassword1->setAlignment(Qt::AlignLeft);
    BankPassword2 = new QLineEdit;
    BankPassword2->setPlaceholderText("请输入银行卡密码");
    BankPassword2->setEchoMode(QLineEdit::Password);

    PayButton = new QPushButton(tr("支付"));
    CancelButton = new QPushButton(tr("取消"));

    connect(PayButton,SIGNAL(clicked()),this,SLOT(Pay()));
    connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));

    QGridLayout *mainlayout = new QGridLayout;
    mainlayout->setAlignment(Qt::AlignLeft);
    mainlayout->addWidget(info,0,0,1,5);
    mainlayout->addWidget(PayType,1,0,1,5);
    mainlayout->addWidget(money1,2,0,1,5);
    mainlayout->addWidget(BankAccount1,3,0,1,2);
    mainlayout->addWidget(BankAccount2,3,2,1,3);
    mainlayout->addWidget(BankPassword1,4,0,1,2);
    mainlayout->addWidget(BankPassword2,4,2,1,3);
    mainlayout->addWidget(PayButton,5,0,1,2);
    mainlayout->addWidget(CancelButton,5,3,1,2);

    setLayout(mainlayout);
}

bool PayMoney::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("取消？"),tr("现在退出支付将不会完成，\n确定要退出吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PayMoney::Pay()
{
    if (MainAccount1)
    {
        if (BankPassword2->text() != MainAccount1->getBankPassword())
        {
            QMessageBox::warning(NULL,tr("密码错误"),tr("密码错误！\n请重新输入！"),QMessageBox::Ok,QMessageBox::Ok);
            BankPassword2->setText("");
        }
        else if (MainAccount1->getmoney() < Order->getTotalmoney())
        {
            QMessageBox::warning(NULL,tr("余额不足"),tr("余额不足无法支付！"),QMessageBox::Ok,QMessageBox::Ok);
        }
        else
        {
            if (QMessageBox::question(NULL,tr("支付"),tr("确定要支付吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes) == QMessageBox::Yes)
            {
                accept();
                successful = true;
                Order->changePayOrNot();

                double money;
                money = Order->getTotalmoney();

                QSqlQuery query;
                query.prepare("select account, bankMoney from User");
                query.exec();
                while (query.next())
                {
                    if (query.value(0).toString() == MainAccount1->getaccount())
                    {
                        money = query.value(1).toDouble() - money;
                        break;
                    }
                }

                query.prepare("update User set bankMoney = :money where account = :account");
                query.bindValue(":money",money);
                query.bindValue(":account",MainAccount1->getaccount());
                query.exec();

                MainAccount1->changemoney(money);

                query.prepare("select account, bankMoney from User");
                query.exec();
                while (query.next())
                {
                    if (query.value(0).toString() == "2017011507")
                    {
                        money = query.value(1).toDouble() + Order->getTotalmoney();
                        break;
                    }
                }
                query.prepare("update User set bankMoney = :money where account = :account");
                query.bindValue(":money",money);
                query.bindValue(":account","2017011507");
                query.exec();
            }
        }
    }
    else if (MainAccount2)
    {
        if (BankPassword2->text() != MainAccount2->getBankPassword())
        {
            QMessageBox::warning(NULL,tr("密码错误"),tr("密码错误！\n请重新输入！"),QMessageBox::Ok,QMessageBox::Ok);
            BankPassword2->setText("");
        }
        else if (MainAccount2->getmoney() < Order->getTotalmoney())
        {
            QMessageBox::warning(NULL,tr("余额不足"),tr("余额不足无法支付！"),QMessageBox::Ok,QMessageBox::Ok);
        }
        else
        {
            if (QMessageBox::question(NULL,tr("支付"),tr("确定要支付吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes) == QMessageBox::Yes)
            {
                accept();
                successful = true;
            }
        }
    }
    else if (MainAccount3)
    {
        if (BankPassword2->text() != MainAccount3->getBankPassword())
        {
            QMessageBox::warning(NULL,tr("密码错误"),tr("密码错误！\n请重新输入！"),QMessageBox::Ok,QMessageBox::Ok);
            BankPassword2->setText("");
        }
        else if (MainAccount3->getmoney() < Order->getTotalmoney())
        {
            QMessageBox::warning(NULL,tr("余额不足"),tr("余额不足无法支付！"),QMessageBox::Ok,QMessageBox::Ok);
        }
        else
        {
            if (QMessageBox::question(NULL,tr("支付"),tr("确定要支付吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes) == QMessageBox::Yes)
            {
                accept();
                successful = true;
            }
        }
    }
}

void PayMoney::closeEvent(QCloseEvent *event)
{
    if (successful)
    {
        event->accept();
    }
    else if (ContinueToClose())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
