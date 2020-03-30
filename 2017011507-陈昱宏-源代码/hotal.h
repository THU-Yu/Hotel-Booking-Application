/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：Hotal.h
 * 内容：声明Hotal类
 * 版本：version_1.2
 * 作者：陈昱宏
 * 创建日期：2018/07/20
 */
#ifndef HOTAL_H
#define HOTAL_H

#include "room.h"
#include "hotalorder.h"
#include "PinJiaMessage.h"

class Hotal //声明Hotal类
{
    QString HotalName; //酒店名
    QString HotalInfo; //酒店简介
    QString HotalManagerAccount; //酒店负责人账号
    QString HotalTel;
    QString Area; //酒店所在地
    int roomTypeNum; //酒店房间种类数
    int OrderNum; //酒店订单数
    float minMoney;
    float PinJia;
    int PinJiaNum;
    Room *head, *rear; //房间链表的首尾指针
    HotalOrder *orderhead, *orderrear; //酒店订单链表的首尾指针
    PinJiaMessage *PMhead, *PMrear;
    Hotal *next; //用于创造链表的指针
    bool Successful;
    bool New;
public:
    Hotal(QString HotalName, QString HotalInfo, QString HotalManagerAccount, QString tel, QString Area); //构造函数
    Hotal(Hotal &h);
    //取得属性的函数
    QString getHotalName(){return HotalName;}
    QString getHotalInfo(){return HotalInfo;}
    QString getHotalManagerAccount(){return HotalManagerAccount;}
    QString getHotalTel(){return HotalTel;}
    QString getArea(){return Area;}
    int getroomTypeNum(){return roomTypeNum;}
    int getOrderNum(){return OrderNum;}
    Room* getRoomhead(){return head;}
    Room* getRoomrear(){return rear;}
    Hotal* getHotalnext(){return next;}
    HotalOrder* getorderhead(){return orderhead;}
    HotalOrder* getorderrear(){return orderrear;}
    float getminMoney(){return minMoney;}
    float getPinJia(){return PinJia;}
    int getPinJiaNum(){return PinJiaNum;}
    PinJiaMessage* getPMhead(){return PMhead;}
    PinJiaMessage* getPMrear(){return PMrear;}
    bool getSuccessful(){return Successful;}
    bool getNew(){return New;}

    //修改属性的函数
    void changeHotalName(QString hotalname){HotalName = hotalname;}
    void changeHotalInfo(QString hotalinfo){HotalInfo = hotalinfo;}
    void changeHotalManagerAccount(QString hotalmanageraccount){HotalManagerAccount = hotalmanageraccount;}
    void changeHotalTel(QString tel){HotalTel = tel;}
    void changeArea(QString area){Area = area;}
    void changeroomTypeNum(int num){roomTypeNum = num;}
    void changeOrderNum(int num){OrderNum = num;}
    void changeRoomhead(Room *h){head = h;}
    void changeRoomrear(Room *r){rear = r;}
    void changeHotalnext(Hotal *h){next = h;}
    void changeorderhead(HotalOrder *h){orderhead = h;}
    void changeorderrear(HotalOrder *h){orderrear = h;}
    void changeminMoney(float m){minMoney = m;}
    void changePinJia(float m){PinJia = m;}
    void changePinJiaNum(int m){PinJiaNum = m;}
    void changePMhead(PinJiaMessage *h){PMhead = h;}
    void changePMrear(PinJiaMessage *h){PMrear = h;}
    void changeSuccessful(bool n){Successful = n;}
    void changeNew(bool n){New = n;}


    //增加房间种类数目和酒店订单数目
    void addRoomType(Room *newType);
    void addOrder(HotalOrder *newOrder);
    void addPinJiaMessage(PinJiaMessage *newPinjia);
};
#endif // HOTAL_H
