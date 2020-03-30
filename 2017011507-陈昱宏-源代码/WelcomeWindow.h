/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：WelcomeWindow.h
 * 内容：声明WelcomeWindow类（欢迎界面）
 * 版本：version_1.0
 * 作者：陈昱宏
 * 创建日期：2018/07/18
 *
 * 版本：version_1.1
 * 修改部分：增加新信号槽、增加关闭提示
 * 修改者：陈昱宏（上版本作者：陈昱宏）
 * 修改日期：2018/07/19
 */

#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H


#include "normaluser.h"
#include "hotaluser.h"
#include "platformuser.h"
#include "hotal.h"
#include "hotalorder.h"
#include "room.h"
#include "message.h"
#include "PinJiaMessage.h"
#include <QMainWindow>


class QLabel;
class QPushButton;

class WelcomeWindow : public QMainWindow //声明WelcomeWindow类，单继承自QMainWindow类
{
    Q_OBJECT

public:
    WelcomeWindow(NormalUser *Mainaccount2, HotalUser *Mainaccount3, PlatformUser *Mainaccount1,Hotal *h,HotalOrder *o,
                  Room *r,Message *m,PinJiaMessage *p, QWidget *parent = 0); //构造函数
    bool ContinueToClose(); //判定是否确认关闭(version_1.1)
    ~WelcomeWindow(); //析构函数
signals:
    void showLoginDialog(); //显示登入界面的信号
    void showRegisterDialog(); //显示注册界面的信号
    void showVistorDialog(); //显示访客界面的信号(version_1.1)
protected:
    void closeEvent(QCloseEvent *event); //捕捉关闭事件(version_1.1)
private slots:
    void Login(); //接收loginbutton的clicked()信号
    void Rigistr(); //接收registerbutton的clicked()信号
    void Vistor(); //接收vistorbutton的clicked()信号(version_1.1)
    void Quit(); //接收quitbutton的clicked()信号
    void ResetWelcome();
private:
    QLabel *label; //欢迎信息标签
    QPushButton *loginbutton; //登入按钮
    QPushButton *registerbutton; //注册按钮
    QPushButton *quitbutton; //退出按钮
    QPushButton *vistorbutton; //访客按钮
    NormalUser *MainAccount1;
    HotalUser *MainAccount2;
    PlatformUser *MainAccount3;
    Hotal *Hotalhead;
    HotalOrder *Orderhead;
    Room *Roomhead;
    Message *Messagehead;
    PinJiaMessage *PinJiahead;
};

#endif // WELCOMEWINDOW_H
