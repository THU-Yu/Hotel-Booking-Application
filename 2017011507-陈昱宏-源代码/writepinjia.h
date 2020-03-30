#ifndef WRITEPINJIA_H
#define WRITEPINJIA_H

#include "PinJiaMessage.h"
#include "message.h"
#include "hotal.h"
#include "normaluser.h"
#include "hotaluser.h"
#include "platformuser.h"
#include <QDialog>
#include <QCloseEvent>

class QTextEdit;
class QLabel;
class QPushButton;
class QSpinBox;

class WritePinJia:public QDialog
{
    Q_OBJECT

public:
    WritePinJia(Hotal * hotal,Message *messagehead, PinJiaMessage *pinjiahead, QString receiveUser, NormalUser *Mainaccount1, QWidget *parent=0);
    bool ContinueToClose();
    ~WritePinJia(){}
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void EnableSend();
    void SendMessage();
private:
    QLabel *info;
    QLabel *HotalName1;
    QLabel *HotalName2;
    QLabel *pinjia1;
    QSpinBox *pinjia2;
    QLabel *message;
    QTextEdit *messagetext;
    QPushButton *SendButton;
    QPushButton *CancelButton;
    Hotal *thishotal;
    Message *Messagehead;
    PinJiaMessage *PinJiahead;
    NormalUser *MainAccount1;
    bool sent;
};

#endif // WRITEPINJIA_H
