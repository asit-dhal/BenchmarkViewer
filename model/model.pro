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

QT       += core
QT       -= gui

TARGET = model
TEMPLATE = lib
CONFIG += staticlib c++14

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    benchmark.cpp \
    context.cpp \
    measurement.cpp \
    helper.cpp \
    abstractparser.cpp \
    jsonparser.cpp \
    csvparser.cpp
    
HEADERS += \
    modelglobals.h \
    benchmark.h \
    context.h \
    measurement.h \
    helper.h \
    abstractparser.h \
    jsonparser.h \
    csvparser.h
    
    
