#-------------------------------------------------
#
# Project created by QtCreator 2012-11-22T22:10:45
#
#-------------------------------------------------

QT       += core gui phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = final
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plant.cpp \
    sunflower.cpp \
    backgroundmusic.cpp

HEADERS  += mainwindow.h \
    plant.h \
    sunflower.h \
    backgroundmusic.h

FORMS    +=

RESOURCES += \
    plant.qrc
