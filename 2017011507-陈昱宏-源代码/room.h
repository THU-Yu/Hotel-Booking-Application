/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：Room.h
 * 内容：声明Room类
 * 版本：version_1.2
 * 作者：陈昱宏
 * 创建日期：2018/07/20
 */
#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <QDate>

class Room  //声明Room类
{
    QString HotalName;
    QString RoomType; //房间种类
    int TotalNum;
    int RoomNum; //该种类剩余数量
    QDate *Date;
    float moneyPerNight;
    Room *next;
public:
    Room(QString hotal,QString Type,int n=0, int num=0, QDate *da=nullptr, float moneyPerNight=0, Room *type=nullptr)
        :HotalName(hotal),RoomType(Type),TotalNum(n), RoomNum(num), Date(da), moneyPerNight(moneyPerNight), next(type){}
    Room(Room &r);
    QString getHotalName(){return HotalName;}
    QString getType(){return RoomType;}
    int getTotalNum(){return TotalNum;}
    int getRoomNum(){return RoomNum;}
    QDate* getDate(){return Date;}
    Room* getnext(){return next;}
    float getmoneyPerNight(){return moneyPerNight;}
    void changeHotalName(QString U){HotalName = U;}
    void ChangeType(QString type){RoomType = type;}
    void ChangeTotalNum(int num){TotalNum = num;}
    void ChangeRoomNum(int num){RoomNum = num;}
    void ChangeDate(QDate *date){Date = date;}
    void Changenext(Room *type){next = type;}
    void ChangemoneyPerNight(float money){moneyPerNight = money;}
};
#endif // ROOM_H
