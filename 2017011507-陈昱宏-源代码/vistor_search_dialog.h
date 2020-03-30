/*
 * 无特别标注版本的功能为最初版所添加
 *
 * 档案名：Vistor_Search_Dialog.h
 * 内容：声明Vistor_Search_Dialog类（该界面最后不会存在）
 * 版本：version_1.1
 * 作者：陈昱宏
 * 创建日期：2018/07/19
 */
#ifndef VISTOR_SEARCH_DIALOG_H
#define VISTOR_SEARCH_DIALOG_H

#include <QDialog>

class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;

class Vistor_Search_Dialog:public QDialog
{
    Q_OBJECT

public:
    Vistor_Search_Dialog(QWidget *parent = 0);
    bool ContinueToClose();
    ~Vistor_Search_Dialog();
signals:
    void ShowLogin();
    void ShowRegister();
    void ShowWelcome();
protected:
    void closeEvent(QCloseEvent *event1);
private slots:
    void enableSearch(int index);
    void ShowLoginDialog();
    void ShowRegisterDialog();
    void ShowWelcomeWindow();
private:
    QLabel *info;
    QLabel *StartTime;
    QLabel *FinalTime;
    QLabel *area;
    QLineEdit *StartTimeLineEdit;
    QLineEdit *FinalTimeLineEdit;
    QPushButton *SearchButton;
    QPushButton *LoginButton;
    QPushButton *RegisterButton;
    QPushButton *CancelButton;
    QComboBox *AreaComboBox;
};


#endif // VISTOR_SEARCH_DIALOG_H
