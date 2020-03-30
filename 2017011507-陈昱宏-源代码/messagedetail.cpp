#include "messagedetail.h"
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>

MessageDetail::MessageDetail(Message *ptr, QWidget *parent)
    :QDialog(parent)
{
    info = new QLabel(tr("讯息详情"));
    info->setAlignment(Qt::AlignCenter);

    user1 = new QLabel(tr("发送者"));
    user1->setAlignment(Qt::AlignLeft);
    user2 = new QLabel("：" + ptr->getsendUser());
    user2->setAlignment(Qt::AlignLeft);

    receive1 = new QLabel(tr("接收者"));
    receive1->setAlignment(Qt::AlignLeft);
    receive2 = new QLabel("：" + ptr->getreceiveUser());
    receive2->setAlignment(Qt::AlignLeft);

    date1 = new QLabel(tr("日期"));
    date1->setAlignment(Qt::AlignLeft);
    date2 = new QLabel("：" + ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss"));
    date2->setAlignment(Qt::AlignLeft);

    message1 = new QLabel(tr("内容"));
    message1->setAlignment(Qt::AlignLeft);
    message2 = new QTextEdit;
    message2->setText(ptr->getmessage());
    message2->setWordWrapMode(QTextOption::WrapAnywhere);
    message2->setReadOnly(true);

    OkButton = new QPushButton("Ok");

    connect(OkButton,SIGNAL(clicked()),this,SLOT(close()));

    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->addWidget(info,0,0,1,5);
    gridlayout->addWidget(user1,1,0,1,2);
    gridlayout->addWidget(user2,1,2,1,3);
    gridlayout->addWidget(receive1,2,0,1,2);
    gridlayout->addWidget(receive2,2,2,1,3);
    gridlayout->addWidget(date1,3,0,1,2);
    gridlayout->addWidget(date2,3,2,1,3);
    gridlayout->addWidget(message1,4,0,1,2);
    gridlayout->addWidget(message2,5,0,1,5);
    gridlayout->addWidget(OkButton,6,1,1,3);

    setLayout(gridlayout);
}
