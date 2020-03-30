#include "createhotal.h"
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateTime>
#include <QGridLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include <QRegExp>
#include <QValidator>

CreateHotal::CreateHotal(Hotal *hotalhead, Message *messagehead, HotalUser *Mainaccount, QWidget *parent)
    :Hotalhead(hotalhead),Messagehead(messagehead),MainAccount(Mainaccount),successful(false),QDialog(parent)
{
    QRegExp regx("^[0-9]+$");
    info = new QLabel(tr("新增酒店"));
    info->setAlignment(Qt::AlignCenter);

    HotalName1 = new QLabel("酒店名称：");
    HotalName1->setAlignment(Qt::AlignLeft);
    HotalName2 = new QLineEdit;

    Area1 = new QLabel(tr("所在地："));
    Area1->setAlignment(Qt::AlignLeft);
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

    HotalTel1 = new QLabel(tr("酒店电话："));
    HotalTel1->setAlignment(Qt::AlignLeft);
    HotalTel2 = new QLineEdit;
    QValidator *validator1 = new QRegExpValidator(regx,HotalTel2);
    HotalTel2->setValidator(validator1);

    HotalInfo1 = new QLabel(tr("酒店信息："));
    HotalInfo1->setAlignment(Qt::AlignLeft);
    HotalInfo2 = new QTextEdit;

    CreateButton = new QPushButton(tr("提交"));
    CreateButton->setEnabled(false);
    CancelButton = new QPushButton(tr("取消"));

    connect(HotalName2,SIGNAL(textEdited(QString)),this,SLOT(EnableClick()));
    connect(HotalInfo2,SIGNAL(textChanged()),this,SLOT(EnableClick()));
    connect(AreaComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(EnableClick()));
    connect(CreateButton,SIGNAL(clicked()),this,SLOT(Create()));
    connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));

    QGridLayout *mainlayout = new QGridLayout;
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->addWidget(info,0,0,1,5);
    mainlayout->addWidget(HotalName1,1,0,1,2);
    mainlayout->addWidget(HotalName2,1,2,1,3);
    mainlayout->addWidget(Area1,2,0,1,2);
    mainlayout->addWidget(AreaComboBox,2,2,1,3);
    mainlayout->addWidget(HotalTel1,3,0,1,2);
    mainlayout->addWidget(HotalTel2,3,2,1,3);
    mainlayout->addWidget(HotalInfo1,4,0,1,2);
    mainlayout->addWidget(HotalInfo2,5,0,1,5);
    mainlayout->addWidget(CreateButton,6,0,1,2);
    mainlayout->addWidget(CancelButton,6,3,1,2);

    setLayout(mainlayout);
}

bool CreateHotal::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("取消？"),tr("现在退出酒店将不会完成创建，\n确定要退出吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CreateHotal::EnableClick()
{
    if ((AreaComboBox->currentIndex() != 0) && !(HotalName2->text().isEmpty()) && !(HotalInfo2->toPlainText().isEmpty()))
    {
        CreateButton->setEnabled(true);
    }
    else
    {
        CreateButton->setEnabled(false);;
    }
}

void CreateHotal::Create()
{
    if (QMessageBox::question(NULL,tr("新增酒店"),tr("是否送出申请？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        Hotal *newhotal = new Hotal(HotalName2->text(),HotalInfo2->toPlainText(),MainAccount->getaccount(),HotalTel2->text(),AreaComboBox->currentText());
        Hotal *ptr;
        for (ptr = Hotalhead;ptr->getHotalnext() != nullptr;ptr = ptr->getHotalnext())
        {}
        ptr->changeHotalnext(newhotal);
        Message *ptr1;
        for (ptr1 = Messagehead;ptr1->getnext() != nullptr;ptr1 = ptr1->getnext())
        {}
        Message *newmessage = new Message(MainAccount->getaccount(),"2017011507","我已向你提交我的酒店（酒店名为" + HotalName2->text() + "）新增申请！\n麻烦您尽快审核，谢谢！",nullptr,new QDateTime(QDateTime::currentDateTime()));
        ptr1->changenext(newmessage);
        successful = true;
        close();
    }
}

void CreateHotal::closeEvent(QCloseEvent *event)
{
    if (successful)
    {
        event->accept();
    }
    else if (ContinueToClose())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
