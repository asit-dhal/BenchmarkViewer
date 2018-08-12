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

set(MODEL_SRCS
    src/abstractparser.cpp
    src/benchmark.cpp
    src/context.cpp
    src/csvparser.cpp
    src/jsonparser.cpp
    src/parserfactory.cpp
    src/measurement.cpp
    src/model_globals.cpp
    src/helper.cpp
    src/benchmarkmodel.cpp
)

set(MOC_HEADERS
    include/model/abstractparser.h
    include/model/benchmarkmodel.h
    include/model/csvparser.h
    include/model/jsonparser.h
)

add_library(model ${MODEL_SRCS} ${MOC_HEADERS})
add_library(app::model ALIAS model)

target_include_directories(model
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(model
    Qt5::Core
    Qt5::Gui
)

include (CMakePrintHelpers)
message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
cmake_print_properties(TARGETS model PROPERTIES INTERFACE_INCLUDE_DIRECTORIES IMPORTED_LOCATION)
cmake_print_properties(TARGETS model PROPERTIES INCLUDE_DIRECTORIES IMPORTED_LOCATION)

