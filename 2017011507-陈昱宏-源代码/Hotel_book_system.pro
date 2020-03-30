#-------------------------------------------------
#
# Project created by QtCreator 2018-07-18T09:44:24
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hotel_book_system
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Account.cpp \
    Login_Dialog.cpp \
    WelcomeWindow.cpp \
    Register_Dialog.cpp \
    Search_Dialog.cpp \
    RegisterConfirmDialog.cpp \
    Search.cpp \
    Hotal.cpp \
    NormalUser.cpp \
    HotalUser.cpp \
    PlatformUser.cpp \
    PinJiaMessage.cpp \
    PersonalInfo.cpp \
    PlatformManage.cpp \
    Message.cpp \
    Room.cpp \
    HotalOrder.cpp \
    MainWindow.cpp \
    SearchOrder.cpp \
    OrderDetail.cpp \
    HotalManage.cpp \
    HotalDetail.cpp \
    PinJiaDetail.cpp \
    MessageDetail.cpp \
    ShenHeHotal.cpp \
    ShenHeOrder.cpp \
    ReceiveMessage.cpp \
    SendMessageDialog.cpp \
    WritePinJia.cpp \
    CancelOrder.cpp \
    CreateOrder.cpp \
    PayMoney.cpp \
    ChangeHotalInfo.cpp \
    CreateHotal.cpp \
    CreateRoom.cpp \
    RoomDetail.cpp \
    ChangeRoom.cpp

HEADERS += \
    Login_Dialog.h \
    Account.h \
    WelcomeWindow.h \
    Register_Dialog.h \
    Search_Dialog.h \
    RegisterConfirmDialog.h \
    Search.h \
    HotalOrder.h \
    Room.h \
    Hotal.h \
    NormalUser.h \
    HotalUser.h \
    PlatformUser.h \
    PinJiaMessage.h \
    Message.h \
    Connection.h \
    PersonalInfo.h \
    PlatformManage.h \
    MainWindow.h \
    emptywidget.h \
    SearchOrder.h \
    OrderDetail.h \
    HotalManage.h \
    HotalDetail.h \
    PinJiaDetail.h \
    MessageDetail.h \
    ShenHeHotal.h \
    ShenHeOrder.h \
    ReceiveMessage.h \
    SendMessageDialog.h \
    WritePinJia.h \
    CancelOrder.h \
    CreateOrder.h \
    PayMoney.h \
    ChangeHotalInfo.h \
    CreateHotal.h \
    CreateRoom.h \
    ChangeRoom.h \
    RoomDetail.h

RESOURCES += \
    picture.qrc
