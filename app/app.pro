# =========================================================================
#
#   Program: BenchmarkViewer
#
#   Copyright (c) 2018 Asit Dhal
#   All rights reserved.

#   BenchmarkViewer is a free software; you can redistribute it and/or modify it.


#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
#   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
#   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#========================================================================*/

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BenchmarkViewer
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    benchmarkmodel.cpp \
    benchmarkview.cpp \
    benchmarkdelegate.cpp \
    benchmarkproxymodel.cpp \
    appconfig.cpp \
    bmcolumns.cpp \
    globals.cpp 

HEADERS += \
        mainwindow.h \
    benchmarkmodel.h \
    benchmarkview.h \
    benchmarkdelegate.h \
    benchmarkproxymodel.h \
    appconfig.h \
    bmcolumns.h \
    globals.h 

DISTFILES += \
    appconfig.ini \
    CMakeLists.txt

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../model/release/ -lmodel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../model/debug/ -lmodel
else:unix: LIBS += -L$$OUT_PWD/../model/ -lmodel

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../view/release/ -lview
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../view/debug/ -lview
else:unix: LIBS += -L$$OUT_PWD/../view/ -lview


INCLUDEPATH += $$PWD/../model
INCLUDEPATH += $$PWD/../view

DEPENDPATH += $$PWD/../model
DEPENDPATH += $$PWD/../view
