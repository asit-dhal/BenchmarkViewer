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

find_package(Qt5Widgets 5.10 REQUIRED)
find_package(Qt5Charts 5.10 REQUIRED)
find_package(Qt5Core 5.10 REQUIRED)
find_package(Qt5Gui 5.10 REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(presenter)
#add_subdirectory(test)

set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

set(SRCS
    src/appconfig.cpp
    src/main.cpp
    src/mainwindow.cpp
    src/globals.cpp
    src/mainwindowpresenter.cpp
)

set(MOC_HEADERS
    include/app/mainwindow.h
    include/app/mainwindowpresenter.h
    )

add_executable(benchmarkViewer ${SRCS} ${MOC_HEADERS})

set_property(TARGET benchmarkViewer APPEND PROPERTY AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

target_include_directories(benchmarkViewer
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE app::model
    PRIVATE app::view
    PRIVATE app::presenter
)

target_link_libraries(benchmarkViewer
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Charts
    app::model
    app::view
    app::presenter
)

