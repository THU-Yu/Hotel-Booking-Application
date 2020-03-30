#ifndef PINJIAMESSAGE_H
#define PINJIAMESSAGE_H

#include "message.h"

class PinJiaMessage
{
    QString HotalName;  //酒店名
    float PinJia;
    QString User;
    Message *message;
    PinJiaMessage *next;
public:
    PinJiaMessage(QString HotalName, float PinJia, QString user, Message *n=nullptr, PinJiaMessage *next=nullptr)
        :HotalName(HotalName), PinJia(PinJia), User(user), message(n), next(next){}
    PinJiaMessage(PinJiaMessage &p);

    QString getHotalName(){return HotalName;}
    QString getUser(){return User;}
    float getPinJia(){return PinJia;}
    Message* getmessage(){return message;}
    PinJiaMessage* getnext(){return next;}

    void changeHotalName(QString U){HotalName = U;}
    void changeUser(QString U){User = U;}
    void changePinJia(float p){PinJia = p;}
    void changemessage(Message *m){message = m;}
    void changenext(PinJiaMessage *n){next = n;}

    void addMessage(Message *m);
};

#endif // PINJIAMESSAGE_H
