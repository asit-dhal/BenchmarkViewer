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

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets 5.10 REQUIRED)
find_package(Qt5Charts 5.10 REQUIRED)
find_package(Qt5Core 5.10 REQUIRED)
find_package(Qt5Gui 5.10 REQUIRED)

set(SRCS
    appconfig.cpp
    benchmark.cpp
    benchmarkdelegate.cpp
    benchmarkmodel.cpp
    benchmarkproxymodel.cpp
    benchmarkview.cpp
    chartviewwidget.cpp
    context.cpp
    helper.cpp
    main.cpp
    mainwindow.cpp
    measurement.cpp
    abstractparser.cpp
    jsonparser.cpp
    csvparser.cpp
    globals.cpp
    bmcolumns.cpp
    worker.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME}
                    Qt5::Widgets
                    Qt5::Core
                    Qt5::Gui
                    Qt5::Charts
                    )

