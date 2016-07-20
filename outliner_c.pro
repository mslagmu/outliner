#-------------------------------------------------
#
# Project created by QtCreator 2016-07-09T17:47:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = outliner_c
TEMPLATE = app


SOURCES += main.cpp\
        outlinerviewer.cpp \
        notetreewidget.cpp \
    notetextedit.cpp \
    noteitem.cpp \
    sizedelegate.cpp \
    colorbox.cpp

HEADERS  += outlinerviewer.h \
            notetreewidget.h \
    notetextedit.h \
    noteitem.h \
    sizedelegate.h \
    colorbox.h

FORMS    += outlinerviewer.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS = outliner_fr_FR.ts
