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
    sizedelegate.cpp \
    colorbox.cpp \
    aes.cpp \
    AESStringCrypt.cpp \
    sha256.cpp \
    newnodedialog.cpp

HEADERS  += outlinerviewer.h \
            notetreewidget.h \
    notetextedit.h \
    sizedelegate.h \
    colorbox.h \
    aes.h \
    AESStringCrypt.h \
    sha256.h \
    newnodedialog.h

FORMS    += outlinerviewer.ui \
    newnodedialog.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS = outliner_fr_FR.ts
