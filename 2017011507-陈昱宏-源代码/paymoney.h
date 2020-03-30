#ifndef PAYMONEY_H
#define PAYMONEY_H

#include <QDialog>
#include "hotalorder.h"
#include "normaluser.h"
#include "hotaluser.h"
#include "platformuser.h"

class QLabel;
class QLineEdit;
class QPushButton;

class PayMoney:public QDialog
{
    Q_OBJECT

public:
    PayMoney(HotalOrder *order,QString Paytype,NormalUser *Mainaccount1,HotalUser *Mainaccount2,PlatformUser *Mainaccount3,QWidget *parent=0);
    bool ContinueToClose();
    ~PayMoney(){}
protected:
    void closeEvent(QCloseEvent *);
private slots:
    void Pay();
private:
    QLabel *info;
    QLabel *PayType;
    QLabel *money1;
    QLabel *BankAccount1;
    QLineEdit *BankAccount2;
    QLabel *BankPassword1;
    QLineEdit *BankPassword2;
    QPushButton *PayButton;
    QPushButton *CancelButton;
    HotalOrder *Order;
    NormalUser *MainAccount1;
    HotalUser *MainAccount2;
    PlatformUser *MainAccount3;
    bool successful;
};

#endif // PAYMONEY_H
