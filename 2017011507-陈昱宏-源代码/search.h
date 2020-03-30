/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：Search.h
 * 内容：声明Search类（搜寻功能的窗口，用于嵌入主画面）
 * 版本：version_1.1
 * 作者：陈昱宏
 * 创建日期：2018/07/19
 *
 * 版本：version_1.2
 * 修改部分：修改输入的类型(QDateTimeEdit)，显示日历、新增重设按钮、重设槽函数、搜索信号(未使用)、搜索槽函数(未使用)
 * 修改者：陈昱宏（上版本作者：陈昱宏）
 * 修改日期：2018/07/20
 */
#ifndef SEARCH_H
#define SEARCH_H

#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include "account.h"

class QDateTimeEdit;
class QComboBox;

class Search:public QWidget //声明Search类，单继承自QWidget类
{
    Q_OBJECT

public:
    Search(QWidget *parent = 0); //构造函数
    QString getStatus(){return Login_and_Logout->text();}
    void setWelcome(QString s){Welcome->setText(s);}
    void setLogin_and_Logout(QString s){Login_and_Logout->setText(s);}
    ~Search(); //析构函数
signals:
    void searchHotal(const QString &ST, const QString &FT, const QString &area='\0'); //发送搜索酒店的信号(version_1.2)
    void showLogin();
    void hideMainWindow();
    void ShowWelcome();
public slots:
    void enableSearch(int index); //接收AreaComboBox的currentIndexChanged(int)信号
    void SearchHotal(); //接收SearchButton的clicked()信号(version_1.2)
    void ResetSearch(); //接收ResetButton的clicked()信号(version_1.2)
    void ChangeLog();
private:
    QLabel *Logo; //Logo图标签
    QLabel *info; //提示信息标签
    QLabel *Welcome;
    QLabel *StartTime; //起始时间标签
    QLabel *FinalTime; //终止时间标签
    QLabel *area; //地区标签
    QDateTimeEdit *StartTimeLineEdit; //起始时间输入
    QDateTimeEdit *FinalTimeLineEdit; //终止时间输入
    QPushButton *SearchButton; //搜寻按钮
    QPushButton *ResetButton; //重设按钮
    QPushButton *Login_and_Logout;
    QComboBox *AreaComboBox; //地区组合框
};

#endif // SEARCH_H
