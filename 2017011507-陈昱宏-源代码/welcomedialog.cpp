#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QMessageBox>
#include "WelcomeDialog.h"
#include "Login_Dialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent)
    :QDialog(parent)
{
    /*setMaximumSize(800,1200);
    setMinimumSize(400,600);*/

    label = new QLabel(tr("欢迎来到C&W酒店预定系统~"));
    label->setAlignment(Qt::AlignCenter);

    loginbutton = new QPushButton(tr("登入"));
    registerbutton = new QPushButton(tr("注册"));
    quitbutton = new QPushButton(tr("退出"));
    vistorbutton = new QPushButton(tr("访客"));

    connect(loginbutton,SIGNAL(clicked()),this,SLOT(Login()));
    connect(registerbutton,SIGNAL(clicked()),this,SLOT(Rigistr()));
    connect(quitbutton,SIGNAL(clicked()),this,SLOT(Quit()));
    connect(this,SIGNAL(clickYes()),this,SLOT(close()));

    QHBoxLayout *toplayout = new QHBoxLayout;
    toplayout->addStretch();
    toplayout->addWidget(label);
    toplayout->addStretch();

    QHBoxLayout *midlayout = new QHBoxLayout;
    midlayout->addStretch();
    midlayout->addWidget(loginbutton);
    midlayout->addWidget(registerbutton);
    midlayout->addStretch();

    QHBoxLayout *lastlayout = new QHBoxLayout;
    lastlayout->addStretch();
    lastlayout->addWidget(vistorbutton);
    lastlayout->addWidget(quitbutton);
    lastlayout->addStretch();

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addStretch();
    mainlayout->addLayout(toplayout);
    mainlayout->addStretch();
    mainlayout->addLayout(midlayout);
    mainlayout->addLayout(lastlayout);
    mainlayout->addStretch();

    setLayout(mainlayout);
    setWindowTitle(tr("C&W酒店预定"));
}

WelcomeDialog::~WelcomeDialog()
{
    delete label;
    delete loginbutton;
    delete registerbutton;
    delete quitbutton;
    delete vistorbutton;
}

void WelcomeDialog::Login()
{
    this->hide();
    emit showLoginDialog();
}

void WelcomeDialog::Rigistr()
{

}

void WelcomeDialog::Quit()
{
    if (QMessageBox::question(NULL,tr("退出？"),tr("确定要退出吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        emit clickYes();
    }
}

