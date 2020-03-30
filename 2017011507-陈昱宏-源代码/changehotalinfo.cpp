#include "changehotalinfo.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QCloseEvent>
#include <QGridLayout>
#include <QRegExp>
#include <QValidator>

ChangeHotalInfo::ChangeHotalInfo(Hotal *h, QWidget *parent)
    :hotal(h),change(false),QDialog(parent)
{
    QRegExp regx("^[0-9]+$");
    info = new QLabel(tr("修改酒店资讯"));
    info->setAlignment(Qt::AlignCenter);

    hotalname1 = new QLabel(tr("酒店名："));
    hotalname1->setAlignment(Qt::AlignLeft);
    hotalname2 = new QLineEdit;
    hotalname2->setText(hotal->getHotalName());
    if (hotal->getSuccessful())
    {
        hotalname2->setReadOnly(true);
    }

    Area1 = new QLabel(tr("所在地："));
    Area1->setAlignment(Qt::AlignLeft);
    AreaComboBox = new QComboBox;
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
    AreaComboBox->setCurrentText(h->getArea());
    if (h->getSuccessful())
    {
        AreaComboBox->setEnabled(false);
    }

    HotalTel1 = new QLabel(tr("酒店电话："));
    HotalTel1->setAlignment(Qt::AlignLeft);
    HotalTel2 = new QLineEdit;
    QValidator *validator1 = new QRegExpValidator(regx,HotalTel2);
    HotalTel2->setText(hotal->getHotalTel());
    HotalTel2->setValidator(validator1);

    hotalinfo1 = new QLabel(tr("酒店信息："));
    hotalinfo1->setAlignment(Qt::AlignLeft);
    hotalinfo2 = new QTextEdit;
    hotalinfo2->setText(hotal->getHotalInfo());

    ChangeButton = new QPushButton(tr("更改"));
    CancelButton = new QPushButton(tr("取消"));

    connect(ChangeButton,SIGNAL(clicked()),this,SLOT(Change()));
    connect(CancelButton,SIGNAL(clicked()),this,SLOT(close()));

    QGridLayout *mainlayout = new QGridLayout;
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->addWidget(info,0,0,1,5);
    mainlayout->addWidget(hotalname1,1,0,1,2);
    mainlayout->addWidget(hotalname2,1,2,1,3);
    mainlayout->addWidget(Area1,2,0,1,2);
    mainlayout->addWidget(AreaComboBox,2,2,1,3);
    mainlayout->addWidget(HotalTel1,3,0,1,2);
    mainlayout->addWidget(HotalTel2,3,2,1,3);
    mainlayout->addWidget(hotalinfo1,4,0,1,2);
    mainlayout->addWidget(hotalinfo2,5,0,1,5);
    mainlayout->addWidget(ChangeButton,6,0,1,2);
    mainlayout->addWidget(CancelButton,6,3,1,2);

    setLayout(mainlayout);

}

bool ChangeHotalInfo::ContinueToClose()
{
    if (QMessageBox::question(NULL,tr("取消修改"),tr("确定要取消修改吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ChangeHotalInfo::Change()
{
    hotal->changeHotalName(hotalname2->text());
    hotal->changeArea(AreaComboBox->currentText());
    hotal->changeHotalTel(HotalTel2->text());
    hotal->changeHotalInfo(hotalinfo2->toPlainText());
    change = true;
    close();
}

void ChangeHotalInfo::closeEvent(QCloseEvent *event)
{
    if (change)
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
