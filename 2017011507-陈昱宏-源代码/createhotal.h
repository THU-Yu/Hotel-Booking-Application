#ifndef CREATEHOTAL_H
#define CREATEHOTAL_H

#include <QDialog>
#include "hotal.h"
#include "message.h"
#include "hotaluser.h"

class QLabel;
class QPushButton;
class QLineEdit;
class QTextEdit;
class QComboBox;

class CreateHotal:public QDialog
{
    Q_OBJECT

public:
    CreateHotal(Hotal *hotalhead,Message *messagehead,HotalUser *Mainaccount,QWidget *parent=0);
    bool ContinueToClose();
    ~CreateHotal(){}
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void EnableClick();
    void Create();
private:
    QLabel *info;
    QLabel *HotalName1;
    QLineEdit *HotalName2;
    QLabel *HotalTel1;
    QLineEdit *HotalTel2;
    QLabel *Area1;
    QComboBox *AreaComboBox;
    QLabel *HotalInfo1;
    QTextEdit *HotalInfo2;
    QPushButton *CreateButton;
    QPushButton *CancelButton;
    Hotal *Hotalhead;
    Message *Messagehead;
    HotalUser *MainAccount;
    bool successful;
};

#endif // CREATEHOTAL_H
