#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>

class QLabel;
class QPushButton;

class WelcomeDialog:public QDialog
{
    Q_OBJECT

public:
    WelcomeDialog(QWidget *parent = 0);
    ~WelcomeDialog();
signals:
    void clickYes();
    void showLoginDialog();
private slots:
    void Login();
    void Rigistr();
    void Quit();
private:
    QLabel *label;
    QPushButton *loginbutton;
    QPushButton *registerbutton;
    QPushButton *quitbutton;
    QPushButton *vistorbutton;
};
#endif // WELCOMEDIALOG_H
