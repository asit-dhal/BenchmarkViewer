set(SRCS
    abstractparser.cpp
    benchmark.cpp
    context.cpp
    csvparser.cpp
    helper.cpp
    jsonparser.cpp
    measurement.cpp
    modelglobals.cpp
)

set(LIB_NAME model)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(${LIB_NAME} static ${SRCS})

target_link_libraries(${LIB_NAME}
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        Qt5::Charts
    )
