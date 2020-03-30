/*
 * 档案名：WelcomeWindow.cpp
 * 内容：实现WelcomeWindow类（欢迎界面）
 * 版本：version_1.0
 * 作者：陈昱宏
 * 创建日期：2018/07/18
 *
 * 版本：version_1.1
 * 修改部分：布局重新修改、增加新信号槽、增加关闭提示
 * 修改者：陈昱宏（上版本作者：陈昱宏）
 * 修改日期：2018/07/19
 */
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QMessageBox>
#include <QDate>
#include <QDateTime>
#include <QCloseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "WelcomeWindow.h"
#include <QDebug>

WelcomeWindow::WelcomeWindow(NormalUser *Mainaccount2, HotalUser *Mainaccount3, PlatformUser *Mainaccount1, Hotal *h, HotalOrder *o, Room *r, Message *m, PinJiaMessage *p, QWidget *parent/*=0*/) //构造函数实现
    :MainAccount1(Mainaccount2), MainAccount2(Mainaccount3), MainAccount3(Mainaccount1),Hotalhead(h),Orderhead(o),Roomhead(r),
      Messagehead(m),PinJiahead(p), QMainWindow(parent)
{
    //界面大小设定
    resize(640,400);
    //不可最大化，并设定最大尺寸
    setMaximumSize(640,400);

    //欢迎信息初始化
    label = new QLabel(tr("欢迎来到C&W酒店预定系统~"), this);
    label->setAlignment(Qt::AlignCenter); //设定置中对齐

    //四个QPushButton初始化
    loginbutton = new QPushButton(tr("登入"), this);
    registerbutton = new QPushButton(tr("注册"), this);
    quitbutton = new QPushButton(tr("退出"), this);
    vistorbutton = new QPushButton(tr("访客"), this);

    //连接信号槽
    connect(loginbutton,SIGNAL(clicked()),this,SLOT(Login()));
    connect(registerbutton,SIGNAL(clicked()),this,SLOT(Rigistr()));
    connect(quitbutton,SIGNAL(clicked()),this,SLOT(Quit()));
    //连接信号槽(version_1.1)
    connect(vistorbutton,SIGNAL(clicked()),this,SLOT(Vistor()));

    //网格加垂直布局(version_1.1)(原为水平加垂直布局)
    QGridLayout *griduplayout = new QGridLayout(this);
    griduplayout->addWidget(loginbutton,0,0,1,1);
    griduplayout->addWidget(registerbutton,0,1,1,1);

    QGridLayout *griddownlayout = new QGridLayout(this);
    griddownlayout->addWidget(vistorbutton,0,0,1,1);
    griddownlayout->addWidget(quitbutton,0,1,1,1);

    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->addStretch(2);
    mainlayout->addWidget(label);
    mainlayout->addStretch(1);
    mainlayout->addLayout(griduplayout);
    mainlayout->addLayout(griddownlayout);
    mainlayout->addStretch(2);

    //将部件放在QMainWindow的CentralWidget区域
    QWidget *widget = new QWidget(this);
    widget->setLayout(mainlayout);
    setCentralWidget(widget);
    //设定窗口标题
    setWindowTitle(tr("C&W酒店预定"));
}

/* 函数名称：bool ContinueToClose()
 * 函数类型：公有函数
 * 函数功能：显示关闭提示讯息，返回是否关闭
 * 输出参数：bool值
 * (version_1.1)
 */
bool WelcomeWindow::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("退出？"),tr("亲，确定要退出吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

WelcomeWindow::~WelcomeWindow() //析构函数实现
{

}

/* 函数名称：void Login()
 * 函数类型：槽函数
 * 函数功能：隐藏WelcomeWindow，发送ShowLoginDialog()信号
 */
void WelcomeWindow::Login()
{
    this->hide();
    emit showLoginDialog();
}

/* 函数名称：void Register()
 * 函数类型：槽函数
 * 函数功能：隐藏WelcomeWindow，发送ShowRegisterDialog()信号
 */
void WelcomeWindow::Rigistr()
{
    this->hide();
    emit showRegisterDialog();
}

/* 函数名称：void Vistor()
 * 函数类型：槽函数
 * 函数功能：隐藏WelcomeWindow，发送showVistorDialog()信号
 * (version_1.1)
 */
void WelcomeWindow::Vistor()
{
    this->hide();
    emit showVistorDialog();
}

/* 函数名称：void Quit()
 * 函数类型：槽函数
 * 函数功能：开启一个QMessageBox，若点击Yes，发送clickYes()信号
 */
void WelcomeWindow::Quit()
{
    this->close();
}

/* 函数名称：void closeEvent(QCloseEvent *event)
 * 函数类型：保护函数
 * 函数功能：捕捉关闭事件，调用ContinueToClose()，决定是否接收事件
 * (version_1.1)
 */
void WelcomeWindow::closeEvent(QCloseEvent *event)
{
    if (ContinueToClose())
    {
        QSqlQuery query;
        query.exec("delete from Hotal");
        query.exec("delete from HotalOrder");
        query.exec("delete from Room");
        query.exec("delete from Message");
        query.exec("delete from PinJiaMessage");

        int i = 0;
        for (Hotal *head = Hotalhead;head != nullptr;head = head->getHotalnext())
        {
            query.prepare("insert into Hotal values (?, ?, ?, ?, ?, ?, ?, ?)");
            query.addBindValue(i);
            query.addBindValue(head->getHotalName());
            query.addBindValue(head->getHotalInfo());
            query.addBindValue(head->getHotalManagerAccount());
            query.addBindValue(head->getHotalTel());
            query.addBindValue(head->getArea());
            query.addBindValue(head->getSuccessful());
            query.addBindValue(head->getNew());
            query.exec();

            i ++;
        }

        i =0;
        for (HotalOrder *head = Orderhead;head != nullptr;head = head->getnext())
        {
            query.prepare("insert into HotalOrder values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
            query.addBindValue(i);
            query.addBindValue(head->getOrderNumber());
            query.addBindValue(head->getUserAccount());
            query.addBindValue(head->getHotalName());
            query.addBindValue(head->getHotalAccount());
            query.addBindValue(head->getRoomType());
            query.addBindValue(head->getTotalmoney());
            query.addBindValue(head->getStart()->toString("yyyy-MM-dd"));
            query.addBindValue(head->getFinal()->toString("yyyy-MM-dd"));
            query.addBindValue(head->getPayOrNot());
            query.addBindValue(head->getSuccessFul());
            query.addBindValue(head->getNew());
            query.addBindValue(head->getCancel());
            query.addBindValue(head->getCancelSuccessful());
            query.addBindValue(head->getCancelNew());
            query.addBindValue(head->getcheckin());
            query.addBindValue(head->getcheckout());
            query.exec();

            i ++;
        }

        i = 0;
        for (Room *head = Roomhead;head != nullptr;head = head->getnext())
        {
            query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
            query.addBindValue(i);
            query.addBindValue(head->getHotalName());
            query.addBindValue(head->getType());
            query.addBindValue(head->getTotalNum());
            query.addBindValue(head->getRoomNum());
            query.addBindValue(head->getDate()->toString("yyyy-MM-dd"));
            query.addBindValue(head->getmoneyPerNight());
            query.exec();

            i ++;
        }

        i = 0;
        for (Message *head = Messagehead;head != nullptr;head = head->getnext())
        {
            query.prepare("insert into Message values (?, ?, ?, ?, ?, ?)");
            query.addBindValue(i);
            query.addBindValue(head->getsendUser());
            query.addBindValue(head->getreceiveUser());
            query.addBindValue(head->getmessage());
            query.addBindValue(head->getdate()->toString("yyyy-MM-dd hh:mm:ss"));
            query.addBindValue(head->getNew());
            query.exec();

            i ++;
        }

        i = 0;
        for (PinJiaMessage *head = PinJiahead;head != nullptr;head = head->getnext())
        {
            query.prepare("insert into PinJiaMessage values (?, ?, ?, ?)");
            query.addBindValue(i);
            query.addBindValue(head->getHotalName());
            query.addBindValue(head->getPinJia());
            query.addBindValue(head->getUser());
            query.exec();

            i ++;
        }

        if (MainAccount1)
        {
            delete MainAccount1;
        }
        else if (MainAccount2)
        {
            delete MainAccount2;
        }
        else if (MainAccount3)
        {
            delete MainAccount3;
        }
        Message *ptr;
        for (Message *head = Messagehead;head != nullptr;head = ptr)
        {
            ptr = head->getnext();
            delete head;
        }
        HotalOrder *ptr1;
        for (HotalOrder *head = Orderhead;head != nullptr;head = ptr1)
        {
            ptr1 = head->getnext();
            delete head;
        }
        Room *ptr2;
        for (Room *head = Roomhead;head != nullptr;head = ptr2)
        {
            ptr2 = head->getnext();
            delete head;
        }
        PinJiaMessage *ptr3;
        for (PinJiaMessage *head = PinJiahead;head != nullptr;head = ptr3)
        {
            ptr3 = head->getnext();
            Message *ptr4;
            for (ptr = head->getmessage();ptr != nullptr;ptr = ptr4)
            {
                ptr4 = ptr->getnext();
                delete ptr;
            }
            delete head;
        }
        Hotal *ptr5;
        for (Hotal *head = Hotalhead;head != nullptr;head = ptr5)
        {
            ptr5 = head->getHotalnext();
            HotalOrder *ptr6;
            for (ptr1 = head->getorderhead();ptr1 != nullptr;ptr1 = ptr6)
            {
                ptr6 = ptr1->getnext();
                delete ptr1;
            }
            Room *ptr7;
            for (ptr2 = head->getRoomhead();ptr2 != nullptr;ptr2 = ptr7)
            {
                ptr7 = ptr2->getnext();
                delete ptr2;
            }

            PinJiaMessage *ptr8;
            for (ptr3 = head->getPMhead();ptr3 != nullptr;ptr3 = ptr8)
            {
                ptr8 = ptr3->getnext();
                Message *ptr9;
                for (ptr = ptr3->getmessage();ptr != nullptr;ptr = ptr9)
                {
                    ptr9 = ptr->getnext();
                    delete ptr;
                }
                delete ptr3;
            }
            delete head;
        }
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void WelcomeWindow::ResetWelcome()
{
    (MainAccount1) = nullptr;
    (MainAccount2) = nullptr;
    (MainAccount3) = nullptr;
    show();
}
