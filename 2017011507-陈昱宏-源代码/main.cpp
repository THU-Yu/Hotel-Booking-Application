/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：main.cpp
 * 内容：主函数
 * 版本：version_1.0
 * 作者：陈昱宏
 * 创建日期：2018/07/18
 *
 * 版本：version_1.1
 * 修改部分：字体修改
 * 修改者：陈昱宏（上版本作者：陈昱宏）
 * 修改日期：2018/07/19
 *
 * 版本：version_2.0
 * 修改部分：数据库连接
 * 修改者：陈昱宏（上版本作者：陈昱宏）
 * 修改日期：2018/07/21
 */
#include "account.h"
#include "normaluser.h"
#include "hotaluser.h"
#include "platformuser.h"
#include "WelcomeWindow.h"
#include "Login_Dialog.h"
#include "Register_Dialog.h"
#include "Search_Dialog.h"
#include "registerconfirmdialog.h"
#include "vistor_search_dialog.h"
#include "search.h"
#include "MainWindow.h"
#include "Connection.h"
#include "personalinfo.h"
#include "platformmanage.h"
#include "hotal.h"
#include "hotalorder.h"
#include "room.h"
#include "message.h"
#include "PinJiaMessage.h"
#include "searchorder.h"
#include "hotalmanage.h"
#include "receivemessage.h"
#include <QApplication>
#include <QObject>
#include <QFont>
#include <QDebug>

Account *Mainaccount1=nullptr;
NormalUser *Mainaccount2=nullptr;
HotalUser *Mainaccount3=nullptr;
PlatformUser *Mainaccount4=nullptr;
Hotal *Hotalhead=nullptr;
HotalOrder *Orderhead=nullptr;
Room *Roomhead=nullptr;
Message *Messagehead=nullptr;
PinJiaMessage *PinJiahead=nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设定QApplication字体大小、字型
    QFont font;
    font.setPointSize(14);
    //字体修改为FangSong(仿宋)(version_1.1)
    font.setFamily(("FangSong"));
    a.setFont(font);

    //连接数据库(version_2.0)
    createConnection("create table User (account varchar(20) primary key, password varchar(20), phone_number varchar(15),"
                     " email_address varchar(100), bankAccount varchar(20), bankPassword varchar(10), bankMoney double,"
                     " UserType varchar(30))");
    createConnection("create table Hotal (No int primary key,HotalName varchar(100), HotalInfo varchar(1000),"
                     " HotalManagerAccount varchar(20),HotalTel varchar(15), Area varchar(50), Successful bool, New bool)");
    createConnection("create table HotalOrder (No int primary key,OrderNumber varchar(20), UserAccount varchar(20), HotalName varchar(100), HotalAccount varchar(20), RoomType varchar(100),"
                     " Totalmoney double, Start varchar(30), Final varchar(30), PayOrNot bool, SuccessFul bool, New bool, Cancel bool, CancelSuccessful bool, CancelNew bool, Checkin bool, Checkout bool)");
    createConnection("create table Room (No int primary key,HotalName varchar(100), RoomType varchar(100), TotalNum int,"
                     " RoomNum int, Date varchar(30), moneyPerNight float)");
    createConnection("create table Message (No int primary key,sendUser varchar(20), receiveUser varchar(100),"
                     " message varchar(1000), Date varchar(15), New bool)");
    createConnection("create table PinJiaMessage (No int primary key,HotalName varchar(100), PinJia float, User varchar(20))");

    QSqlQuery _query,query,query1,query2,query3,query4,query5;
    _query.prepare("select * from User");
    _query.exec();
    if (!_query.next())
    {
        query.prepare("insert into User values (?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue("2017011507");
        query.addBindValue("990714");
        query.addBindValue("17810270258");
        query.addBindValue("YuHung.Chen@studentpartner.com");
        query.addBindValue("11111111111111111111111");
        query.addBindValue("990714");
        query.addBindValue(100000000);
        query.addBindValue("平台管理");
        query.exec();

        query.prepare("insert into User values (?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue("HotalManager1");
        query.addBindValue("111111");
        query.addBindValue("12545347845");
        query.addBindValue("123123@123.com");
        query.addBindValue("1000000000000000000000");
        query.addBindValue("111111");
        query.addBindValue(12000);
        query.addBindValue("酒店经理");
        query.exec();

        query.prepare("insert into User values (?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue("123123123");
        query.addBindValue("123123");
        query.addBindValue("17545245478");
        query.addBindValue("123456@123.com");
        query.addBindValue("0000000000000000000000");
        query.addBindValue("123123");
        query.addBindValue(1200);
        query.addBindValue("一般用户");
        query.exec();

        query.prepare("insert into User values (?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue("HotalManager2");
        query.addBindValue("000000");
        query.addBindValue("12545345678");
        query.addBindValue("456@123.com");
        query.addBindValue("0000000000000000000111");
        query.addBindValue("000000");
        query.addBindValue(12000);
        query.addBindValue("酒店经理");
        query.exec();

        query.prepare("insert into User values (?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue("HotalManager3");
        query.addBindValue("222222");
        query.addBindValue("12545349876");
        query.addBindValue("1789@123.com");
        query.addBindValue("1110000000000000000000");
        query.addBindValue("222222");
        query.addBindValue(12000);
        query.addBindValue("酒店经理");
        query.exec();
    }
    _query.prepare("select * from Hotal");
    _query.exec();
    if (!_query.next())
    {
        query.prepare("insert into Hotal values (?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(0);
        query.addBindValue("清华大酒店");
        query.addBindValue("位于清华校内");
        query.addBindValue("HotalManager1");
        query.addBindValue("98464561");
        query.addBindValue("北京市");
        query.addBindValue(true);
        query.addBindValue(false);
        query.exec();

        query.prepare("insert into Hotal values (?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(1);
        query.addBindValue("清华豪华酒店");
        query.addBindValue("位于清华校内");
        query.addBindValue("HotalManager2");
        query.addBindValue("66875686");
        query.addBindValue("北京市");
        query.addBindValue(true);
        query.addBindValue(false);
        query.exec();

        query.prepare("insert into Hotal values (?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(2);
        query.addBindValue("北大小旅馆");
        query.addBindValue("位于世界一流大学-清华大学的隔壁");
        query.addBindValue("HotalManager3");
        query.addBindValue("79846578");
        query.addBindValue("北京市");
        query.addBindValue(false);
        query.addBindValue(true);
        query.exec();
    }

    _query.prepare("select * from HotalOrder");
    _query.exec();
    if (!_query.next())
    {
        query.prepare("insert into HotalOrder values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(0);
        query.addBindValue("0000000000001");
        query.addBindValue("123123123");
        query.addBindValue("清华大酒店");
        query.addBindValue("HotalManager1");
        query.addBindValue("双人标间");
        query.addBindValue(200.00);
        query.addBindValue("2018-07-18");
        query.addBindValue("2018-07-22");
        query.addBindValue(true);
        query.addBindValue(true);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(true);
        query.addBindValue(true);
        query.exec();

        query.prepare("insert into HotalOrder values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(1);
        query.addBindValue("0000000000002");
        query.addBindValue("123123123");
        query.addBindValue("清华大酒店");
        query.addBindValue("HotalManager1");
        query.addBindValue("双人标间");
        query.addBindValue(50.00);
        query.addBindValue("2018-07-29");
        query.addBindValue("2018-07-30");
        query.addBindValue(true);
        query.addBindValue(false);
        query.addBindValue(true);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(false);
        query.exec();

        query.prepare("insert into HotalOrder values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(2);
        query.addBindValue("0000000000003");
        query.addBindValue("123123123");
        query.addBindValue("清华豪华酒店");
        query.addBindValue("HotalManager2");
        query.addBindValue("总统套房");
        query.addBindValue(500.00);
        query.addBindValue("2018-07-24");
        query.addBindValue("2018-07-25");
        query.addBindValue(true);
        query.addBindValue(true);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(true);
        query.addBindValue(true);
        query.exec();

        query.prepare("insert into HotalOrder values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(3);
        query.addBindValue("0000000000004");
        query.addBindValue("123123123");
        query.addBindValue("清华豪华酒店");
        query.addBindValue("HotalManager2");
        query.addBindValue("总统套房");
        query.addBindValue(500.00);
        query.addBindValue("2018-07-26");
        query.addBindValue("2018-07-27");
        query.addBindValue(true);
        query.addBindValue(true);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(false);
        query.addBindValue(false);
        query.exec();
    }
    _query.prepare("select * from Room");
    _query.exec();
    if (!_query.next())
    {
        query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(0);
        query.addBindValue("清华大酒店");
        query.addBindValue("单人标间");
        query.addBindValue(20);
        query.addBindValue(20);
        query.addBindValue("2018-07-24");
        query.addBindValue(25);
        query.exec();

        query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(1);
        query.addBindValue("清华大酒店");
        query.addBindValue("单人标间");
        query.addBindValue(20);
        query.addBindValue(20);
        query.addBindValue("2018-07-25");
        query.addBindValue(25);
        query.exec();

        query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(2);
        query.addBindValue("清华大酒店");
        query.addBindValue("单人标间");
        query.addBindValue(20);
        query.addBindValue(20);
        query.addBindValue("2018-07-26");
        query.addBindValue(25);
        query.exec();

        query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(3);
        query.addBindValue("清华大酒店");
        query.addBindValue("单人标间");
        query.addBindValue(20);
        query.addBindValue(0);
        query.addBindValue("2018-07-27");
        query.addBindValue(25);
        query.exec();

        query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(4);
        query.addBindValue("清华大酒店");
        query.addBindValue("双人标间");
        query.addBindValue(20);
        query.addBindValue(20);
        query.addBindValue("2018-07-24");
        query.addBindValue(50);
        query.exec();

        query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(5);
        query.addBindValue("清华大酒店");
        query.addBindValue("双人标间");
        query.addBindValue(20);
        query.addBindValue(20);
        query.addBindValue("2018-07-25");
        query.addBindValue(50);
        query.exec();

        query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(6);
        query.addBindValue("清华大酒店");
        query.addBindValue("双人标间");
        query.addBindValue(20);
        query.addBindValue(20);
        query.addBindValue("2018-07-26");
        query.addBindValue(50);
        query.exec();

        query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(7);
        query.addBindValue("清华大酒店");
        query.addBindValue("双人标间");
        query.addBindValue(20);
        query.addBindValue(0);
        query.addBindValue("2018-07-27");
        query.addBindValue(50);
        query.exec();

        query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(8);
        query.addBindValue("清华大酒店");
        query.addBindValue("双人标间");
        query.addBindValue(20);
        query.addBindValue(0);
        query.addBindValue("2018-07-28");
        query.addBindValue(50);
        query.exec();

        query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(9);
        query.addBindValue("清华大酒店");
        query.addBindValue("双人标间");
        query.addBindValue(20);
        query.addBindValue(0);
        query.addBindValue("2018-07-29");
        query.addBindValue(50);
        query.exec();

        query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(10);
        query.addBindValue("清华大酒店");
        query.addBindValue("双人标间");
        query.addBindValue(20);
        query.addBindValue(0);
        query.addBindValue("2018-07-30");
        query.addBindValue(50);
        query.exec();

        query.prepare("insert into Room values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(11);
        query.addBindValue("清华豪华酒店");
        query.addBindValue("总统套房");
        query.addBindValue(2);
        query.addBindValue(2);
        query.addBindValue("2018-07-24");
        query.addBindValue(500);
        query.exec();
    }

    _query.prepare("select * from Message");
    _query.exec();
    if (!_query.next())
    {
        query.prepare("insert into Message values (?, ?, ?, ?, ?, ?)");
        query.addBindValue(0);
        query.addBindValue("123123123");
        query.addBindValue("清华大酒店");
        query.addBindValue("环境很好，很舒适；text:bskajkasjjndjshfjsdhjdhfjsdhfdsvhfjsh");
        query.addBindValue("2018-07-24 10:29:30");
        query.addBindValue(true);
        query.exec();

        query.prepare("insert into Message values (?, ?, ?, ?, ?, ?)");
        query.addBindValue(1);
        query.addBindValue("123123123");
        query.addBindValue("清华豪华酒店");
        query.addBindValue("真的豪华，性价比高");
        query.addBindValue("2018-07-25 22:29:30");
        query.addBindValue(true);
        query.exec();
    }

    _query.prepare("select * from PinJiaMessage");
    _query.exec();
    if (!_query.next())
    {
        query.prepare("insert into PinJiaMessage values (?, ?, ?, ?)");
        query.addBindValue(0);
        query.addBindValue("清华大酒店");
        query.addBindValue(4.9);
        query.addBindValue("123123123");
        query.exec();

        query.prepare("insert into PinJiaMessage values (?, ?, ?, ?)");
        query.addBindValue(1);
        query.addBindValue("清华豪华酒店");
        query.addBindValue(5.0);
        query.addBindValue("123123123");
        query.exec();
    }

    query1.prepare("select * from HotalOrder");
    if (query1.exec())
    {
        while(query1.next())
        {
            HotalOrder *ptr1, *ptr2;
            ptr1 = new HotalOrder(query1.value(2).toString(),query1.value(3).toString(),query1.value(4).toString(),query1.value(5).toString(),
                                  query1.value(1).toString(),query1.value(6).toFloat(),new QDate(QDate::fromString(query1.value(7).toString(),"yyyy-MM-dd")),
                                  new QDate(QDate::fromString(query1.value(8).toString(),"yyyy-MM-dd")),
                                  query1.value(9).toBool(),query1.value(10).toBool(),query1.value(11).toBool(),
                                  query1.value(12).toBool(),query1.value(13).toBool(),query1.value(14).toBool());
            ptr1->changecheckin(query1.value(15).toBool());
            ptr1->changecheckout(query1.value(16).toBool());
            if (!Orderhead)
            {
                Orderhead = ptr1;
                ptr2 = ptr1;
            }
            else
            {
                ptr2->changenext(ptr1);
                ptr2 = ptr1;
            }
        }
    }
    query2.prepare("select * from Room");
    if (query2.exec())
    {
        Room *ptr1, *ptr2;
        while(query2.next())
        {
            ptr1 = new Room(query2.value(1).toString(),query2.value(2).toString(),query2.value(3).toInt(),query2.value(4).toInt(),
                            new QDate(QDate::fromString(query2.value(5).toString(),"yyyy-MM-dd")),query2.value(6).toFloat());
            if (!Roomhead)
            {
                Roomhead = ptr1;
                ptr2 = ptr1;
            }
            else
            {
                if ((ptr2->getHotalName() == ptr1->getHotalName())&&(ptr2->getType() == ptr1->getType()))
                {
                    ptr2->Changenext(ptr1);
                    ptr2 = ptr1;
                }
                else
                {
                    for (QDate date = ptr2->getDate()->addDays(1);date <= QDate::currentDate().addDays(31);date = date.addDays(1))
                    {
                        ptr2->Changenext(new Room(ptr2->getHotalName(),ptr2->getType(),ptr2->getTotalNum(),ptr2->getTotalNum(),new QDate(date),ptr2->getmoneyPerNight()));
                        ptr2 = ptr2->getnext();
                    }
                    ptr2->Changenext(ptr1);
                    ptr2 = ptr1;
                }
            }
        }

        for (QDate date = ptr2->getDate()->addDays(1);date <= QDate::currentDate().addDays(31);date = date.addDays(1))
        {
            ptr2->Changenext(new Room(ptr2->getHotalName(),ptr2->getType(),ptr2->getTotalNum(),ptr2->getTotalNum(),new QDate(date),ptr2->getmoneyPerNight()));
            ptr2 = ptr2->getnext();
        }
    }
    query3.prepare("select * from Message");
    if (query3.exec())
    {
        while(query3.next())
        {
            Message *ptr1, *ptr2;
            ptr1 = new Message(query3.value(1).toString(),query3.value(2).toString(),query3.value(3).toString(),
                               nullptr, new QDateTime(QDateTime::fromString(query3.value(4).toString(),"yyyy-MM-dd hh:mm:ss")),query3.value(6).toBool());
            if (!Messagehead)
            {
                Messagehead = ptr1;
                ptr2 = ptr1;
            }
            else
            {
                ptr2->changenext(ptr1);
                ptr2 = ptr1;
            }
        }
    }

    query4.prepare("select * from PinJiaMessage");
    if (query4.exec())
    {
        while(query4.next())
        {
            PinJiaMessage *ptr1, *ptr2;
            ptr1 = new PinJiaMessage(query4.value(1).toString(),query4.value(2).toFloat(),query4.value(3).toString());
            if (!PinJiahead)
            {
                PinJiahead = ptr1;
                ptr2 = ptr1;
            }
            else
            {
                ptr2->changenext(ptr1);
                ptr2 = ptr1;
            }
            Message *ptr_1, *ptr_2;
            for (ptr_1 = Messagehead;ptr_1 != nullptr;ptr_1 = ptr_1->getnext())
            {
                if ((ptr1->getHotalName() == ptr_1->getreceiveUser()) && (ptr1->getUser() == ptr_1->getsendUser()))
                {
                    ptr_2 = new Message((*ptr_1));
                    ptr1->addMessage(ptr_2);
                }
            }
        }
    }

    query5.prepare("select * from Hotal");
    if (query5.exec())
    {
        while(query5.next())
        {
            Hotal *ptr1, *ptr2;
            ptr1 = new Hotal(query5.value(1).toString(),query5.value(2).toString(),
                             query5.value(3).toString(),query5.value(4).toString(),query5.value(5).toString());
            if (!Hotalhead)
            {
                Hotalhead = ptr1;
                ptr2 = ptr1;
            }
            else
            {
                ptr2->changeHotalnext(ptr1);
                ptr2 = ptr1;
            }
            ptr1->changeSuccessful(query5.value(6).toBool());
            ptr1->changeNew(query5.value(7).toBool());
            if (ptr1->getSuccessful())
            {
                PinJiaMessage *ptr_1, *ptr_2;
                for (ptr_1 = PinJiahead;ptr_1 != nullptr;ptr_1 = ptr_1->getnext())
                {
                    if (ptr1->getHotalName() == ptr_1->getHotalName())
                    {
                        ptr_2 = new PinJiaMessage((*ptr_1));
                        ptr1->addPinJiaMessage(ptr_2);
                    }
                }
                Room *ptr_3, *ptr_4;
                for (ptr_3 = Roomhead;ptr_3 != nullptr;ptr_3 = ptr_3->getnext())
                {
                    if (ptr1->getHotalName() == ptr_3->getHotalName())
                    {
                        ptr_4 = new Room((*ptr_3));
                        ptr1->addRoomType(ptr_4);
                    }
                }
                HotalOrder *ptr_5, *ptr_6;
                for (ptr_5 = Orderhead;ptr_5 != nullptr;ptr_5 = ptr_5->getnext())
                {
                    if (ptr1->getHotalName() == ptr_5->getHotalName())
                    {
                        ptr_6 = new HotalOrder((*ptr_5));
                        ptr1->addOrder(ptr_6);
                    }
                }
            }
        }
    }
    //建构WelcomeWindow、Login_Dialog、Register_Dialog对象
    WelcomeWindow *mywindow = new WelcomeWindow(Mainaccount2,Mainaccount3,Mainaccount4,Hotalhead,Orderhead,Roomhead,Messagehead,PinJiahead);
    Login_Dialog *mylogin = new Login_Dialog(Mainaccount2,Mainaccount3,Mainaccount4);
    //建构Search_Dialog、RegisterConfirmDialog、Vistor_Search_Dialog、Search对象(version_1.1)
    Search_Dialog *userSearch = new Search_Dialog;
    RegisterConfirmDialog *Confirm = new RegisterConfirmDialog;
    Register_Dialog *myregister = new Register_Dialog(Confirm);
    Search *mysearch = new Search;
    PersonalInfo *mypersonalinfo = new PersonalInfo(Mainaccount2,Mainaccount3,Mainaccount4);
    PlatformManage *myplatform = new PlatformManage(Hotalhead,Orderhead,Messagehead,Roomhead);
    SearchOrder *mysearchorder1 = new SearchOrder(Hotalhead,Messagehead,PinJiahead,Roomhead,Orderhead,Mainaccount2,Mainaccount3,Mainaccount4);
    SearchOrder *mysearchorder2 = new SearchOrder(Hotalhead,Messagehead,PinJiahead,Roomhead,Orderhead,Mainaccount2,Mainaccount3,Mainaccount4);
    HotalManage *myhotalmanage0 = new HotalManage(Hotalhead,Messagehead,Roomhead,Orderhead,Mainaccount2,Mainaccount3,Mainaccount4);
    HotalManage *myhotalmanage1 = new HotalManage(Hotalhead,Messagehead,Roomhead,Orderhead,Mainaccount2,Mainaccount3,Mainaccount4);
    HotalManage *myhotalmanage2 = new HotalManage(Hotalhead,Messagehead,Roomhead,Orderhead,Mainaccount2,Mainaccount3,Mainaccount4);
    HotalManage *myhotalmanage3 = new HotalManage(Hotalhead,Messagehead,Roomhead,Orderhead,Mainaccount2,Mainaccount3,Mainaccount4);
    HotalManage *myhotalmanage4 = new HotalManage(Hotalhead,Messagehead,Roomhead,Orderhead,Mainaccount2,Mainaccount3,Mainaccount4);
    ReceiveMessage *myreceivemessage = new ReceiveMessage(Messagehead,Mainaccount2,Mainaccount3,Mainaccount4);
    MainWindow *mymainwindow = new MainWindow(Mainaccount2,Mainaccount3,Mainaccount4,Hotalhead,Orderhead,Roomhead,Messagehead,PinJiahead,mysearch,userSearch,mypersonalinfo,myplatform,mysearchorder1,mysearchorder2,myhotalmanage0,myhotalmanage1,myhotalmanage2,myhotalmanage3,myhotalmanage4,myreceivemessage);

    //连接不同界面间的信号槽
    QObject::connect(mywindow,SIGNAL(showLoginDialog()),mylogin,SLOT(exec()));
    QObject::connect(mylogin,SIGNAL(ShowWelcome()),mywindow,SLOT(show()));
    QObject::connect(mywindow,SIGNAL(showRegisterDialog()),myregister,SLOT(exec()));
    QObject::connect(myregister,SIGNAL(ShowWelcome()),mywindow,SLOT(show()));
    //连接不同界面间的信号槽(version_1.1)
    QObject::connect(mylogin,SIGNAL(successful(NormalUser*&)),mymainwindow,SLOT(RealLogin(NormalUser*&)));
    QObject::connect(mylogin,SIGNAL(successful(HotalUser*&)),mymainwindow,SLOT(RealLogin(HotalUser*&)));
    QObject::connect(mylogin,SIGNAL(successful(PlatformUser*&)),mymainwindow,SLOT(RealLogin(PlatformUser*&)));
    QObject::connect(mywindow,SIGNAL(showVistorDialog()),mymainwindow,SLOT(show()));
    QObject::connect(mysearch,SIGNAL(showLogin()),mylogin,SLOT(exec()));
    QObject::connect(mysearch,SIGNAL(hideMainWindow()),mymainwindow,SLOT(hide()));
    QObject::connect(mysearch,SIGNAL(ShowWelcome()),mywindow,SLOT(ResetWelcome()));
    QObject::connect(mysearch,SIGNAL(ShowWelcome()),mymainwindow,SLOT(RealLogout()));
    QObject::connect(mysearch,SIGNAL(searchHotal(QString,QString,QString)),mymainwindow,SLOT(searchHotal(QString,QString,QString)));
    QObject::connect(userSearch,SIGNAL(searchHotal(QString,QString,QString)),mymainwindow,SLOT(searchHotal(QString,QString,QString)));
    QObject::connect(mymainwindow,SIGNAL(showWelcome()),mywindow,SLOT(ResetWelcome()));
    QObject::connect(mypersonalinfo,SIGNAL(back()),mymainwindow,SLOT(Back()));
    QObject::connect(mysearchorder1,SIGNAL(back()),mymainwindow,SLOT(Back()));
    QObject::connect(mysearchorder2,SIGNAL(back()),mymainwindow,SLOT(Back()));
    QObject::connect(myplatform,SIGNAL(back()),mymainwindow,SLOT(Back()));
    QObject::connect(myhotalmanage0,SIGNAL(back()),mymainwindow,SLOT(Back()));
    QObject::connect(myhotalmanage1,SIGNAL(back()),mymainwindow,SLOT(Back()));
    QObject::connect(myhotalmanage2,SIGNAL(back()),mymainwindow,SLOT(Back()));
    QObject::connect(myhotalmanage3,SIGNAL(back()),mymainwindow,SLOT(Back()));
    QObject::connect(myhotalmanage4,SIGNAL(back()),mymainwindow,SLOT(Back()));
    QObject::connect(myreceivemessage,SIGNAL(back()),mymainwindow,SLOT(Back()));

    //初始显示mywindow
    mywindow->show();
    a.exec();
    exit(0);
}
