#ifndef ROOMDETAIL_H
#define ROOMDETAIL_H

#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "hotal.h"
#include "room.h"

class QLabel;
class QPushButton;
class QLineEdit;
class QDateTimeEdit;

class RoomDetail:public QDialog
{
    Q_OBJECT

public:
    RoomDetail(Hotal *ptr, QString roomtype,QWidget *parent=0);
    ~RoomDetail(){}
private slots:
    void changeTotalNum();
    void changeRoomNum();
    void changemoney();
private:
    QLabel *info;
    QLabel *picture;
    QLabel *hotalname1;
    QLabel *hotalname2;
    QLabel *RoomType1;
    QLabel *RoomType2;
    QLabel *text2;
    QLabel *date_1;
    QDateTimeEdit *date_2;
    QLabel *TotalNum1;
    QLabel *TotalNum2;
    QLabel *text;
    QLabel *date1;
    QDateTimeEdit *date2;
    QLabel *RoomNum1;
    QLabel *RoomNum2;
    QLabel *text1;
    QLabel *Date1;
    QDateTimeEdit *Date2;
    QLabel *MoneyPerNight1;
    QLabel *MoneyPerNight2;
    QPushButton *OkButton;
    Hotal *thishotal;
    QString Roomtype;
};

#endif // ROOMDETAIL_H
