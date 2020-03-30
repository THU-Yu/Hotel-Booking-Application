/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：Search_Dialog.cpp
 * 内容：实现Search_Dialog类（该界面最后不会存在）
 * 版本：version_1.1
 * 作者：陈昱宏
 * 创建日期：2018/07/19
 */
#include "search_dialog.h"
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>
#include <QFormLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QDebug>

Search_Dialog::Search_Dialog(QWidget *parent/*=0*/)
    :QWidget(parent)
{
    //info初始化
    info = new QLabel(tr("请输入酒店条件："), this);
    info->setAlignment(Qt::AlignLeft);

    //StartTime和StartTimeLineEdit初始化
    StartTime = new QLabel(tr("起始时间："), this);
    StartTime->setAlignment(Qt::AlignLeft); //设置左对齐
    //预设为系统当前时间
    StartTimeLineEdit = new QDateTimeEdit(QDate::currentDate(), this);
    //设置可选择的范围+0~+365
    StartTimeLineEdit->setMinimumDate(QDate::currentDate());
    StartTimeLineEdit->setMaximumDate(QDate::currentDate().addDays(30));
    //设置可弹出日历插件
    StartTimeLineEdit->setCalendarPopup(true);
    //设置最大尺寸
    StartTimeLineEdit->setMaximumWidth(150);
    //设置显示格式
    StartTimeLineEdit->setDisplayFormat("yyyy-MM-dd");

    //FinalTime和FinalTimeLineEdit初始化
    FinalTime = new QLabel(tr("结束时间："), this);
    FinalTime->setAlignment(Qt::AlignLeft); //设置左对齐
    //预设为系统当前时间+1
    FinalTimeLineEdit = new QDateTimeEdit(QDate::currentDate().addDays(1), this);
    //设置可选择的范围+1~+366
    FinalTimeLineEdit->setMinimumDate(QDate::currentDate().addDays(1));
    FinalTimeLineEdit->setMaximumDate(QDate::currentDate().addDays(31));
    //设置可弹出日历插件
    FinalTimeLineEdit->setCalendarPopup(true);
    //设置最大尺寸
    FinalTimeLineEdit->setMaximumWidth(150);
    //设置显示格式
    FinalTimeLineEdit->setDisplayFormat("yyyy-MM-dd");

    //area和AreaComboBox初始化
    area = new QLabel(tr("省份："), this);
    area->setAlignment(Qt::AlignLeft); //设置左对齐
    AreaComboBox = new QComboBox(this);
    //设置最大尺寸
    AreaComboBox->setMaximumWidth(150);
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
    SearchButton = new QPushButton(tr("搜寻"), this);
    SearchButton->setMaximumWidth(70);
    SearchButton->setDefault(true);
    SearchButton->setEnabled(false);
    //ResetButton初始化
    ResetButton = new QPushButton(tr("重设"), this);
    ResetButton->setMaximumWidth(70);
    ResetButton->setDefault(true);

    //连接信号槽
    connect(AreaComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(enableSearch(int)));
    connect(SearchButton,SIGNAL(clicked()),this,SLOT(SearchHotal()));
    connect(ResetButton,SIGNAL(clicked()),this,SLOT(ResetSearch()));

    //表单、网格和垂直布局
    QFormLayout *formlayout = new QFormLayout;
    formlayout->addRow(StartTime, StartTimeLineEdit);
    formlayout->addRow(FinalTime, FinalTimeLineEdit);
    formlayout->addRow(area, AreaComboBox);
    //设置成上方Label下方方框
    formlayout->setRowWrapPolicy(QFormLayout::WrapAllRows);

    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->addLayout(formlayout,0,0,1,4);
    gridlayout->addWidget(SearchButton,1,0,1,1);
    gridlayout->addWidget(ResetButton,1,2,1,1);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->setAlignment(Qt::AlignLeft);
    mainlayout->addWidget(info);
    mainlayout->addStretch(1);
    mainlayout->addLayout(gridlayout);
    mainlayout->addStretch(10);

    //设定窗口的Layout
    setLayout(mainlayout);
}

Search_Dialog::~Search_Dialog() //析构函数实现
{

}


/* 函数名称：void enableSearch(int index)
 * 函数类型：槽函数
 * 输入参数：int类
 * 函数功能：若传入参数不为0，则将SearchButton设为可点击
 */
void Search_Dialog::enableSearch(int index)
{
    SearchButton->setEnabled(index != 0);
}


/* 函数名称：SearchHotal()
 * 函数类型：槽函数
 * 函数功能：日期选择无误，发送searchHotal(StartTimeLineEdit->text(), FinalTimeLineEdit->text(), AreaComboBox->currentText())信号
 */
void Search_Dialog::SearchHotal()
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
 */
void Search_Dialog::ResetSearch()
{
    StartTimeLineEdit->setDate(QDate::currentDate());
    FinalTimeLineEdit->setDate(QDate::currentDate().addDays(1));
    AreaComboBox->setCurrentIndex(0);
}
