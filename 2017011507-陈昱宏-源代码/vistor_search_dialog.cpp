/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：Vistor_Search_Dialog.cpp
 * 内容：实现Vistor_Search_Dialog类（该界面最后不会存在）
 * 版本：version_1.1
 * 作者：陈昱宏
 * 创建日期：2018/07/19
 */
#include "vistor_search_dialog.h"
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>
#include <QFormLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QCloseEvent>

Vistor_Search_Dialog::Vistor_Search_Dialog(QWidget *parent/*=0*/)
    :QDialog(parent)
{
    resize(640,400);

    info = new QLabel(tr("请输入你要搜寻的酒店条件"), this);
    info->setAlignment(Qt::AlignCenter);

    StartTime = new QLabel(tr("起始时间："), this);
    StartTime->setAlignment(Qt::AlignRight);
    StartTimeLineEdit = new QLineEdit;
    QRegExp regx("(^20[0-9]{2}-02-[0-2][0-9]$)"
                 "|(^20[0-9]{2}-0[1,3,5,7,8]-(([0-2][0-9])|3[0,1])$)"
                 "|(^20[0-9]{2}-0[4,6,9]-(([0-2][0-9])|30)$)"
                 "|^20[0-9]{2}-1[0,2]-(([0-2][0-9])|3[0,1])$"
                 "|(^20[0-9]{2}-11-(([0-2][0-9])|30)$)");
    QValidator *validator1 = new QRegExpValidator(regx, StartTimeLineEdit);
    StartTimeLineEdit->setValidator(validator1);
    StartTimeLineEdit->setPlaceholderText("2018-00-00");

    FinalTime = new QLabel(tr("结束时间："));
    FinalTime->setAlignment(Qt::AlignRight);
    FinalTimeLineEdit = new QLineEdit;
    QValidator *validator2 = new QRegExpValidator(regx, FinalTimeLineEdit);
    FinalTimeLineEdit->setValidator(validator2);
    FinalTimeLineEdit->setPlaceholderText("2018-00-00");

    area = new QLabel(tr("省份："), this);
    area->setAlignment(Qt::AlignRight);
    AreaComboBox = new QComboBox(this);
    AreaComboBox->addItem(" ");
    AreaComboBox->addItem(tr("北京市"));
    AreaComboBox->addItem(tr("天津市"));
    AreaComboBox->addItem(tr("上海市"));
    AreaComboBox->addItem(tr("重庆市"));
    AreaComboBox->addItem(tr("河北省"));
    AreaComboBox->addItem(tr("山西省"));
    AreaComboBox->addItem(tr("辽宁省"));
    AreaComboBox->addItem(tr("吉林省"));
    AreaComboBox->addItem(tr("黑龙江省"));
    AreaComboBox->addItem(tr("江苏省"));
    AreaComboBox->addItem(tr("浙江省"));
    AreaComboBox->addItem(tr("安徽省"));
    AreaComboBox->addItem(tr("福建省"));
    AreaComboBox->addItem(tr("江西省"));
    AreaComboBox->addItem(tr("山东省"));
    AreaComboBox->addItem(tr("河南省"));
    AreaComboBox->addItem(tr("湖北省"));
    AreaComboBox->addItem(tr("湖南省"));
    AreaComboBox->addItem(tr("广东省"));
    AreaComboBox->addItem(tr("海南省"));
    AreaComboBox->addItem(tr("四川省"));
    AreaComboBox->addItem(tr("贵州省"));
    AreaComboBox->addItem(tr("云南省"));
    AreaComboBox->addItem(tr("陕西省"));
    AreaComboBox->addItem(tr("甘肃省"));
    AreaComboBox->addItem(tr("青海省"));
    AreaComboBox->addItem(tr("内蒙古自治区"));
    AreaComboBox->addItem(tr("广西壮族自治区"));
    AreaComboBox->addItem(tr("西藏自治区"));
    AreaComboBox->addItem(tr("宁夏回族自治区"));
    AreaComboBox->addItem(tr("新疆维吾尔自治区"));
    AreaComboBox->addItem(tr("香港特别行政区"));
    AreaComboBox->addItem(tr("澳门特别行政区"));
    AreaComboBox->addItem(tr("台湾省"));

    SearchButton = new QPushButton(tr("搜寻"), this);
    SearchButton->setDefault(true);
    SearchButton->setEnabled(false);
    LoginButton = new QPushButton((tr("登入")), this);
    LoginButton->setDefault(true);
    RegisterButton = new QPushButton((tr("注册")), this);
    RegisterButton->setDefault(true);
    CancelButton = new QPushButton((tr("返回")), this);
    CancelButton->setDefault(true);


    connect(AreaComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(enableSearch(int)));
    connect(LoginButton,SIGNAL(clicked()),this,SLOT(ShowLoginDialog()));
    connect(RegisterButton,SIGNAL(clicked()),this,SLOT(ShowRegisterDialog()));
    connect(CancelButton,SIGNAL(clicked()),this,SLOT(ShowWelcomeWindow()));

    QFormLayout *formlayout = new QFormLayout;
    formlayout->addRow(StartTime, StartTimeLineEdit);
    formlayout->addRow(FinalTime, FinalTimeLineEdit);
    formlayout->addRow(area, AreaComboBox);

    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->addLayout(formlayout,0,0,1,5);
    gridlayout->addWidget(SearchButton,1,0,1,1);
    gridlayout->addWidget(LoginButton,1,2,1,1);
    gridlayout->addWidget(RegisterButton,1,4,1,1);
    gridlayout->addWidget(CancelButton,2,0,1,5);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->addStretch(2);
    mainlayout->addWidget(info);
    mainlayout->addStretch(1);
    mainlayout->addLayout(gridlayout);
    mainlayout->addStretch(2);

    setLayout(mainlayout);
    setWindowTitle(tr("搜寻"));
}

bool Vistor_Search_Dialog::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("退出？"),tr("亲，确定不搜寻吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Vistor_Search_Dialog::~Vistor_Search_Dialog()
{

}

void Vistor_Search_Dialog::enableSearch(int index)
{
    SearchButton->setEnabled(index != 0);
}

void Vistor_Search_Dialog::ShowLoginDialog()
{
    this->hide();
    emit ShowLogin();
}

void Vistor_Search_Dialog::ShowRegisterDialog()
{
    this->hide();
    emit ShowRegister();
}

void Vistor_Search_Dialog::ShowWelcomeWindow()
{
    StartTimeLineEdit->setText("\0");
    FinalTimeLineEdit->setText("\0");
    AreaComboBox->setCurrentIndex(0);
    this->close();
    emit ShowWelcome();
}

void Vistor_Search_Dialog::closeEvent(QCloseEvent *event)
{
    if (ContinueToClose())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
