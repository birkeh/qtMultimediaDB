#-------------------------------------------------
#
# Project created by QtCreator 2016-02-16T11:33:54
#
#-------------------------------------------------

QT       += core gui network xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtMultimediaDB
TEMPLATE = app
RC_ICONS = qtMultimediaDB.ico

SOURCES += main.cpp\
        cmainwindow.cpp \
    cserie.cpp \
    cseasondelegate.cpp \
    cseason.cpp \
    cepisode.cpp \
    csearch.cpp \
    cmessageanimatedialog.cpp \
    cedit.cpp \
    cseasondetails.cpp \
    cverticallabel.cpp \
    cepisodedetails.cpp \
    cmessagedialog.cpp \
    cupdatethread.cpp \
    cpicturesthread.cpp \
    cthemoviedbv3.cpp \
    cmovie.cpp \
    cmoviesearch.cpp \
    cmovieviewitemdelegate.cpp \
    common.cpp \
    cmovieedit.cpp \
    cmovieimage.cpp \
    cscrollarea.cpp \
    cpixmapwidget.cpp \
    cfanart.cpp \
    cfanarttv.cpp \
    cfanartimage.cpp \
    cexportdialog.cpp \
    cdiscover.cpp \
    cmoviediscover.cpp \
    qxtspanslider.cpp \
    ccheckboxitemdelegate.cpp \
    cmoviedetails.cpp \
    cseriedetails.cpp \
    ctheaudiodbv1.cpp \
    cartist.cpp

HEADERS  += cmainwindow.h \
    cserie.h \
    cseasondelegate.h \
    cseason.h \
    cepisode.h \
    csearch.h \
    cmessageanimatedialog.h \
    cedit.h \
    cseasondetails.h \
    cverticallabel.h \
    cepisodedetails.h \
    cmessagedialog.h \
    cupdatethread.h \
    cpicturesthread.h \
    cthemoviedbv3.h \
    cmovie.h \
    cmoviesearch.h \
    cmovieviewitemdelegate.h \
    common.h \
    cmovieedit.h \
    cmovieimage.h \
    cscrollarea.h \
    cpixmapwidget.h \
    cfanart.h \
    cfanarttv.h \
    cfanartimage.h \
    cexportdialog.h \
    cdiscover.h \
    cmoviediscover.h \
    qxtspanslider.h \
    qxtspanslider_p.h \
    ccheckboxitemdelegate.h \
    cmoviedetails.h \
    cseriedetails.h \
    ctheaudiodbv1.h \
    cartist.h

FORMS    += cmainwindow.ui \
    csearch.ui \
    cmessageanimatedialog.ui \
    cedit.ui \
    cseasondetails.ui \
    cepisodedetails.ui \
    cmessagedialog.ui \
    cmoviesearch.ui \
    cmovieedit.ui \
    cexportdialog.ui \
    cdiscover.ui \
    cmoviediscover.ui \
    cmoviedetails.ui \
    cseriedetails.ui

DISTFILES += \
    Doxyfile \
    logo.jpg \
    splash.jpg \
    splashEmpty.png \
    qtMultimediaDB.ico

RESOURCES += \
    resource.qrc
