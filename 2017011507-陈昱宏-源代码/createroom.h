#ifndef CREATEROOM_H
#define CREATEROOM_H

#include <QDialog>
#include "room.h"
#include "hotal.h"

class QLabel;
class QLineEdit;
class QPushButton;

class CreateRoom:public QDialog
{
    Q_OBJECT

public:
    CreateRoom(Hotal *hotal,Room *roomhead, QWidget *parent=0);
    bool ContinueToClose();
    ~CreateRoom(){}
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void EnableClick();
    void Create();
private:
    QLabel *info;
    QLabel *RoomType1;
    QLineEdit *RoomType2;
    QLabel *TotalNum1;
    QLineEdit *TotalNum2;
    QLabel *MoneyPerNight1;
    QLineEdit *MoneyPerNight2;
    QPushButton *CreateButton;
    QPushButton *CancelButton;
    Hotal *thishotal;
    Room *Roomhead;
    bool successful;
};

#endif // CREATEROOM_H
