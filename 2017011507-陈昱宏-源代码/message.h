#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDate>

class Message
{
    QString sendUser;
    QString receiveUser;
    QString message;
    Message *next;
    QDateTime *date;
    bool New;
public:
    Message(QString sendUser, QString receiveUser, QString message='\0', Message *next=nullptr,QDateTime *date=nullptr, bool New=true)
        :sendUser(sendUser), receiveUser(receiveUser), message(message), next(next), date(date), New(New){}
    Message(Message &m);
    QString getsendUser(){return sendUser;}
    QString getreceiveUser(){return receiveUser;}
    QString getmessage(){return message;}
    Message* getnext(){return next;}
    QDateTime* getdate(){return date;}
    bool getNew(){return New;}

    void changesendUser(QString s){sendUser = s;}
    void changereceiveUser(QString s){receiveUser = s;}
    void changemessage(QString s){message = s;}
    void changenext(Message *s){next = s;}
    void changedate(QDateTime *d){date = d;}
    void changeNew(bool n){New = n;}
};

#endif // MESSAGE_H
