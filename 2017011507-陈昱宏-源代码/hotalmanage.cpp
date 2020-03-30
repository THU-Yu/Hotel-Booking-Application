#include "HotalManage.h"
#include "createorder.h"
#include "changehotalinfo.h"
#include "createhotal.h"
#include "createroom.h"
#include "changeroom.h"
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QComboBox>
#include <QDebug>

void HotalManage::changeHotalManage(NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainaccount3, QDate *start, QDate *final, QString area)
{
    MainAccount1 = Mainaccount1;
    MainAccount2 = Mainaccount2;
    MainAccount3 = Mainaccount3;

    Start = start;
    Final = final;
    Area = area;

    row = 0;
    int index = 0;
    bool avail = true;
    QString pinjia;
    if (MainAccount1)
    {
        if ((start == nullptr) && (final == nullptr) && (area == '\0'))
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    row += 1;
                }
            }
        }
        else
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    Room *_ptr1;
                    for (Room *_ptr = ptr->getRoomhead();_ptr != 0;_ptr = _ptr->getnext())
                    {
                        if ((*(_ptr->getDate()) >= *start) && (*(_ptr->getDate()) < *final) && (_ptr->getRoomNum() == 0))
                        {
                            avail = false;
                        }
                        if (_ptr != ptr->getRoomhead())
                        {
                            if (_ptr1->getType() != _ptr->getType())
                            {
                                if (avail)
                                {
                                    break;
                                }
                                else
                                {
                                    avail = true;
                                }
                            }
                        }
                        _ptr1 = _ptr;
                    }
                    if (avail && (ptr->getArea() == area))
                    {
                        row += 1;
                    }
                    avail = true;
                }
            }
        }
    }
    else if (MainAccount2)
    {
        for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
        {
            if (ptr->getHotalManagerAccount() == MainAccount2->getaccount())
            {
                row += 1;
            }
        }
    }
    else if (MainAccount3)
    {
        for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
        {
            row += 1;
        }
    }
    else
    {
        if ((start == nullptr) && (final == nullptr) && (area == '\0'))
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    row += 1;
                }
            }
        }
        else
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    Room *_ptr1;
                    for (Room *_ptr = ptr->getRoomhead();_ptr != 0;_ptr = _ptr->getnext())
                    {
                        if ((*(_ptr->getDate()) >= *start) && (*(_ptr->getDate()) < *final) && (_ptr->getRoomNum() == 0))
                        {
                            avail = false;
                        }
                        if (_ptr != ptr->getRoomhead())
                        {
                            if (_ptr1->getType() != _ptr->getType())
                            {
                                if (avail)
                                {
                                    break;
                                }
                                else
                                {
                                    avail = true;
                                }
                            }
                        }
                        _ptr1 = _ptr;
                    }
                    if (avail && (ptr->getArea() == area))
                    {
                        row += 1;
                    }
                    avail = true;
                }
            }
        }
    }

    QStringList header;
    if (MainAccount1)
    {
        MainTable = new QTableWidget(row,9,this);
        header << "酒店名" << "酒店经理账户" << "所在地" << "酒店信息" << "最便宜价格(取整)" << "评价" << " " << " " << " ";
        MainTable->setColumnWidth(4,200);
        if ((start == nullptr) && (final == nullptr) && (area == '\0'))
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    QTableWidgetItem *item = new QTableWidgetItem(pinjia.setNum(ptr->getminMoney(),'f',2));
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
                    MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
                    MainTable->setItem(index,4,item);
                    item->setData(Qt::DisplayRole,float(ptr->getminMoney()));
                    if (ptr->getPinJiaNum() == 0)
                    {
                        MainTable->setItem(index,5,new QTableWidgetItem("还未有用户评价"));
                    }
                    else
                    {
                        MainTable->setItem(index,5,new QTableWidgetItem(pinjia.setNum(ptr->getPinJia(),'f',2)));
                    }
                    MainTable->setItem(index,6,new QTableWidgetItem("详情"));
                    MainTable->setItem(index,7,new QTableWidgetItem("订购"));
                    MainTable->setItem(index,8,new QTableWidgetItem("咨询"));
                    index ++;
                }
            }
        }
        else
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    Room *_ptr1;
                    for (Room *_ptr = ptr->getRoomhead();_ptr != 0;_ptr = _ptr->getnext())
                    {
                        if ((*(_ptr->getDate()) >= *start) && (*(_ptr->getDate()) < *final) && (_ptr->getRoomNum() == 0))
                        {
                            avail = false;
                        }
                        if (_ptr != ptr->getRoomhead())
                        {
                            if (_ptr1->getType() != _ptr->getType())
                            {
                                if (avail)
                                {
                                    break;
                                }
                                else
                                {
                                    avail = true;
                                }
                            }
                        }
                        _ptr1 = _ptr;
                    }
                    if (avail && (ptr->getArea() == area))
                    {
                        QTableWidgetItem *item = new QTableWidgetItem(pinjia.setNum(ptr->getminMoney(),'f',2));
                        MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
                        MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
                        MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
                        MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
                        MainTable->setItem(index,4,item);
                        item->setData(Qt::DisplayRole,ptr->getminMoney());
                        if (ptr->getPinJiaNum() == 0)
                        {
                            MainTable->setItem(index,5,new QTableWidgetItem("还未有用户评价"));
                        }
                        else
                        {
                            MainTable->setItem(index,5,new QTableWidgetItem(pinjia.setNum(ptr->getPinJia(),'f',2)));
                        }
                        MainTable->setItem(index,6,new QTableWidgetItem("详情"));
                        MainTable->setItem(index,7,new QTableWidgetItem("订购"));
                        MainTable->setItem(index,8,new QTableWidgetItem("咨询"));
                        index ++;
                    }
                    avail = true;
                }
            }
        }
    }
    else if (MainAccount2)
    {
        MainTable = new QTableWidget(row,9,this);
        header << "酒店名" << "酒店经理账户" << "所在地" << "酒店信息" << "评价" << " " << " " << " " << " ";
        for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
        {
            if (ptr->getHotalManagerAccount() == MainAccount2->getaccount())
            {
                MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
                MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
                MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
                MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
                if (ptr->getPinJiaNum() == 0)
                {
                    MainTable->setItem(index,4,new QTableWidgetItem("还未有用户评价"));
                }
                else
                {
                    MainTable->setItem(index,4,new QTableWidgetItem(pinjia.setNum(ptr->getPinJia(),'f',2)));
                }
                MainTable->setItem(index,5,new QTableWidgetItem("详情"));
                MainTable->setItem(index,6,new QTableWidgetItem("修改"));
                if ((!ptr->getSuccessful()) && (!ptr->getNew()))
                {
                    MainTable->setItem(index,7,new QTableWidgetItem("再次提交审核"));
                }
                else if (ptr->getSuccessful())
                {
                    MainTable->setItem(index,7,new QTableWidgetItem("新增房型"));
                }
                if (ptr->getSuccessful())
                {
                    MainTable->setItem(index,8,new QTableWidgetItem("修改房间资讯"));
                }
                index ++;
            }
        }
    }
    else if (MainAccount3)
    {
        MainTable = new QTableWidget(row,6,this);
        header << "酒店名" << "酒店经理账户" << "所在地" << "酒店信息" << "评价" << " ";
        for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
        {
            MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
            MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
            MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
            MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
            if (ptr->getPinJiaNum() == 0)
            {
                MainTable->setItem(index,4,new QTableWidgetItem("还未有用户评价"));
            }
            else
            {
                MainTable->setItem(index,4,new QTableWidgetItem(pinjia.setNum(ptr->getPinJia(),'f',2)));
            }
            MainTable->setItem(index,5,new QTableWidgetItem("详情"));
            index ++;
        }
    }
    else
    {
        MainTable = new QTableWidget(row,7,this);
        header << "酒店名" << "酒店经理账户" << "所在地" << "酒店信息" << "最便宜价格(取整)" << "评价" << " " ;
        MainTable->setColumnWidth(4,200);
        if ((start == nullptr) && (final == nullptr) && (area == '\0'))
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    QTableWidgetItem *item = new QTableWidgetItem(pinjia.setNum(ptr->getminMoney(),'f',2));
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
                    MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
                    MainTable->setItem(index,4,item);
                    item->setData(Qt::DisplayRole,ptr->getminMoney());
                    if (ptr->getPinJiaNum() == 0)
                    {
                        MainTable->setItem(index,5,new QTableWidgetItem("还未有用户评价"));
                    }
                    else
                    {
                        MainTable->setItem(index,5,new QTableWidgetItem(pinjia.setNum(ptr->getPinJia(),'f',2)));
                    }
                    MainTable->setItem(index,6,new QTableWidgetItem("详情"));
                    index ++;
                }
            }
        }
        else
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    Room *_ptr1;
                    for (Room *_ptr = ptr->getRoomhead();_ptr->getnext() != 0;_ptr = _ptr->getnext())
                    {
                        if ((*(_ptr->getDate()) >= *start) && (*(_ptr->getDate()) < *final) && (_ptr->getRoomNum() == 0))
                        {
                            avail = false;
                        }
                        if (_ptr != ptr->getRoomhead())
                        {
                            if (_ptr->getType() != _ptr->getnext()->getType())
                            {
                                if (avail)
                                {
                                    break;
                                }
                                else
                                {
                                    avail = true;
                                }
                            }
                        }
                        _ptr1 = _ptr;
                    }
                    if (avail && (ptr->getArea() == area))
                    {
                        QTableWidgetItem *item = new QTableWidgetItem(pinjia.setNum(ptr->getminMoney(),'f',2));
                        MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
                        MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
                        MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
                        MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
                        MainTable->setItem(index,4,item);
                        item->setData(Qt::DisplayRole,ptr->getminMoney());
                        if (ptr->getPinJiaNum() == 0)
                        {
                            MainTable->setItem(index,5,new QTableWidgetItem("还未有用户评价"));
                        }
                        else
                        {
                            MainTable->setItem(index,5,new QTableWidgetItem(pinjia.setNum(ptr->getPinJia(),'f',2)));
                        }
                        MainTable->setItem(index,6,new QTableWidgetItem("详情"));
                        index ++;
                    }
                    avail = true;
                }
            }
        }
    }

    CreatButton = new QPushButton(tr("新增酒店"));
    BackButton = new QPushButton(tr("返回"));

    likebox = new QComboBox;
    likebox->addItem("按最低价格排序");
    likebox->addItem("按评价高低排序");

    connect(CreatButton,SIGNAL(clicked()),this,SLOT(createhotal()));
    connect(MainTable,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(ButtonClicked(QTableWidgetItem*)));
    connect(BackButton,SIGNAL(clicked()),this,SLOT(Back()));
    connect(likebox,SIGNAL(currentIndexChanged(int)),this,SLOT(ChangeLike(int)));

    MainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MainTable->setColumnWidth(1,150);
    MainTable->setHorizontalHeaderLabels(header);
    MainTable->setColumnWidth(7,200);
    MainTable->setColumnWidth(8,200);

    gridlayout = new QGridLayout;
    gridlayout->setAlignment(Qt::AlignCenter);
    if (MainAccount1 && ((start == nullptr) && (final == nullptr) && (area == '\0')))
    {
        MainTable->sortItems(4);
        gridlayout->addWidget(likebox,0,0,1,20);
        gridlayout->addWidget(MainTable,1,0,1,110);
        gridlayout->addWidget(CreatButton,2,55,1,1);
        gridlayout->addWidget(BackButton,3,55,1,1);
        BackButton->setVisible(false);
    }
    else if (((start == nullptr) && (final == nullptr) && (area == '\0')) && ((MainAccount2 == nullptr) && (MainAccount3 == nullptr)))
    {
        MainTable->sortItems(4);
        gridlayout->addWidget(likebox,0,0,1,20);
        gridlayout->addWidget(MainTable,1,0,1,110);
        gridlayout->addWidget(CreatButton,2,55,1,1);
        gridlayout->addWidget(BackButton,3,55,1,1);
        BackButton->setVisible(false);
    }
    else if (((start != nullptr) || (final != nullptr) || (area != '\0')) && ((MainAccount2 == nullptr) && (MainAccount3 == nullptr)))
    {
        MainTable->sortItems(4);
        gridlayout->addWidget(likebox,0,0,1,20);
        gridlayout->addWidget(MainTable,1,0,1,110);
        gridlayout->addWidget(CreatButton,2,55,1,1);
        gridlayout->addWidget(BackButton,3,55,1,1);
        BackButton->setVisible(true);
    }
    else
    {
        MainTable->sortItems(4);
        gridlayout->addWidget(likebox,0,0,1,20);
        gridlayout->addWidget(MainTable,1,0,1,110);
        gridlayout->addWidget(CreatButton,2,55,1,1);
        gridlayout->addWidget(BackButton,3,55,1,1);
        BackButton->setVisible(true);
    }

    if (MainAccount2 && MainTable->rowCount() == 0)
    {
        CreatButton->setVisible(true);
    }
    else
    {
        CreatButton->setVisible(false);
    }

    hboxlayout = new QHBoxLayout;
    hboxlayout->addLayout(gridlayout);

    mainlayout = new QVBoxLayout;
    mainlayout->addLayout(hboxlayout);

    setLayout(mainlayout);
}

void HotalManage::changeMainTable(NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainaccount3,QDate *start, QDate *final, QString area)
{
    MainAccount1 = Mainaccount1;
    MainAccount2 = Mainaccount2;
    MainAccount3 = Mainaccount3;

    Start = start;
    Final = final;
    Area = area;

    row = 0;
    int index = 0;
    bool avail = true;
    QString pinjia;
    MainTable->clear();
    if (MainAccount1)
    {
        if ((start == nullptr) && (final == nullptr) && (area == '\0'))
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    row += 1;
                }
            }
        }
        else
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    Room *_ptr1;
                    for (Room *_ptr = ptr->getRoomhead();_ptr != 0;_ptr = _ptr->getnext())
                    {
                        if ((*(_ptr->getDate()) >= *start) && (*(_ptr->getDate()) < *final) && (_ptr->getRoomNum() == 0))
                        {
                            avail = false;
                        }
                        if (_ptr != ptr->getRoomhead())
                        {
                            if (_ptr1->getType() != _ptr->getType())
                            {
                                if (avail)
                                {
                                    break;
                                }
                                else
                                {
                                    avail = true;
                                }
                            }
                        }
                        _ptr1 = _ptr;
                    }
                    if (avail && (ptr->getArea() == area))
                    {
                        row += 1;
                    }
                    avail = true;
                }
            }
        }
    }
    else if (MainAccount2)
    {
        for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
        {
            if (ptr->getHotalManagerAccount() == MainAccount2->getaccount())
            {
                row += 1;
            }
        }
    }
    else if (MainAccount3)
    {
        for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
        {
            row += 1;
        }
    }
    else
    {
        if ((start == nullptr) && (final == nullptr) && (area == '\0'))
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    row += 1;
                }
            }
        }
        else
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    Room *_ptr1;
                    for (Room *_ptr = ptr->getRoomhead();_ptr != 0;_ptr = _ptr->getnext())
                    {
                        if ((*(_ptr->getDate()) >= *start) && (*(_ptr->getDate()) < *final) && (_ptr->getRoomNum() == 0))
                        {
                            avail = false;
                        }
                        if (_ptr != ptr->getRoomhead())
                        {
                            if (_ptr1->getType() != _ptr->getType())
                            {
                                if (avail)
                                {
                                    break;
                                }
                                else
                                {
                                    avail = true;
                                }
                            }
                        }
                        _ptr1 = _ptr;
                    }
                    if (avail && (ptr->getArea() == area))
                    {
                        row += 1;
                    }
                    avail = true;
                }
            }
        }
    }
    MainTable->setRowCount(row);
    QStringList header;
    if (Mainaccount1)
    {
        MainTable->setColumnCount(9);
        header << "酒店名" << "酒店经理账户" << "所在地" << "酒店信息" << "最便宜价格(取整)" << "评价" << " " << " " << " ";
        MainTable->setColumnWidth(4,200);
        if ((start == nullptr) && (final == nullptr) && (area == '\0'))
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    QTableWidgetItem *item = new QTableWidgetItem(pinjia.setNum(ptr->getminMoney(),'f',2));
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
                    MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
                    MainTable->setItem(index,4,item);
                    item->setData(Qt::DisplayRole,ptr->getminMoney());
                    if (ptr->getPinJiaNum() == 0)
                    {
                        MainTable->setItem(index,5,new QTableWidgetItem("还未有用户评价"));
                    }
                    else
                    {
                        MainTable->setItem(index,5,new QTableWidgetItem(pinjia.setNum(ptr->getPinJia(),'f',2)));
                    }
                    MainTable->setItem(index,6,new QTableWidgetItem("详情"));
                    MainTable->setItem(index,7,new QTableWidgetItem("订购"));
                    MainTable->setItem(index,8,new QTableWidgetItem("咨询"));
                    index ++;
                }
            }
        }
        else
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    Room *_ptr1;
                    for (Room *_ptr = ptr->getRoomhead();_ptr != 0;_ptr = _ptr->getnext())
                    {
                        if ((*(_ptr->getDate()) >= *start) && (*(_ptr->getDate()) < *final) && (_ptr->getRoomNum() == 0))
                        {
                            avail = false;
                        }
                        if (_ptr != ptr->getRoomhead())
                        {
                            if (_ptr1->getType() != _ptr->getType())
                            {
                                if (avail)
                                {
                                    break;
                                }
                                else
                                {
                                    avail = true;
                                }
                            }
                        }
                        _ptr1 = _ptr;
                    }
                    if (avail && (ptr->getArea() == area))
                    {
                        QTableWidgetItem *item = new QTableWidgetItem(pinjia.setNum(ptr->getminMoney(),'f',2));
                        MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
                        MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
                        MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
                        MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
                        MainTable->setItem(index,4,item);
                        item->setData(Qt::DisplayRole,ptr->getminMoney());
                        if (ptr->getPinJiaNum() == 0)
                        {
                            MainTable->setItem(index,5,new QTableWidgetItem("还未有用户评价"));
                        }
                        else
                        {
                            MainTable->setItem(index,5,new QTableWidgetItem(pinjia.setNum(ptr->getPinJia(),'f',2)));
                        }
                        MainTable->setItem(index,6,new QTableWidgetItem("详情"));
                        MainTable->setItem(index,7,new QTableWidgetItem("订购"));
                        MainTable->setItem(index,8,new QTableWidgetItem("咨询"));
                        index ++;
                    }
                    avail = true;
                }
            }
        }
    }
    else if (Mainaccount2)
    {
        MainTable->setColumnCount(9);
        header << "酒店名" << "酒店经理账户" << "所在地" << "酒店信息" << "评价" << " " << " " << " " << " ";
        for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
        {
            if (ptr->getHotalManagerAccount() == MainAccount2->getaccount())
            {
                MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
                MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
                MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
                MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
                if (ptr->getPinJiaNum() == 0)
                {
                    MainTable->setItem(index,4,new QTableWidgetItem("还未有用户评价"));
                }
                else
                {
                    MainTable->setItem(index,4,new QTableWidgetItem(pinjia.setNum(ptr->getPinJia(),'f',2)));
                }
                MainTable->setItem(index,5,new QTableWidgetItem("详情"));
                MainTable->setItem(index,6,new QTableWidgetItem("修改"));
                if ((!ptr->getSuccessful()) && (!ptr->getNew()))
                {
                    MainTable->setItem(index,7,new QTableWidgetItem("再次提交审核"));
                }
                else if (ptr->getSuccessful())
                {
                    MainTable->setItem(index,7,new QTableWidgetItem("新增房型"));
                }
                if (ptr->getSuccessful())
                {
                    MainTable->setItem(index,8,new QTableWidgetItem("修改房间资讯"));
                }
                index ++;
            }
        }
    }
    else if (Mainaccount3)
    {
        MainTable->setColumnCount(6);
        header << "酒店名" << "酒店经理账户" << "所在地" << "酒店信息" << "评价" << " ";
        for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
        {
            MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
            MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
            MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
            MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
            if (ptr->getPinJiaNum() == 0)
            {
                MainTable->setItem(index,4,new QTableWidgetItem("还未有用户评价"));
            }
            else
            {
                MainTable->setItem(index,4,new QTableWidgetItem(pinjia.setNum(ptr->getPinJia(),'f',2)));
            }
            MainTable->setItem(index,5,new QTableWidgetItem("详情"));
            index ++;
        }
    }
    else
    {
        MainTable->setColumnCount(7);
        header << "酒店名" << "酒店经理账户" << "所在地" << "酒店信息" << "最便宜价格(取整)" << "评价" << " " ;
        MainTable->setColumnWidth(4,200);
        if ((start == nullptr) && (final == nullptr) && (area == '\0'))
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    QTableWidgetItem *item = new QTableWidgetItem(pinjia.setNum(ptr->getminMoney(),'f',2));
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
                    MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
                    MainTable->setItem(index,4,item);
                    item->setData(Qt::DisplayRole,ptr->getminMoney());
                    if (ptr->getPinJiaNum() == 0)
                    {
                        MainTable->setItem(index,5,new QTableWidgetItem("还未有用户评价"));
                    }
                    else
                    {
                        MainTable->setItem(index,5,new QTableWidgetItem(pinjia.setNum(ptr->getPinJia(),'f',2)));
                    }
                    MainTable->setItem(index,6,new QTableWidgetItem("详情"));
                    index ++;
                }
            }
        }
        else
        {
            for (Hotal *ptr = Hotalhead;ptr != 0;ptr = ptr->getHotalnext())
            {
                if (ptr->getSuccessful() && ptr->getRoomhead() != nullptr)
                {
                    Room *_ptr1;
                    for (Room *_ptr = ptr->getRoomhead();_ptr != 0;_ptr = _ptr->getnext())
                    {
                        if ((*(_ptr->getDate()) >= *start) && (*(_ptr->getDate()) < *final) && (_ptr->getRoomNum() == 0))
                        {
                            avail = false;
                        }
                        if (_ptr != ptr->getRoomhead())
                        {
                            if (_ptr1->getType() != _ptr->getType())
                            {
                                if (avail)
                                {
                                    break;
                                }
                                else
                                {
                                    avail = true;
                                }
                            }
                        }
                        _ptr1 = _ptr;
                    }
                    if (avail && (ptr->getArea() == area))
                    {
                        QTableWidgetItem *item = new QTableWidgetItem(pinjia.setNum(ptr->getminMoney(),'f',2));
                        MainTable->setItem(index,0,new QTableWidgetItem(ptr->getHotalName()));
                        MainTable->setItem(index,1,new QTableWidgetItem(ptr->getHotalManagerAccount()));
                        MainTable->setItem(index,2,new QTableWidgetItem(ptr->getArea()));
                        MainTable->setItem(index,3,new QTableWidgetItem(ptr->getHotalInfo()));
                        MainTable->setItem(index,4,item);
                        item->setData(Qt::DisplayRole,ptr->getminMoney());
                        if (ptr->getPinJiaNum() == 0)
                        {
                            MainTable->setItem(index,5,new QTableWidgetItem("还未有用户评价"));
                        }
                        else
                        {
                            MainTable->setItem(index,5,new QTableWidgetItem(pinjia.setNum(ptr->getPinJia(),'f',2)));
                        }
                        MainTable->setItem(index,6,new QTableWidgetItem("详情"));
                        index ++;
                    }
                    avail = true;
                }
            }
        }
    }

    if (MainAccount2 && MainTable->rowCount() == 0)
    {
        CreatButton->setVisible(true);
    }
    else
    {
        CreatButton->setVisible(false);
    }

    if (MainAccount2 || MainAccount3)
    {
        BackButton->setVisible(true);
    }
    MainTable->sortItems(4);
    MainTable->setColumnWidth(1,150);
    MainTable->setHorizontalHeaderLabels(header);
    MainTable->setColumnWidth(7,200);
    MainTable->setColumnWidth(8,200);
}

void HotalManage::ButtonClicked(QTableWidgetItem *item)
{
    int row;
    int col;
    row = item->row();
    col = item->column();
    if (item->text() == "详情")
    {
        Hotal *ptr;
        for (ptr = Hotalhead;ptr->getHotalName() != MainTable->item(row,0)->text();ptr = ptr->getHotalnext())
        {}
        hotaldetail = new HotalDetail(ptr,this);
        hotaldetail->show();
    }
    else if (item->text() == "再次提交审核")
    {
        Hotal *ptr;
        for (ptr = Hotalhead;ptr->getHotalName() != MainTable->item(row,0)->text();ptr = ptr->getHotalnext())
        {}
        ptr->changeNew(true);
        changeMainTable(MainAccount1,MainAccount2,MainAccount3);
    }
    else if (item->text() == "咨询")
    {
        SendMessageDialog *sent = new SendMessageDialog(Messagehead,MainTable->item(row,1)->text(),MainAccount1,MainAccount2,MainAccount3);
        sent->exec();
    }
    else if (item->text() == "订购")
    {
        Hotal *ptr;
        for (ptr = Hotalhead;ptr->getHotalName() != MainTable->item(row,0)->text();ptr = ptr->getHotalnext())
        {}
        CreateOrder *order = new CreateOrder(Hotalhead,Roomhead,Messagehead,Orderhead,ptr,MainAccount1,this);
        order->exec();
    }
    else if (item->text() == "修改")
    {
        Hotal *ptr;
        for (ptr = Hotalhead;ptr->getHotalName() != MainTable->item(row,0)->text();ptr = ptr->getHotalnext())
        {}
        ChangeHotalInfo *change = new ChangeHotalInfo(ptr,this);
        change->exec();
        changeMainTable(MainAccount1,MainAccount2,MainAccount3);
    }
    else if (item->text() == "新增房型")
    {
        Hotal *ptr;
        for (ptr = Hotalhead;ptr->getHotalName() != MainTable->item(row,0)->text();ptr = ptr->getHotalnext())
        {}
        CreateRoom *newroom = new CreateRoom(ptr,Roomhead,this);
        newroom->exec();
        changeMainTable(MainAccount1,MainAccount2,MainAccount3);
    }
    else if (item->text() == "修改房间资讯")
    {
        Hotal *ptr;
        for (ptr = Hotalhead;ptr->getHotalName() != MainTable->item(row,0)->text();ptr = ptr->getHotalnext())
        {}
        ChangeRoom *newroom = new ChangeRoom(ptr,Roomhead,this);
        newroom->exec();
    }
}

void HotalManage::Back()
{
    emit back();
}

void HotalManage::ChangeLike(int n)
{
    if (n == 0)
    {
        changeMainTable(MainAccount1,MainAccount2,MainAccount3,Start,Final,Area);
    }
    else if (n == 1)
    {
        MainTable->sortItems(5,Qt::DescendingOrder);
    }
}

void HotalManage::createhotal()
{
    CreateHotal *newhotal = new CreateHotal(Hotalhead,Messagehead,MainAccount2);
    newhotal->exec();
    changeMainTable(MainAccount1,MainAccount2,MainAccount3);
}
