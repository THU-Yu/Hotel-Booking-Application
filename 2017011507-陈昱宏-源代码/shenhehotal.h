#ifndef SHENHEHOTAL_H
#define SHENHEHOTAL_H

#include <QMainWindow>
#include "hotal.h"
#include "hotaldetail.h"
#include "message.h"

class QTableWidget;
class QTableWidgetItem;
class QPushButton;

class ShenHeHotal:public QMainWindow
{
    Q_OBJECT

public:
    ShenHeHotal(Hotal *hotalhead, Message *messagehead, QWidget *parent=0);
    ~ShenHeHotal(){}
private slots:
    void ButtonClicked(QTableWidgetItem *item);
private:
    QLabel *info;
    QTableWidget *MainTable;
    Hotal *Hotalhead;
    Message *Messagehead;
    HotalDetail *hotaldetail;
    QPushButton *BackButton;
};

#endif // SHENHEHOTAL_H
