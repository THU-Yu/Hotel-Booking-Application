#include "writepinjia.h"
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QSpinBox>
#include <QMessageBox>
#include <QDateTime>
#include <QGridLayout>
#include <QDebug>

WritePinJia::WritePinJia(Hotal *hotal,Message *messagehead, PinJiaMessage *pinjiahead,QString receiveUser, NormalUser *Mainaccount1, QWidget *parent)
    :thishotal(hotal),Messagehead(messagehead),PinJiahead(pinjiahead),MainAccount1(Mainaccount1),QDialog(parent)
{
    info = new QLabel(tr("发送消息"));
    info->setAlignment(Qt::AlignCenter);

    HotalName1 = new QLabel(tr("酒店名："));
    HotalName1->setAlignment(Qt::AlignLeft);
    HotalName2 = new QLabel(receiveUser);
    HotalName2->setAlignment(Qt::AlignLeft);

    pinjia1 = new QLabel(tr("评价分数"));
    pinjia1->setAlignment(Qt::AlignLeft);
    pinjia2 = new QSpinBox;
    pinjia2->setRange(0,5);
    pinjia2->setValue(3);

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
    mainlayout->addWidget(HotalName1,1,0,1,2);
    mainlayout->addWidget(HotalName2,1,2,1,3);
    mainlayout->addWidget(pinjia1,2,0,1,2);
    mainlayout->addWidget(pinjia2,2,2,1,1);
    mainlayout->addWidget(message,3,0,1,2);
    mainlayout->addWidget(messagetext,4,0,1,5);
    mainlayout->addWidget(SendButton,5,0,1,2);
    mainlayout->addWidget(CancelButton,5,3,1,2);

    setLayout(mainlayout);
}

void WritePinJia::EnableSend()
{
    SendButton->setEnabled(true);
}

bool WritePinJia::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("取消"),tr("还未成功填写评价，\n确定要退出吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void WritePinJia::SendMessage()
{
    if (QMessageBox::question(NULL,tr("填写评价"),tr("确定要填写评价吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        Message *newmessage = new Message(MainAccount1->getaccount(),HotalName2->text(),messagetext->toPlainText(),nullptr,new QDateTime(QDateTime::currentDateTime()));
        Message *ptr;
        for (ptr = Messagehead;ptr->getnext() != nullptr;ptr = ptr->getnext())
        {}
        ptr->changenext(newmessage);
        PinJiaMessage *ptr1;
        for(ptr1 = PinJiahead;(ptr1->getUser() != MainAccount1->getaccount()) || (ptr1->getHotalName() != HotalName2->text());ptr1 = ptr1->getnext())
        {
            if ((ptr1->getnext() == nullptr) && ((ptr1->getUser() != MainAccount1->getaccount()) || (ptr1->getHotalName() != HotalName2->text())))
            {
                ptr1 = ptr1->getnext();
                break;
            }
        }
        if (ptr1 != nullptr)
        {
            int num = 1;
            float pingjia = ptr1->getPinJia();
            for (ptr = ptr1->getmessage();ptr->getnext() != nullptr;ptr = ptr->getnext())
            {
                num ++;
            }
            ptr1->changePinJia((pingjia * num + pinjia2->value()) / (num + 1));
        }
        else
        {
            Message *newmessage1 = new Message(MainAccount1->getaccount(),HotalName2->text(),messagetext->toPlainText(),nullptr,new QDateTime(QDateTime::currentDateTime()));
            PinJiaMessage *newPinJia = new PinJiaMessage(HotalName2->text(),pinjia2->value(),MainAccount1->getaccount(),newmessage1);
            for(ptr1 = PinJiahead;;ptr1 = ptr1->getnext())
            {
                if (ptr1->getnext() == nullptr)
                {
                    break;
                }
            }
            ptr1->changenext(newPinJia);
        }
        float totalpinji = thishotal->getPinJia() * thishotal->getPinJiaNum();
        for (ptr1 = thishotal->getPMhead();(ptr1->getUser() != MainAccount1->getaccount());ptr1 = ptr1->getnext())
        {
            if ((ptr1->getnext() == nullptr) && (ptr1->getUser() != MainAccount1->getaccount()))
            {
                ptr1 = ptr1->getnext();
                break;
            }
        }
        if (ptr1 != nullptr)
        {
            Message *newmessage2 = new Message(MainAccount1->getaccount(),HotalName2->text(),messagetext->toPlainText(),nullptr,new QDateTime(QDateTime::currentDateTime()));
            int num = 1;
            float pingjia = ptr1->getPinJia();
            for (ptr = ptr1->getmessage();ptr->getnext() != nullptr;ptr = ptr->getnext())
            {
                num ++;
            }
            totalpinji = totalpinji -  ptr1->getPinJia();
            ptr1->changePinJia(((pingjia * num + pinjia2->value()) / (num + 1)));
            ptr->changenext(newmessage2);
            totalpinji = totalpinji + ptr1->getPinJia();
            totalpinji = totalpinji / thishotal->getPinJiaNum();
            thishotal->changePinJia(totalpinji);
        }
        else
        {
            Message *newmessage2 = new Message(MainAccount1->getaccount(),HotalName2->text(),messagetext->toPlainText(),nullptr,new QDateTime(QDateTime::currentDateTime()));
            PinJiaMessage *newPinJia1 = new PinJiaMessage(HotalName2->text(),pinjia2->value(),MainAccount1->getaccount(),newmessage2);
            thishotal->addPinJiaMessage(newPinJia1);
        }

        sent = true;
        close();
    }
}

void WritePinJia::closeEvent(QCloseEvent *event)
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
