#ifndef SENDMESSAGEDIALOG_H
#define SENDMESSAGEDIALOG_H

#include "message.h"
#include "normaluser.h"
#include "hotaluser.h"
#include "platformuser.h"
#include <QDialog>
#include <QCloseEvent>

class QTextEdit;
class QLabel;
class QPushButton;

class SendMessageDialog:public QDialog
{
    Q_OBJECT

public:
    SendMessageDialog(Message *messagehead, QString receiveUser, NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainaccount3, QWidget *parent=0);
    bool ContinueToClose();
    ~SendMessageDialog(){}
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void EnableSend();
    void SendMessage();
private:
    QLabel *info;
    QLabel *receiveUser1;
    QLabel *receiveUser2;
    QLabel *message;
    QTextEdit *messagetext;
    QPushButton *SendButton;
    QPushButton *CancelButton;
    Message *Messagehead;
    NormalUser *MainAccount1;
    HotalUser *MainAccount2;
    PlatformUser *MainAccount3;
    bool sent;
};

#endif // SENDMESSAGEDIALOG_H
