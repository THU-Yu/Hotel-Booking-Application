#ifndef CHANGEHOTALINFO_H
#define CHANGEHOTALINFO_H

#include <QDialog>
#include "hotal.h"

class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;
class QTextEdit;

class ChangeHotalInfo:public QDialog
{
    Q_OBJECT

public:
    ChangeHotalInfo(Hotal *h,QWidget *parent=0);
    bool ContinueToClose();
    ~ChangeHotalInfo(){}
protected:
    void closeEvent(QCloseEvent *);
private slots:
    void Change();
private:
    QLabel *info;
    QLabel *hotalname1;
    QLineEdit *hotalname2;
    QLabel *Area1;
    QComboBox *AreaComboBox;
    QLabel *HotalTel1;
    QLineEdit *HotalTel2;
    QLabel *hotalinfo1;
    QTextEdit *hotalinfo2;
    QPushButton *ChangeButton;
    QPushButton *CancelButton;
    Hotal *hotal;
    bool change;
};

#endif // CHANGEHOTALINFO_H
