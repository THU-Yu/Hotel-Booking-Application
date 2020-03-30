#ifndef EMPTYWIDGET_H
#define EMPTYWIDGET_H

#include <QWidget>

class EmptyWidget:public QWidget
{
    Q_OBJECT

public:
    EmptyWidget(QWidget *parent=0):QWidget(parent){}
    ~EmptyWidget(){}
};

#endif // EMPTYWIDGET_H
