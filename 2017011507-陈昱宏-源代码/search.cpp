/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：Search.cpp
 * 内容：实现Search类（搜寻功能的窗口，用于嵌入主画面）
 * 版本：version_1.1
 * 作者：陈昱宏
 * 创建日期：2018/07/19
 */
#include "search.h"
#include <QComboBox>
#include <QDateTimeEdit>
#include <QImage>
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>
#include <QFormLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPalette>

Search::Search(QWidget *parent/*=0*/) //构造函数实现
    :QWidget(parent)
{
    //设置Logo
    Logo = new QLabel(this);
    //设置Logo大小
    Logo->setGeometry(0,0,16,9);
    //设置Logo图片
    QPixmap Image(":/Logo.jpg");
    //图片缩放
    QPixmap newImage = Image.scaled(640,360).scaled(160,90,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //不随视窗放大
    Logo->setScaledContents(false);
    //设置Logo上的图片
    Logo->setPixmap(newImage);

    //info初始化
    info = new QLabel(tr("请输入你要搜寻的酒店条件:"),this);
    info->setAlignment(Qt::AlignRight); //设置右对齐

    Welcome = new QLabel;
    Welcome->setAlignment(Qt::AlignRight);

    Login_and_Logout = new QPushButton(tr("登入"));

    //StartTime和StartTimeLineEdit初始化(version_1.2)
    StartTime = new QLabel(tr("起始日期："),this);
    StartTime->setAlignment(Qt::AlignRight|Qt::AlignBottom); //设置右对齐
    //预设为系统当前时间(version_1.2)
    StartTimeLineEdit = new QDateTimeEdit(QDate::currentDate(),this);
    //设置可选择的范围+0~+365(version_1.2)
    StartTimeLineEdit->setMinimumDate(QDate::currentDate());
    StartTimeLineEdit->setMaximumDate(QDate::currentDate().addDays(30));
    //设置可弹出日历插件(version_1.2)
    StartTimeLineEdit->setCalendarPopup(true);
    //设置显示格式(version_1.2)
    StartTimeLineEdit->setDisplayFormat("yyyy-MM-dd");

    //FinalTime和FinalTimeLineEdit初始化(version_1.2)
    FinalTime = new QLabel(tr("结束日期："),this);
    FinalTime->setAlignment(Qt::AlignRight); //设置右对齐
    //预设为系统当前时间+1(version_1.2)
    FinalTimeLineEdit = new QDateTimeEdit(QDate::currentDate().addDays(1),this);
    //设置可选择的范围+1~+366(version_1.2)
    FinalTimeLineEdit->setMinimumDate(QDate::currentDate().addDays(1));
    FinalTimeLineEdit->setMaximumDate(QDate::currentDate().addDays(31));
    //设置可弹出日历插件(version_1.2)
    FinalTimeLineEdit->setCalendarPopup(true);
    //设置显示格式(version_1.2)
    FinalTimeLineEdit->setDisplayFormat("yyyy-MM-dd");

    //area和AreaComboBox初始化
    area = new QLabel(tr("省份："),this);
    area->setAlignment(Qt::AlignRight); //设置右对齐
    AreaComboBox = new QComboBox(this);
    //加入所有省份
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

    //SearchButton初始化
    SearchButton = new QPushButton(tr("搜寻"),this);
    SearchButton->setDefault(true);
    SearchButton->setEnabled(false);
    //ResetButton初始化(version_1.2)
    ResetButton = new QPushButton(tr("重设"), this);
    ResetButton->setDefault(true);

    //连接信号槽
    connect(AreaComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(enableSearch(int)));
    connect(SearchButton,SIGNAL(clicked()),this,SLOT(SearchHotal()));
    connect(ResetButton,SIGNAL(clicked()),this,SLOT(ResetSearch()));
    connect(Login_and_Logout,SIGNAL(clicked()),this,SLOT(ChangeLog()));

    //表单、网格和水平布局
    QFormLayout *formlayout1 = new QFormLayout;
    formlayout1->addRow(StartTime, StartTimeLineEdit);
    //设置成上方Label下方方框
    formlayout1->setRowWrapPolicy(QFormLayout::WrapAllRows);
    QFormLayout *formlayout2 = new QFormLayout;
    formlayout2->addRow(FinalTime, FinalTimeLineEdit);
    formlayout2->setRowWrapPolicy(QFormLayout::WrapAllRows);
    QFormLayout *formlayout3 = new QFormLayout;
    formlayout3->addRow(area, AreaComboBox);
    formlayout3->setRowWrapPolicy(QFormLayout::WrapAllRows);

    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->addWidget(Logo,0,0,9,16);
    gridlayout->addWidget(info,9,0,1,1);
    gridlayout->addLayout(formlayout1,8,1,2,1);
    gridlayout->addLayout(formlayout2,8,2,2,1);
    gridlayout->addLayout(formlayout3,8,3,2,1);
    gridlayout->addWidget(SearchButton,9,4,1,1);
    //增加ResetButton的布局(version_1.2)
    gridlayout->addWidget(ResetButton,9,5,1,1);

    QHBoxLayout *hboxlayout = new QHBoxLayout;
    hboxlayout->addLayout(gridlayout);
    hboxlayout->addStretch();

    QGridLayout *mainlayout = new QGridLayout;
    mainlayout->addLayout(hboxlayout,0,0,9,23);
    mainlayout->addWidget(Welcome,4,23,1,1);
    mainlayout->addWidget(Login_and_Logout,4,24,1,1);


    //设定窗口的Layout
    setLayout(mainlayout);
    //设定窗口的背景色
    QPalette background(this->palette());
    background.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(background);
}

Search::~Search() //析构函数实现
{

}

/* 函数名称：void enableSearch(int index)
 * 函数类型：槽函数
 * 输入参数：int类
 * 函数功能：若传入参数不为0，则将SearchButton设为可点击
 */
void Search::enableSearch(int index)
{
    SearchButton->setEnabled(index != 0);
}

/* 函数名称：SearchHotal()
 * 函数类型：槽函数
 * 函数功能：日期选择无误，发送searchHotal(StartTimeLineEdit->text(), FinalTimeLineEdit->text(), AreaComboBox->currentText())信号
 * (version_1.2)
 */
void Search::SearchHotal()
{
    if (StartTimeLineEdit->date() >= FinalTimeLineEdit->date())
    {
        QMessageBox::warning(NULL,tr("警告"),tr("错误日期区间，\n请重新填写！"),QMessageBox::Ok);
    }
    else
    {
        emit searchHotal(StartTimeLineEdit->text(), FinalTimeLineEdit->text(), AreaComboBox->currentText());
    }
}

/* 函数名称：ResetSearch()
 * 函数类型：槽函数
 * 函数功能：重设所有选项
 * (version_1.2)
 */
void Search::ResetSearch()
{
    StartTimeLineEdit->setDate(QDate::currentDate());
    FinalTimeLineEdit->setDate(QDate::currentDate().addDays(1));
    AreaComboBox->setCurrentIndex(0);
}

void Search::ChangeLog()
{
    if (getStatus() == "登入")
    {
        emit hideMainWindow();
        emit showLogin();
    }
    else
    {
        if (QMessageBox::question(NULL,tr("登出？"),tr("确定要登出吗？\n登出前请先确认所有变更已经保存！"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
        {
            if (QMessageBox::information(NULL,tr("登出"),tr("成功登出！"),QMessageBox::Ok) == QMessageBox::Ok)
            {
                emit hideMainWindow();
                emit ShowWelcome();
            }
        }
    }
}
