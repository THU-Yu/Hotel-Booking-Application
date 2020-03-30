#ifndef MESSAGEDETAIL_H
#define MESSAGEDETAIL_H

#include "message.h"
#include <QDialog>

class QLabel;
class QPushButton;
class QTextEdit;

class MessageDetail:public QDialog
{
    Q_OBJECT

public:
    MessageDetail(Message *ptr, QWidget *parent=0);
    ~MessageDetail(){}
private:
    QLabel *info;
    QLabel *user1;
    QLabel *user2;
    QLabel *receive1;
    QLabel *receive2;
    QLabel *date1;
    QLabel *date2;
    QLabel *message1;
    QPushButton *OkButton;
    QTextEdit *message2;
};

#endif // MESSAGEDETAIL_H
