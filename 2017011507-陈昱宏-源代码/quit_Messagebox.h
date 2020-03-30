#ifndef QUIT_MESSAGEBOX_H
#define QUIT_MESSAGEBOX_H

#include <QMessageBox>
#include <QWidget>

class QLabel;

class Quit_MessageBox:public QMessageBox
{
public:
    Quit_MessageBox(QWidget* parent = 0);
    ~Quit_MessageBox();
private:

};
#endif // QUIT_MESSAGEBOX_H
