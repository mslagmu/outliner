#-------------------------------------------------
#
# Project created by QtCreator 2016-07-09T17:47:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = outliner
TEMPLATE = app


SOURCES += main.cpp\
        outlinerviewer.cpp \
        notetreewidget.cpp \
    notetextedit.cpp \
    noteitem.cpp \
    sizedelegate.cpp \
    colorbox.cpp \
    aes.cpp \
    AESStringCrypt.cpp \
    sha256.cpp

HEADERS  += outlinerviewer.h \
            notetreewidget.h \
    notetextedit.h \
    noteitem.h \
    sizedelegate.h \
    colorbox.h \
    aes.h \
    AESStringCrypt.h \
    sha256.h

FORMS    += outlinerviewer.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS = outliner_fr_FR.ts
