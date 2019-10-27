#-------------------------------------------
# Project : studentManager（学生综合测评系统）
# Version : 1.0.0
# Author  : Qiu Bing Wei
# Date    : 2019/07/06
#-------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = studentManager
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
    logindialog.cpp \
    mainwindow.cpp

HEADERS  += \
    logindialog.h \
    connection.h \
    mainwindow.h

FORMS    += \
    logindialog.ui \
    mainwindow.ui

RESOURCES += \
    myresources.qrc

RC_ICONS = icon.ico

DISTFILES += \
    finalfrontier.png
