#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "normaluser.h"
#include "hotaluser.h"
#include "platformuser.h"
#include "hotal.h"
#include "hotalorder.h"
#include "PinJiaMessage.h"
#include "search.h"
#include "search_dialog.h"
#include "personalinfo.h"
#include "platformmanage.h"
#include "searchorder.h"
#include "hotalmanage.h"
#include "receivemessage.h"
#include <QMainWindow>
#include <QToolBox>
#include <QStackedWidget>
#include <QListWidget>
#include <QDockWidget>

class EmptyWidget;
class QPushButton;

class MainWindow:public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(NormalUser *user1, HotalUser *user2, PlatformUser *user3, Hotal *h, HotalOrder *o,
               Room *r, Message *m, PinJiaMessage *p, Search *search, Search_Dialog *sd,
               PersonalInfo *personalinfo, PlatformManage *platformmanage, SearchOrder *searchorder1,
               SearchOrder *searchorder2, HotalManage *h0, HotalManage *h1, HotalManage *h2,
               HotalManage *h3, HotalManage *h4, ReceiveMessage *rm,QWidget *parent=0);
    bool ContinueToClose();
    ~MainWindow();
signals:
    void back(int);
    void showWelcome();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void RealLogin(NormalUser *&ptr);
    void RealLogin(HotalUser *&);
    void RealLogin(PlatformUser *&);
    void RealLogout();
    void Back();
    void reflash();
    void searchHotal(QString,QString,QString);
    void KeFu();
private:
    QToolBox *leftbox;
    QListWidget *leftList;
    QStackedWidget *stack;
    Search *topSearch;
    Search_Dialog *leftSearch;
    NormalUser *MainAccount1;
    HotalUser *MainAccount2;
    PlatformUser *MainAccount3;
    Hotal *Hotalhead;
    HotalOrder *Orderhead;
    Room *Roomhead;
    Message *Messagehead;
    PinJiaMessage *PinJiahead;
    PersonalInfo *personalinfo;
    PlatformManage *platformmanage;
    SearchOrder *searchorder1;
    SearchOrder *searchorder2;
    HotalManage *hotalmanage0;
    HotalManage *hotalmanage1;
    HotalManage *hotalmanage2;
    HotalManage *hotalmanage3;
    HotalManage *hotalmanage4;
    ReceiveMessage *receivemessage;
    QPushButton *ReflashButton;
    QPushButton *KeFuButton;
    int logintime;
    int searchtime;
};

#endif // MAINWINDOW_H
