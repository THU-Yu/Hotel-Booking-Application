/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：HotalOrder.h
 * 内容：声明HotalOrder类
 * 版本：version_1.2
 * 作者：陈昱宏
 * 创建日期：2018/07/20
 */
#ifndef HOTALORDER_H
#define HOTALORDER_H

#include <QString>
#include <QDate>

class HotalOrder //声明HotalOrder类
{
    HotalOrder *next; //用于创造链表的指针
    QString UserAccount; //下单用户账号
    QString HotalName;  //酒店名
    QString HotalAccount;
    QString RoomType; //酒店房间种类
    QString OrderNumber;
    double Totalmoney; //总金额
    QDate *Start; //起始时间
    QDate *Final; //结束时间
    bool PayOrNot;
    bool SuccessFul; //是否通过平台审核
    bool New;
    bool Cancel;
    bool CancelSuccessful;
    bool CancelNew;
    bool checkin;
    bool checkout;
public:
    HotalOrder(QString u='\0', QString h='\0', QString HotalAccount='\0', QString r='\0',QString Number='\0', double m=0, QDate *s=nullptr, QDate *f=nullptr
            , bool pay=false, bool SuccessFul=false, bool New=true, bool Cancel=false, bool CancelSuccessful=false, bool CancelNew=false)
        :UserAccount(u), HotalName(h), HotalAccount(HotalAccount), RoomType(r), OrderNumber(Number), Totalmoney(m), Start(s), Final(f), PayOrNot(pay),
          SuccessFul(SuccessFul), New(New), Cancel(Cancel), CancelSuccessful(CancelSuccessful), CancelNew(CancelNew),checkin(false),checkout(false)
    {next = nullptr;} //构造函数
    HotalOrder(HotalOrder &h);
    //取得属性的函数
    HotalOrder* getnext(){return next;}
    QString getUserAccount(){return UserAccount;}
    QString getHotalName(){return HotalName;}
    QString getHotalAccount(){return HotalAccount;}
    QString getRoomType(){return RoomType;}
    QString getOrderNumber(){return OrderNumber;}
    double getTotalmoney(){return Totalmoney;}
    QDate* getStart(){return Start;}
    QDate* getFinal(){return Final;}
    bool getPayOrNot(){return PayOrNot;}
    bool getSuccessFul(){return SuccessFul;}
    bool getNew(){return New;}
    bool getCancel(){return Cancel;}
    bool getCancelSuccessful(){return CancelSuccessful;}
    bool getCancelNew(){return CancelNew;}
    bool getcheckin(){return checkin;}
    bool getcheckout(){return checkout;}

    //修改属性的函数
    void changenext(HotalOrder *n){next = n;}
    void changeUserAccount(QString U){UserAccount = U;}
    void changeHotalName(QString U){HotalName = U;}
    void changeHotalAccount(QString U){HotalAccount = U;}
    void changeRoomType(QString U){RoomType = U;}
    void changeOrderNumber(QString n){OrderNumber = n;}
    void changeTotalmoney(double T){Totalmoney = T;}
    void changeStart(QDate *S){Start = S;}
    void changeFinal(QDate *S){Final = S;}
    void changePayOrNot(){PayOrNot = (!PayOrNot);}
    void changeSuccessFul(){SuccessFul = (!SuccessFul);}
    void changeNew(){New = (!New);}
    void changeCancel(){Cancel = (!Cancel);}
    void changeCancelSuccessful(){CancelSuccessful = (!CancelSuccessful);}
    void changeCancelNew(){CancelNew = (!CancelNew);}
    void changecheckin(bool n){checkin = n;}
    void changecheckout(bool n){checkout = n;}
};

#endif // HOTALORDER_H
