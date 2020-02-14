#-------------------------------------------------
#
# Project created by QtCreator 2019-12-29T10:18:55
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyGridLayout
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    Item.cpp \
    itemWidget/HeadImg.cpp \
    itemWidget/OtherSectionWidget.cpp \
    itemWidget/SelfSectionWidget.cpp \
    itemWidget/SeniorConversationItem.cpp \
    itemWidget/StarsWidget.cpp \
    itemWidget/animation/SequenceFrame.cpp \
    dlg/dialog.cpp

HEADERS += \
        widget.h \
    Item.h \
    itemWidget/HeadImg.h \
    itemWidget/OtherSectionWidget.h \
    itemWidget/SelfSectionWidget.h \
    itemWidget/SeniorConversationItem.h \
    itemWidget/StarsWidget.h \
    itemWidget/RolePlayDefine.h \
    itemWidget/animation/SequenceFrame.h \
    dlg/dialog.h

FORMS += \
        widget.ui \
    Item.ui \
    itemWidget/OtherSectionWidget.ui \
    itemWidget/SelfSectionWidget.ui \
    itemWidget/SeniorConversationItem.ui \
    dlg/dialog.ui

RESOURCES += \
    res.qrc
