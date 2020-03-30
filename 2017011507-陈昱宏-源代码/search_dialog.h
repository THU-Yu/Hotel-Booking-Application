/*
 * 无特别标注版本的功能为version_1.2所添加
 *
 * 档案名：Search_Dialog.h
 * 内容：声明Search_Dialog类（该界面最后不会存在）
 * 版本：version_1.1
 * 作者：陈昱宏
 * 创建日期：2018/07/19
 *
 * 版本：version_1.2
 * 修改部分：该界面重置成搜索界面(嵌入在MainWindow类)
 * 修改者：陈昱宏（上版本作者：陈昱宏）
 * 修改日期：2018/07/20
 */
#ifndef SEARCH_DIALOG_H
#define SEARCH_DIALOG_H

#include <QDialog>

class QLabel;
class QPushButton;
class QDateTimeEdit;
class QComboBox;

class Search_Dialog:public QWidget //声明Search_Dialog类，单继承自QWidget类
{
    Q_OBJECT

public:
    Search_Dialog(QWidget *parent = 0); //构造函数
    ~Search_Dialog(); //析构函数
signals:
    void searchHotal(const QString &ST, const QString &FT, const QString &area='\0'); //发送搜索酒店的信号
public slots:
    void enableSearch(int index);
    void SearchHotal();
    void ResetSearch();
private:
    QLabel *info; //提示信息标签
    QLabel *StartTime; //起始时间标签
    QLabel *FinalTime; //终止时间标签
    QLabel *area; //地区标签
    QDateTimeEdit *StartTimeLineEdit; //起始时间输入
    QDateTimeEdit *FinalTimeLineEdit; //终止时间输入
    QPushButton *SearchButton; //搜寻按钮
    QPushButton *ResetButton; //重设按钮
    QComboBox *AreaComboBox; //地区组合框
};

#endif // SEARCH_DIALOG_H
