#ifndef HOTALDETAIL_H
#define HOTALDETAIL_H

#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "hotal.h"

class QLabel;
class QPushButton;
class QTableWidget;
class QTextEdit;
class QTableWidgetItem;

class HotalDetail:public QDialog
{
    Q_OBJECT

public:
    HotalDetail(Hotal *ptr,QWidget *parent=0);
    ~HotalDetail(){}
private slots:
    void ButtonClicked(QTableWidgetItem *item);
    void buttonclicked(QTableWidgetItem *item);
private:
    QLabel *info;
    QLabel *picture;
    QLabel *hotalname1;
    QLabel *hotalaccount1;
    QLabel *hotalname2;
    QLabel *hotalaccount2;
    QLabel *hotaltel;
    QLabel *HotalTel;
    QLabel *hotalinfo;
    QTextEdit *HotalInfo;
    QLabel *RoomType;
    QTableWidget *room;
    QLabel *PinJia;
    QTableWidget *pinjia;
    QLabel *ordernum;
    QLabel *Successful1;
    QLabel *Successful2;
    QPushButton *OkButton;
    QGridLayout *gridlayout;
    QHBoxLayout *hboxlayout;
    QVBoxLayout *mainlayout;
    Hotal *hotal;
};

#endif // HOTALDETAIL_H
