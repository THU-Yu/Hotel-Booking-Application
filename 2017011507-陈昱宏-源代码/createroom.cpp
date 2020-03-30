#include "createroom.h"
#include <QLabel>
#include <QDate>
#include <QLineEdit>
#include <QPushButton>
#include <QRegExp>
#include <QValidator>
#include <QMessageBox>
#include <QGridLayout>
#include <QCloseEvent>
#include <QDebug>

CreateRoom::CreateRoom(Hotal *hotal, Room *roomhead, QWidget *parent)
    :thishotal(hotal),Roomhead(roomhead),successful(false),QDialog(parent)
{
    QRegExp regx("^[0-9\.]+$");

    info = new QLabel(tr("创建新房型"));
    info->setAlignment(Qt::AlignCenter);

    RoomType1 = new QLabel(tr("房间类型："));
    RoomType1->setAlignment(Qt::AlignLeft);
    RoomType2 = new QLineEdit;

    TotalNum1 = new QLabel(tr("房间总数"));
    TotalNum1->setAlignment(Qt::AlignLeft);
    TotalNum2 = new QLineEdit;
    QValidator *validator1 = new QRegExpValidator(regx, TotalNum2);
    TotalNum2->setValidator(validator1);

    MoneyPerNight1 = new QLabel(tr("每晚价格："));
    MoneyPerNight1->setAlignment(Qt::AlignLeft);
    MoneyPerNight2 = new QLineEdit;
    QValidator *validator2 = new QRegExpValidator(regx, MoneyPerNight2);
    MoneyPerNight2->setValidator(validator2);

    CreateButton = new QPushButton(tr("创建"));
    CreateButton->setEnabled(false);
    CancelButton = new QPushButton(tr("取消"));

    connect(RoomType2,SIGNAL(textEdited(QString)),this,SLOT(EnableClick()));
    connect(TotalNum2,SIGNAL(textEdited(QString)),this,SLOT(EnableClick()));
    connect(MoneyPerNight2,SIGNAL(textEdited(QString)),this,SLOT(EnableClick()));
    connect(CreateButton,SIGNAL(clicked()),this,SLOT(Create()));
    connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));

    QGridLayout *mainlayout = new QGridLayout;
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->addWidget(info,0,0,1,5);
    mainlayout->addWidget(RoomType1,1,0,1,2);
    mainlayout->addWidget(RoomType2,1,2,1,3);
    mainlayout->addWidget(TotalNum1,2,0,1,2);
    mainlayout->addWidget(TotalNum2,2,2,1,3);
    mainlayout->addWidget(MoneyPerNight1,3,0,1,2);
    mainlayout->addWidget(MoneyPerNight2,3,2,1,3);
    mainlayout->addWidget(CreateButton,4,0,1,2);
    mainlayout->addWidget(CancelButton,4,3,1,2);

    setLayout(mainlayout);
}

bool CreateRoom::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("取消？"),tr("现在退出房间将不会完成创建，\n确定要退出吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CreateRoom::EnableClick()
{
    if ((!(RoomType2->text().isEmpty())) && (!(TotalNum2->text().isEmpty())) && (!(MoneyPerNight2->text().isEmpty())))
    {
        CreateButton->setEnabled(true);
    }
    else
    {
        CreateButton->setEnabled(false);;
    }
}

void CreateRoom::Create()
{
    if (QMessageBox::question(NULL,tr("新增房型"),tr("是否新增房型？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        Room *ptr;
        QDate date = QDate::currentDate();
        if (thishotal->getRoomhead() != nullptr)
        {
            for(ptr = thishotal->getRoomhead();ptr->getnext() != nullptr;ptr = ptr->getnext())
            {
                if (ptr->getType() == RoomType2->text())
                {
                    QMessageBox::warning(NULL,tr("错误"),tr("创建失败！\n房型已存在！"),QMessageBox::Ok,QMessageBox::Ok);
                    successful = true;
                    close();
                    return;
                }
            }
            for (;date <= QDate::currentDate().addDays(31);date = date.addDays(1))
            {
                float totalnum = TotalNum2->text().toFloat();
                float moneypernight = MoneyPerNight2->text().toFloat();
                Room *newroom = new Room(thishotal->getHotalName(),RoomType2->text(),(int)totalnum,(int)totalnum,new QDate(date),moneypernight);
                thishotal->addRoomType(newroom);
            }
        }
        else
        {
            for (;date <= QDate::currentDate().addDays(31);date = date.addDays(1))
            {
                float totalnum = TotalNum2->text().toFloat();
                float moneypernight = MoneyPerNight2->text().toFloat();
                Room *newroom = new Room(thishotal->getHotalName(),RoomType2->text(),(int)totalnum,(int)totalnum,new QDate(date),moneypernight);
                if (date == QDate::currentDate())
                {
                    thishotal->addRoomType(newroom);
                    ptr = thishotal->getRoomhead();
                }
                else
                {
                    ptr->Changenext(newroom);
                    ptr = ptr->getnext();
                }
            }
        }

        for(ptr = Roomhead;ptr->getnext() != nullptr;ptr = ptr->getnext())
        {}
        date = QDate::currentDate();
        for (;date <= QDate::currentDate().addDays(31);date = date.addDays(1))
        {
            float totalnum = TotalNum2->text().toFloat();
            float moneypernight = MoneyPerNight2->text().toFloat();
            Room *newroom = new Room(thishotal->getHotalName(),RoomType2->text(),(int)totalnum,(int)totalnum,new QDate(date),moneypernight);
            ptr->Changenext(newroom);
            ptr = ptr->getnext();
        }
        successful = true;
        close();
    }
}

void CreateRoom::closeEvent(QCloseEvent *event)
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
