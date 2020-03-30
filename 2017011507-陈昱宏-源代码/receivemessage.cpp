#include "receivemessage.h"
#include "sendmessagedialog.h"
#include <QPushButton>
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>

void ReceiveMessage::changeReceiveMessage(NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainaccount3)
{
    MainAccount1 = Mainaccount1;
    MainAccount2 = Mainaccount2;
    MainAccount3 = Mainaccount3;

    int row = 0;
    int index = 0;

    if (MainAccount1)
    {
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getreceiveUser() == MainAccount1->getaccount())
            {
                row += 1;
            }
        }
    }
    else if (MainAccount2)
    {
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getreceiveUser() == MainAccount2->getaccount())
            {
                row += 1;
            }
        }
    }
    else
    {
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getreceiveUser() == MainAccount3->getaccount())
            {
                row += 1;
            }
        }
    }

    QStringList header;
    if (MainAccount1)
    {
        MainTable = new QTableWidget(row,6,this);
        header << "发送者" << "内容" << "时间" << " " << " " << " ";
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getNew())
            {
                if (ptr->getreceiveUser() == MainAccount1->getaccount())
                {
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getsendUser()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getmessage()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss")));
                    MainTable->setItem(index,3,new QTableWidgetItem("详情"));
                    MainTable->setItem(index,4,new QTableWidgetItem("回复"));
                    MainTable->setItem(index,5,new QTableWidgetItem("删除"));
                    index ++;
                }
            }
        }
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (!(ptr->getNew()))
            {
                if (ptr->getreceiveUser() == MainAccount1->getaccount())
                {
                    QTableWidgetItem *item1 = new QTableWidgetItem;
                    item1->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item2 = new QTableWidgetItem;
                    item2->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item3 = new QTableWidgetItem;
                    item3->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item4 = new QTableWidgetItem;
                    item4->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item5 = new QTableWidgetItem;
                    item5->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item6 = new QTableWidgetItem;
                    item6->setBackgroundColor(QColor(192,192,192));
                    item1->setText(ptr->getsendUser());
                    MainTable->setItem(index,0,item1);
                    item2->setText(ptr->getmessage());
                    MainTable->setItem(index,1,item2);
                    item3->setText(ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss"));
                    MainTable->setItem(index,2,item3);
                    item4->setText("详情");
                    MainTable->setItem(index,3,item4);
                    item5->setText("回复");
                    MainTable->setItem(index,4,item5);
                    item6->setText("删除");
                    MainTable->setItem(index,5,item6);
                    index ++;
                }
            }
        }
    }
    else if (MainAccount2)
    {
        MainTable = new QTableWidget(row,6,this);
        header << "发送者" << "内容" << "时间" << " " << " " << " ";
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getNew())
            {
                if (ptr->getreceiveUser() == MainAccount2->getaccount())
                {
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getsendUser()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getmessage()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss")));
                    MainTable->setItem(index,3,new QTableWidgetItem("详情"));
                    MainTable->setItem(index,4,new QTableWidgetItem("回复"));
                    MainTable->setItem(index,5,new QTableWidgetItem("删除"));
                    index ++;
                }
            }
        }
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (!(ptr->getNew()))
            {
                if (ptr->getreceiveUser() == MainAccount2->getaccount())
                {
                    QTableWidgetItem *item1 = new QTableWidgetItem;
                    item1->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item2 = new QTableWidgetItem;
                    item2->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item3 = new QTableWidgetItem;
                    item3->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item4 = new QTableWidgetItem;
                    item4->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item5 = new QTableWidgetItem;
                    item5->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item6 = new QTableWidgetItem;
                    item6->setBackgroundColor(QColor(192,192,192));
                    item1->setText(ptr->getsendUser());
                    MainTable->setItem(index,0,item1);
                    item2->setText(ptr->getmessage());
                    MainTable->setItem(index,1,item2);
                    item3->setText(ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss"));
                    MainTable->setItem(index,2,item3);
                    item4->setText("详情");
                    MainTable->setItem(index,3,item4);
                    item5->setText("回复");
                    MainTable->setItem(index,4,item5);
                    item6->setText("删除");
                    MainTable->setItem(index,5,item6);
                    index ++;
                }
            }
        }
    }
    else
    {
        MainTable = new QTableWidget(row,6,this);
        header << "发送者" << "内容" << "时间" << " " << " " << " ";
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getNew())
            {
                if (ptr->getreceiveUser() == MainAccount3->getaccount())
                {
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getsendUser()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getmessage()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss")));
                    MainTable->setItem(index,3,new QTableWidgetItem("详情"));
                    MainTable->setItem(index,4,new QTableWidgetItem("回复"));
                    MainTable->setItem(index,5,new QTableWidgetItem("删除"));
                    index ++;
                }
            }
        }
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (!(ptr->getNew()))
            {
                if (ptr->getreceiveUser() == MainAccount3->getaccount())
                {
                    QTableWidgetItem *item1 = new QTableWidgetItem;
                    item1->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item2 = new QTableWidgetItem;
                    item2->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item3 = new QTableWidgetItem;
                    item3->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item4 = new QTableWidgetItem;
                    item4->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item5 = new QTableWidgetItem;
                    item5->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item6 = new QTableWidgetItem;
                    item6->setBackgroundColor(QColor(192,192,192));
                    item1->setText(ptr->getsendUser());
                    MainTable->setItem(index,0,item1);
                    item2->setText(ptr->getmessage());
                    MainTable->setItem(index,1,item2);
                    item3->setText(ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss"));
                    MainTable->setItem(index,2,item3);
                    item4->setText("详情");
                    MainTable->setItem(index,3,item4);
                    item5->setText("回复");
                    MainTable->setItem(index,4,item5);
                    item6->setText("删除");
                    MainTable->setItem(index,5,item6);
                    index ++;
                }
            }
        }
    }

    BackButton = new QPushButton(tr("返回"));

    connect(MainTable,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(ButtonClicked(QTableWidgetItem*)));
    connect(BackButton,SIGNAL(clicked()),this,SLOT(Back()));

    MainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MainTable->setHorizontalHeaderLabels(header);

    gridlayout = new QGridLayout;
    gridlayout->setAlignment(Qt::AlignCenter);
    gridlayout->addWidget(MainTable,0,0,1,110);
    gridlayout->addWidget(BackButton,1,55,1,1);

    hboxlayout = new QHBoxLayout;
    hboxlayout->addLayout(gridlayout);

    mainlayout = new QVBoxLayout;
    mainlayout->addLayout(hboxlayout);

    setLayout(mainlayout);
}

void ReceiveMessage::changeMainTable(NormalUser *Mainaccount1, HotalUser *Mainaccount2, PlatformUser *Mainaccount3)
{
    MainAccount1 = Mainaccount1;
    MainAccount2 = Mainaccount2;
    MainAccount3 = Mainaccount3;

    int row = 0;
    int index = 0;
    MainTable->clearContents();

    if (MainAccount1)
    {
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getreceiveUser() == MainAccount1->getaccount())
            {
                row += 1;
            }
        }
    }
    else if (MainAccount2)
    {
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getreceiveUser() == MainAccount2->getaccount())
            {
                row += 1;
            }
        }
    }
    else
    {
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getreceiveUser() == MainAccount3->getaccount())
            {
                row += 1;
            }
        }
    }

    MainTable->setRowCount(row);

    if (MainAccount1)
    {
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getNew())
            {
                if (ptr->getreceiveUser() == MainAccount1->getaccount())
                {
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getsendUser()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getmessage()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss")));
                    MainTable->setItem(index,3,new QTableWidgetItem("详情"));
                    MainTable->setItem(index,4,new QTableWidgetItem("回复"));
                    MainTable->setItem(index,5,new QTableWidgetItem("删除"));
                    index ++;
                }
            }
        }
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (!(ptr->getNew()))
            {
                if (ptr->getreceiveUser() == MainAccount1->getaccount())
                {
                    QTableWidgetItem *item1 = new QTableWidgetItem;
                    item1->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item2 = new QTableWidgetItem;
                    item2->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item3 = new QTableWidgetItem;
                    item3->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item4 = new QTableWidgetItem;
                    item4->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item5 = new QTableWidgetItem;
                    item5->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item6 = new QTableWidgetItem;
                    item6->setBackgroundColor(QColor(192,192,192));
                    item1->setText(ptr->getsendUser());
                    MainTable->setItem(index,0,item1);
                    item2->setText(ptr->getmessage());
                    MainTable->setItem(index,1,item2);
                    item3->setText(ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss"));
                    MainTable->setItem(index,2,item3);
                    item4->setText("详情");
                    MainTable->setItem(index,3,item4);
                    item5->setText("回复");
                    MainTable->setItem(index,4,item5);
                    item6->setText("删除");
                    MainTable->setItem(index,5,item6);
                    index ++;
                }
            }
        }
    }
    else if (MainAccount2)
    {
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getNew())
            {
                if (ptr->getreceiveUser() == MainAccount2->getaccount())
                {
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getsendUser()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getmessage()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss")));
                    MainTable->setItem(index,3,new QTableWidgetItem("详情"));
                    MainTable->setItem(index,4,new QTableWidgetItem("回复"));
                    MainTable->setItem(index,5,new QTableWidgetItem("删除"));
                    index ++;
                }
            }
        }
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (!(ptr->getNew()))
            {
                if (ptr->getreceiveUser() == MainAccount2->getaccount())
                {
                    QTableWidgetItem *item1 = new QTableWidgetItem;
                    item1->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item2 = new QTableWidgetItem;
                    item2->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item3 = new QTableWidgetItem;
                    item3->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item4 = new QTableWidgetItem;
                    item4->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item5 = new QTableWidgetItem;
                    item5->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item6 = new QTableWidgetItem;
                    item6->setBackgroundColor(QColor(192,192,192));
                    item1->setText(ptr->getsendUser());
                    MainTable->setItem(index,0,item1);
                    item2->setText(ptr->getmessage());
                    MainTable->setItem(index,1,item2);
                    item3->setText(ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss"));
                    MainTable->setItem(index,2,item3);
                    item4->setText("详情");
                    MainTable->setItem(index,3,item4);
                    item5->setText("回复");
                    MainTable->setItem(index,4,item5);
                    item6->setText("删除");
                    MainTable->setItem(index,5,item6);
                    index ++;
                }
            }
        }
    }
    else
    {
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (ptr->getNew())
            {
                if (ptr->getreceiveUser() == MainAccount3->getaccount())
                {
                    MainTable->setItem(index,0,new QTableWidgetItem(ptr->getsendUser()));
                    MainTable->setItem(index,1,new QTableWidgetItem(ptr->getmessage()));
                    MainTable->setItem(index,2,new QTableWidgetItem(ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss")));
                    MainTable->setItem(index,3,new QTableWidgetItem("详情"));
                    MainTable->setItem(index,4,new QTableWidgetItem("回复"));
                    MainTable->setItem(index,5,new QTableWidgetItem("删除"));
                    index ++;
                }
            }
        }
        for (Message *ptr = Messagehead;ptr != 0;ptr = ptr->getnext())
        {
            if (!(ptr->getNew()))
            {
                if (ptr->getreceiveUser() == MainAccount3->getaccount())
                {
                    QTableWidgetItem *item1 = new QTableWidgetItem;
                    item1->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item2 = new QTableWidgetItem;
                    item2->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item3 = new QTableWidgetItem;
                    item3->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item4 = new QTableWidgetItem;
                    item4->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item5 = new QTableWidgetItem;
                    item5->setBackgroundColor(QColor(192,192,192));
                    QTableWidgetItem *item6 = new QTableWidgetItem;
                    item6->setBackgroundColor(QColor(192,192,192));
                    item1->setText(ptr->getsendUser());
                    MainTable->setItem(index,0,item1);
                    item2->setText(ptr->getmessage());
                    MainTable->setItem(index,1,item2);
                    item3->setText(ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss"));
                    MainTable->setItem(index,2,item3);
                    item4->setText("详情");
                    MainTable->setItem(index,3,item4);
                    item5->setText("回复");
                    MainTable->setItem(index,4,item5);
                    item6->setText("删除");
                    MainTable->setItem(index,5,item6);
                    index ++;
                }
            }
        }
    }
}

void ReceiveMessage::ButtonClicked(QTableWidgetItem *item)
{
    int row;
    int col;
    row = item->row();
    col = item->column();
    if (col == 3)
    {
        Message *ptr;
        for (ptr = Messagehead;(ptr->getsendUser() != MainTable->item(row,0)->text()) || (ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss") != MainTable->item(row,2)->text()) || (ptr->getmessage() != MainTable->item(row,1)->text());ptr = ptr->getnext())
        {}
        messagedetail = new MessageDetail(ptr);
        messagedetail->show();
        ptr->changeNew(false);
        changeMainTable(MainAccount1,MainAccount2,MainAccount3);
    }
    else if (col == 4)
    {
        SendMessageDialog *send = new SendMessageDialog(Messagehead,MainTable->item(row,0)->text(),MainAccount1,MainAccount2,MainAccount3);
        send->exec();
    }
    else if (col == 5)
    {
        if (QMessageBox::question(NULL,tr("删除消息"),tr("确定要删除吗？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
        {
            Message *ptr,*ptr1;
            for (ptr = Messagehead;(ptr->getsendUser() != MainTable->item(row,0)->text()) || (ptr->getdate()->toString("yyyy-MM-dd hh:mm:ss") != MainTable->item(row,2)->text()) || (ptr->getmessage() != MainTable->item(row,1)->text());ptr = ptr->getnext())
            {
                ptr1 = ptr;
            }
            if ((ptr == Messagehead) && (ptr->getnext() != nullptr))
            {
                ptr1 = ptr;
                ptr->changedate(ptr->getnext()->getdate());
                ptr->changemessage(ptr->getnext()->getmessage());
                ptr->changesendUser(ptr->getnext()->getsendUser());
                ptr->changereceiveUser(ptr->getnext()->getreceiveUser());
                ptr->changeNew(ptr->getnext()->getNew());
                ptr = ptr->getnext();
            }
            ptr1->changenext(ptr->getnext());
            delete ptr;
            changeMainTable(MainAccount1,MainAccount2,MainAccount3);
        }
    }
}

void ReceiveMessage::Back()
{
    emit back();
}
