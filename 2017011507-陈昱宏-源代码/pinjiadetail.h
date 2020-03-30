#ifndef PINJIADETAIL_H
#define PINJIADETAIL_H

#include <QDialog>
#include "PinJiaMessage.h"
#include "messagedetail.h"

class QLabel;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;

class PinJiaDetail:public QDialog
{
    Q_OBJECT

public:
    PinJiaDetail(PinJiaMessage *ptr, QWidget *parent=0);
    ~PinJiaDetail(){}
private slots:
    void ButtonClicked(QTableWidgetItem *item);
private:
    QLabel *info;
    QLabel *user1;
    QLabel *user2;
    QLabel *pinjia1;
    QLabel *pinjia2;
    QLabel *message1;
    QTableWidget *message2;
    QPushButton *OkButton;
    PinJiaMessage *PinJia;
    MessageDetail *messagedetail;
};

#endif // PINJIADETAIL_H
