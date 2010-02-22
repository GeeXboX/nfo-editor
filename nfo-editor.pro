# -------------------------------------------------
# Project created by QtCreator 2010-02-09T08:29:09
# -------------------------------------------------
QT += network \
    xml \
    xmlpatterns \
    testlib
TARGET = nfo-editor
TEMPLATE = app
SOURCES += main.cpp \
    nfomain.cpp
HEADERS += nfomain.h
FORMS += nfomainwindow.ui
OTHER_FILES += icons/icon_enna_128.png
LIBS += -lnfo -lvalhalla
INCLUDEPATH += -I"/usr/include"
