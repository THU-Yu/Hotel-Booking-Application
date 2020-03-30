#ifndef CHANGEROOM_H
#define CHANGEROOM_H

#include <QDialog>
#include "hotal.h"
#include "room.h"

class QLabel;
class QComboBox;
class QDateTimeEdit;
class QLineEdit;
class QCheckBox;

class ChangeRoom:public QDialog
{
    Q_OBJECT

public:
    ChangeRoom(Hotal *hotel,Room *roomhead,QWidget *parent=0);
    bool ContinueToClose();
    ~ChangeRoom(){}
protected:
    void closeEvent(QCloseEvent *);
private slots:
    void Change();
    void ChangeTotalNum();
    void ChangeRoomNum();
    void EnableChange();
    void ChangeMoney();
private:
    QLabel *info;
    QLabel *RoomType1;
    QComboBox *RoomType2;
    QLabel *TotalNumInfo;
    QLabel *TotalNum1;
    QLineEdit *TotalNum2;
    QLabel *date1;
    QDateTimeEdit *date2;
    QLabel *RoomNumInfo;
    QLabel *RoomNum1;
    QLineEdit *RoomNum2;
    QLabel *Date1;
    QDateTimeEdit *Date2;
    QLabel *MoneyPerNightInfo;
    QLabel *MoneyPerNight1;
    QLineEdit *MoneyPerNight2;
    QLabel *Date3;
    QDateTimeEdit *Date4;
    QCheckBox *totalchange;
    QCheckBox *roomnumchange;
    QCheckBox *moneychange;
    QPushButton *ChangeButton;
    QPushButton *CancelButton;
    Hotal *thishotel;
    Room *Roomhead;
    bool successful;
};

#endif // CHANGEROOM_H
