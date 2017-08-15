#-------------------------------------------------
#
# Project created by QtCreator 2017-08-08T19:13:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BoneMineralDensity
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
        MainWindow.cpp \
    PageConstructMesh.cpp \
    StackedConstructMesh.cpp \
    PageDensityAnalysis.cpp \
    StackedDensityAnalysis.cpp \
    WidgetAnalysisMeshItem.cpp \
    PageSegmentMesh.cpp \
    StackedSegmentMesh.cpp

HEADERS += \
        MainWindow.h \
    PageConstructMesh.h \
    StackedConstructMesh.h \
    PageDensityAnalysis.h \
    StackedDensityAnalysis.h \
    WidgetAnalysisMeshItem.h \
    PageSegmentMesh.h \
    StackedSegmentMesh.h

FORMS += \
        MainWindow.ui \
    PageConstructMesh.ui \
    StackedConstructMesh.ui \
    PageDensityAnalysis.ui \
    StackedDensityAnalysis.ui \
    WidgetAnalysisMeshItem.ui \
    PageSegmentMesh.ui \
    StackedSegmentMesh.ui

CONFIG += c++11
