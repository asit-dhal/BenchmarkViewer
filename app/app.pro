QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BenchmarkViewer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    context.cpp \
    parser.cpp \
    benchmarkmodel.cpp \
    measurement.cpp \
    helper.cpp \
    benchmark.cpp \
    benchmarkview.cpp \
    benchmarkdelegate.cpp \
    chartviewwidget.cpp \
    benchmarkproxymodel.cpp

HEADERS += \
        mainwindow.h \
    context.h \
    parser.h \
    benchmarkmodel.h \
    measurement.h \
    helper.h \
    benchmark.h \
    benchmarkview.h \
    benchmarkdelegate.h \
    chartviewwidget.h \
    benchmarkproxymodel.h
