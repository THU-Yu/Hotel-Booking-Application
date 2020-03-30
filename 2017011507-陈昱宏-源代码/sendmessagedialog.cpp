#include "SendMessageDialog.h"
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include <QDateTime>
#include <QGridLayout>

SendMessageDialog::SendMessageDialog(Message *messagehead, QString receiveUser, NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainaccount3, QWidget *parent)
    :Messagehead(messagehead),MainAccount1(Mainaccount1),MainAccount2(Mainaccount2),MainAccount3(Mainaccount3),QDialog(parent)
{
    info = new QLabel(tr("发送消息"));
    info->setAlignment(Qt::AlignCenter);

    receiveUser1 = new QLabel(tr("接收者："));
    receiveUser1->setAlignment(Qt::AlignLeft);
    receiveUser2 = new QLabel(receiveUser);
    receiveUser2->setAlignment(Qt::AlignLeft);

    message = new QLabel(tr("消息内容"));
    message->setAlignment(Qt::AlignLeft);

    messagetext = new QTextEdit;
    messagetext->setWordWrapMode(QTextOption::WrapAnywhere);

    SendButton = new QPushButton(tr("发送"));
    SendButton->setEnabled(false);
    CancelButton = new QPushButton(tr("取消"));

    connect(messagetext,SIGNAL(textChanged()),this,SLOT(EnableSend()));
    connect(SendButton,SIGNAL(clicked()),this,SLOT(SendMessage()));
    connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));

    sent = false;

    QGridLayout *mainlayout = new QGridLayout;
    mainlayout->addWidget(info,0,0,1,5);
    mainlayout->addWidget(receiveUser1,1,0,1,2);
    mainlayout->addWidget(receiveUser2,1,2,1,3);
    mainlayout->addWidget(message,2,0,1,2);
    mainlayout->addWidget(messagetext,3,0,1,5);
    mainlayout->addWidget(SendButton,4,0,1,2);
    mainlayout->addWidget(CancelButton,4,3,1,2);

    setLayout(mainlayout);
}

void SendMessageDialog::EnableSend()
{
    SendButton->setEnabled(true);
}

bool SendMessageDialog::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("取消"),tr("还未成功发送消息，\n确定要退出吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SendMessageDialog::SendMessage()
{
    if (QMessageBox::question(NULL,tr("发送消息"),tr("确定要发送消息吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        if (MainAccount1)
        {
            Message *newmessage = new Message(MainAccount1->getaccount(),receiveUser2->text(),messagetext->toPlainText(),nullptr,new QDateTime(QDateTime::currentDateTime()));
            Message *ptr;
            for (ptr = Messagehead;ptr->getnext() != nullptr;ptr = ptr->getnext())
            {}
            ptr->changenext(newmessage);
        }
        else if (MainAccount2)
        {
            Message *newmessage = new Message(MainAccount2->getaccount(),receiveUser2->text(),messagetext->toPlainText(),nullptr,new QDateTime(QDateTime::currentDateTime()));
            Message *ptr;
            for (ptr = Messagehead;ptr->getnext() != nullptr;ptr = ptr->getnext())
            {}
            ptr->changenext(newmessage);
        }
        else if (MainAccount3)
        {
            Message *newmessage = new Message(MainAccount3->getaccount(),receiveUser2->text(),messagetext->toPlainText(),nullptr,new QDateTime(QDateTime::currentDateTime()));
            Message *ptr;
            for (ptr = Messagehead;ptr->getnext() != nullptr;ptr = ptr->getnext())
            {}
            ptr->changenext(newmessage);
        }
        sent = true;
        close();
    }
}

void SendMessageDialog::closeEvent(QCloseEvent *event)
{
    if (sent)
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
