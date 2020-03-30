#include "mainwindow.h"
#include "emptywidget.h"
#include "sendmessagedialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QPushButton>

MainWindow::MainWindow(NormalUser *user1, HotalUser *user2, PlatformUser *user3, Hotal *h, HotalOrder *o, Room *r, Message *m, PinJiaMessage *p, Search *search, Search_Dialog *sd, PersonalInfo *personalinfo, PlatformManage *platformmanage, SearchOrder *searchorder1, SearchOrder *searchorder2, HotalManage *h0, HotalManage *h1, HotalManage *h2, HotalManage *h3, HotalManage *h4, ReceiveMessage *rm, QWidget *parent)
    :MainAccount1(user1),MainAccount2(user2),MainAccount3(user3),Hotalhead(h),Orderhead(o),Roomhead(r),
      Messagehead(m),PinJiahead(p),topSearch(search),leftSearch(sd),personalinfo(personalinfo),platformmanage(platformmanage),
      searchorder1(searchorder1), searchorder2(searchorder2), hotalmanage0(h0), hotalmanage1(h1), hotalmanage2(h2),
      hotalmanage3(h3), hotalmanage4(h4),receivemessage(rm), searchtime(0),logintime(0), QMainWindow(parent)
{
    QFont font;
    font.setPointSize(10);
    //字体修改为FangSong(仿宋)(version_1.1)
    font.setFamily(("FangSong"));

    QDockWidget *topdock = new QDockWidget(this);
    QWidget *nontitle1 = new QWidget;
    topdock->setTitleBarWidget(nontitle1);
    topdock->setAllowedAreas(Qt::TopDockWidgetArea);
    topdock->setWidget(topSearch);
    topdock->setMaximumHeight(160);
    topdock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::TopDockWidgetArea, topdock);

    leftbox = new QToolBox;
    leftSearch->setFont(font);
    leftbox->addItem(leftSearch, tr("搜寻酒店"));
    leftList = new QListWidget(leftbox);
    leftList->addItem(tr(""));
    leftList->addItem(tr("修改个人资料"));
    leftList->addItem(tr("查询订单资讯"));
    leftList->addItem(tr("修改酒店资讯"));
    leftList->addItem(tr("所有订单资讯"));
    leftList->addItem(tr("所有酒店资讯"));
    leftList->addItem(tr("收到的消息"));
    leftList->addItem(tr("平台管理"));
    leftList->addItem("");
    leftList->item(0)->setHidden(true);
    leftList->item(1)->setHidden(true);
    leftList->item(2)->setHidden(true);
    leftList->item(3)->setHidden(true);
    leftList->item(4)->setHidden(true);
    leftList->item(5)->setHidden(true);
    leftList->item(6)->setHidden(true);
    leftList->item(7)->setHidden(true);
    leftList->item(8)->setHidden(true);
    leftbox->addItem(leftList, tr("个人资料"));

    QDockWidget *leftDock = new QDockWidget;
    //让leftDock不显示标题
    QWidget* titleWidget2 = new QWidget(leftDock);
    leftDock->setTitleBarWidget(titleWidget2);
    leftDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    leftDock->setWidget(leftbox);
    leftDock->setMinimumSize(185,700);
    leftDock->setMaximumSize(185,700);
    leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);

    QDockWidget *bottomDock = new QDockWidget;
    //让bottomDock不显示标题
    QWidget* titleWidget3 = new QWidget(bottomDock);
    bottomDock->setTitleBarWidget(titleWidget3);
    bottomDock->setAllowedAreas(Qt::BottomDockWidgetArea);
    //让bottomDock不显示内容
    ReflashButton = new QPushButton(tr("刷新"));
    KeFuButton = new QPushButton(tr("客服"));
    QVBoxLayout *vboxlayout = new QVBoxLayout;
    vboxlayout->addWidget(ReflashButton);
    vboxlayout->addWidget(KeFuButton);
    KeFuButton->setVisible(false);
    QWidget *widget = new QWidget;
    widget->setLayout(vboxlayout);
    bottomDock->setWidget(widget);
    bottomDock->setMinimumSize(185,100);
    bottomDock->setMaximumSize(185,100);
    bottomDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::BottomDockWidgetArea, bottomDock);

    hotalmanage0->changeHotalManage(MainAccount1,nullptr,nullptr);
    hotalmanage4->changeHotalManage(MainAccount1,nullptr,nullptr,new QDate(QDate::currentDate()),new QDate(QDate::currentDate().addDays(1)),"北京市");

    stack = new QStackedWidget;
    stack->addWidget(hotalmanage0);
    stack->addWidget(hotalmanage4);
    setCentralWidget(stack);

    connect(leftList,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrentIndex(int)));
    connect(this,SIGNAL(back(int)),stack,SLOT(setCurrentIndex(int)));
    connect(ReflashButton,SIGNAL(clicked()),this,SLOT(reflash()));
    connect(KeFuButton,SIGNAL(clicked()),this,SLOT(KeFu()));

    setGeometry(400,40,400,800);
}

MainWindow::~MainWindow()
{

}

bool MainWindow::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("登出？"),tr("确定要登出吗？\n登出前请先确认所有变更已经保存！"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        if (QMessageBox::information(NULL,tr("登出"),tr("成功登出！"),QMessageBox::Ok) == QMessageBox::Ok)
        {
            return true;
        }
    }
    return false;
}

void MainWindow::RealLogin(NormalUser *&ptr)
{
    topSearch->ResetSearch();
    leftSearch->ResetSearch();
    MainAccount1 = ptr;
    KeFuButton->setVisible(true);
    topSearch->setWelcome((MainAccount1)->getaccount() + "，您好！");
    topSearch->setLogin_and_Logout("登出");

    personalinfo->changePersonalInfo(MainAccount1,MainAccount2,MainAccount3);

    platformmanage->changePlatfoemManage();

    stack->removeWidget(hotalmanage4);

    if ((logintime == 0) && (searchtime == 0))
    {
        searchorder1->changeSearchOrder(MainAccount1,MainAccount2,MainAccount3);
        searchorder2->changeSearchOrder(MainAccount1,MainAccount2,MainAccount3);

        hotalmanage1->changeHotalManage(MainAccount1,nullptr,nullptr);
        hotalmanage2->changeHotalManage(MainAccount1,MainAccount2,MainAccount3);
        hotalmanage3->changeHotalManage(MainAccount1,MainAccount2,MainAccount3);

        receivemessage->changeReceiveMessage(MainAccount1,MainAccount2,MainAccount3);
    }
    else
    {
        searchorder1->changeTable(MainAccount1,MainAccount2,MainAccount3);
        searchorder2->changeTable(MainAccount1,MainAccount2,MainAccount3);

        hotalmanage1->changeMainTable(MainAccount1,nullptr,nullptr);
        hotalmanage2->changeMainTable(MainAccount1,MainAccount2,MainAccount3);
        hotalmanage3->changeMainTable(MainAccount1,MainAccount2,MainAccount3);

        receivemessage->changeMainTable(MainAccount1,MainAccount2,MainAccount3);
    }
    leftList->item(1)->setHidden(false);
    leftList->item(2)->setHidden(false);
    leftList->item(6)->setHidden(false);

    stack->removeWidget(hotalmanage0);
    stack->addWidget(hotalmanage1);
    stack->addWidget(personalinfo);
    stack->addWidget(searchorder1);
    stack->addWidget(hotalmanage2);
    stack->addWidget(searchorder2);
    stack->addWidget(hotalmanage3);
    stack->addWidget(receivemessage);
    stack->addWidget(platformmanage);
    stack->addWidget(hotalmanage4);
    show();
}

void MainWindow::RealLogin(HotalUser *&ptr)
{
    topSearch->ResetSearch();
    leftSearch->ResetSearch();
    MainAccount2 = ptr;
    KeFuButton->setVisible(true);
    topSearch->setWelcome((MainAccount2)->getaccount() + "，您好！");
    topSearch->setLogin_and_Logout("登出");

    personalinfo->changePersonalInfo(MainAccount1,MainAccount2,MainAccount3);

    platformmanage->changePlatfoemManage();

    stack->removeWidget(hotalmanage4);

    if ((logintime == 0) && (searchtime == 0))
    {
        searchorder1->changeSearchOrder(MainAccount1,MainAccount2,MainAccount3);
        searchorder2->changeSearchOrder(MainAccount1,MainAccount2,MainAccount3);

        hotalmanage1->changeHotalManage(MainAccount1,nullptr,nullptr);
        hotalmanage2->changeHotalManage(MainAccount1,MainAccount2,MainAccount3);
        hotalmanage3->changeHotalManage(MainAccount1,MainAccount2,MainAccount3);

        receivemessage->changeReceiveMessage(MainAccount1,MainAccount2,MainAccount3);
    }
    else
    {
        searchorder1->changeTable(MainAccount1,MainAccount2,MainAccount3);
        searchorder2->changeTable(MainAccount1,MainAccount2,MainAccount3);

        hotalmanage1->changeMainTable(MainAccount1,nullptr,nullptr);
        hotalmanage2->changeMainTable(MainAccount1,MainAccount2,MainAccount3);
        hotalmanage3->changeMainTable(MainAccount1,MainAccount2,MainAccount3);

        receivemessage->changeMainTable(MainAccount1,MainAccount2,MainAccount3);
    }

    leftList->item(1)->setHidden(false);
    leftList->item(2)->setHidden(false);
    leftList->item(3)->setHidden(false);
    leftList->item(6)->setHidden(false);

    stack->removeWidget(hotalmanage0);
    stack->addWidget(hotalmanage1);
    stack->addWidget(personalinfo);
    stack->addWidget(searchorder1);
    stack->addWidget(hotalmanage2);
    stack->addWidget(searchorder2);
    stack->addWidget(hotalmanage3);
    stack->addWidget(receivemessage);
    stack->addWidget(platformmanage);
    stack->addWidget(hotalmanage4);
    show();
}

void MainWindow::RealLogin(PlatformUser *&ptr)
{
    topSearch->ResetSearch();
    leftSearch->ResetSearch();
    MainAccount3 = ptr;
    KeFuButton->setVisible(false);
    topSearch->setWelcome((MainAccount3)->getaccount() + "，您好！");
    topSearch->setLogin_and_Logout("登出");

    personalinfo->changePersonalInfo(MainAccount1,MainAccount2,MainAccount3);

    platformmanage->changePlatformUser(MainAccount3);
    platformmanage->changePlatfoemManage();

    stack->removeWidget(hotalmanage4);

    if ((logintime == 0) && (searchtime == 0))
    {
        searchorder1->changeSearchOrder(MainAccount1,MainAccount2,MainAccount3);
        searchorder2->changeSearchOrder(MainAccount1,MainAccount2,MainAccount3);

        hotalmanage1->changeHotalManage(MainAccount1,nullptr,nullptr);
        hotalmanage2->changeHotalManage(MainAccount1,MainAccount2,MainAccount3);
        hotalmanage3->changeHotalManage(MainAccount1,MainAccount2,MainAccount3);

        receivemessage->changeReceiveMessage(MainAccount1,MainAccount2,MainAccount3);
    }
    else
    {
        searchorder1->changeTable(MainAccount1,MainAccount2,MainAccount3);
        searchorder2->changeTable(MainAccount1,MainAccount2,MainAccount3);

        hotalmanage1->changeMainTable(MainAccount1,nullptr,nullptr);
        hotalmanage2->changeMainTable(MainAccount1,MainAccount2,MainAccount3);
        hotalmanage3->changeMainTable(MainAccount1,MainAccount2,MainAccount3);

        receivemessage->changeMainTable(MainAccount1,MainAccount2,MainAccount3);
    }

    leftList->item(1)->setHidden(false);
    leftList->item(4)->setHidden(false);
    leftList->item(5)->setHidden(false);
    leftList->item(6)->setHidden(false);
    leftList->item(7)->setHidden(false);

    stack->removeWidget(hotalmanage0);
    stack->addWidget(hotalmanage1);
    stack->addWidget(personalinfo);
    stack->addWidget(searchorder1);
    stack->addWidget(hotalmanage2);
    stack->addWidget(searchorder2);
    stack->addWidget(hotalmanage3);
    stack->addWidget(receivemessage);
    stack->addWidget(platformmanage);
    stack->addWidget(hotalmanage4);
    show();
}

void MainWindow::RealLogout()
{
    KeFuButton->setVisible(false);
    topSearch->setWelcome("\0");
    topSearch->setLogin_and_Logout("登入");
    MainAccount1 = nullptr;
    MainAccount2 = nullptr;
    MainAccount3 = nullptr;
    leftList->item(0)->setHidden(true);
    leftList->item(1)->setHidden(true);
    leftList->item(2)->setHidden(true);
    leftList->item(3)->setHidden(true);
    leftList->item(4)->setHidden(true);
    leftList->item(5)->setHidden(true);
    leftList->item(6)->setHidden(true);
    leftList->item(7)->setHidden(true);
    stack->removeWidget(hotalmanage1);
    stack->removeWidget(personalinfo);
    stack->removeWidget(searchorder1);
    stack->removeWidget(hotalmanage2);
    stack->removeWidget(searchorder2);
    stack->removeWidget(hotalmanage3);
    stack->removeWidget(receivemessage);
    stack->removeWidget(platformmanage);
    stack->removeWidget(hotalmanage4);

    hotalmanage0->changeMainTable(MainAccount1,MainAccount2,MainAccount3);
    hotalmanage4->changeMainTable(MainAccount1,MainAccount2,MainAccount3);
    stack->addWidget(hotalmanage0);
    stack->addWidget(hotalmanage4);

    leftList->setCurrentRow(0);

    topSearch->ResetSearch();
    leftSearch->ResetSearch();
    hotalmanage0->Reset();
    hotalmanage1->Reset();
    hotalmanage2->Reset();
    hotalmanage3->Reset();

    logintime ++;
}

void MainWindow::Back()
{
    emit back(0);
    leftList->setCurrentRow(0);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (topSearch->getStatus() == "登入")
    {
        if (QMessageBox::question(NULL,tr("退出？"),tr("这么优质的系统不继续看会吗？\n确定要退出？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
        {
            event->accept();
            emit showWelcome();
        }
        else
        {
            event->ignore();
        }
    }
    else if (ContinueToClose())
    {
        event->accept();
        emit showWelcome();
        RealLogout();
    }
    else
    {
        event->ignore();
    }
}


void MainWindow::reflash()
{
    if ((MainAccount1)||(MainAccount2)||(MainAccount3))
    {
        personalinfo->changePersonalInfo(MainAccount1,MainAccount2,MainAccount3);

        platformmanage->changePlatfoemManage();
        platformmanage->changePlatformUser(MainAccount3);

        searchorder1->changeTable(MainAccount1,MainAccount2,MainAccount3);
        searchorder2->changeTable(MainAccount1,MainAccount2,MainAccount3);

        hotalmanage1->changeMainTable(MainAccount1,nullptr,nullptr);
        hotalmanage2->changeMainTable(MainAccount1,MainAccount2,MainAccount3);
        hotalmanage3->changeMainTable(MainAccount1,MainAccount2,MainAccount3);

        receivemessage->changeMainTable(MainAccount1,MainAccount2,MainAccount3);
    }
}

void MainWindow::searchHotal(QString s1, QString s2, QString s3)
{
    hotalmanage4->changeMainTable(MainAccount1,nullptr,nullptr,new QDate(QDate::fromString(s1,"yyyy-MM-dd")),new QDate(QDate::fromString(s2,"yyyy-MM-dd")),s3);
    if ((!MainAccount1) && (!MainAccount2) &&(!MainAccount3))
    {
        emit back(1);
    }
    else
    {
        emit back(8);
    }
    leftList->setCurrentRow(8);
}

void MainWindow::KeFu()
{
    SendMessageDialog *sent = new SendMessageDialog(Messagehead,"2017011507",MainAccount1,MainAccount2,MainAccount3);
    sent->exec();
}
