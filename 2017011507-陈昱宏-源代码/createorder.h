#ifndef CREATEORDER_H
#define CREATEORDER_H

#include <QDialog>
#include "hotal.h"
#include "message.h"
#include "room.h"
#include "hotalorder.h"
#include "normaluser.h"

class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;
class QDateTimeEdit;
class QSpinBox;

class CreateOrder:public QDialog
{
    Q_OBJECT

public:
    CreateOrder(Hotal *hotalhead,Room *roomhead,Message *messagehead,HotalOrder *orderhead,Hotal *hotal,NormalUser *Mainaccount,QWidget *parent=0);
    bool ContinueToClose();
    ~CreateOrder(){}
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void EnableClick();
    void MoneyChange(QString);
    void moneychange();
    void ChangeFinalDay();
    void ChangeSpinBoxRange();
    void Create();
private:
    QLabel *info;
    QLabel *Ordernum1;
    QString Ordernum2;
    QLabel *HotalName;
    QLabel *RoomType1;
    QComboBox *RoomType2;
    QLabel *Start1;
    QDateTimeEdit *Start2;
    QLabel *Final1;
    QDateTimeEdit *Final2;
    QLabel *money1;
    QLineEdit *money2;
    QLabel *RoomNum1;
    QSpinBox *RoomNum2;
    QPushButton *CreateButton;
    QPushButton *CancelButton;
    Hotal *Hotalhead;
    Hotal *thishotal;
    Room *Roomhead;
    Message *Messagehead;
    HotalOrder *Orderhead;
    NormalUser *MainAccount;
    bool successful;
};

#endif // CREATEORDER_H
