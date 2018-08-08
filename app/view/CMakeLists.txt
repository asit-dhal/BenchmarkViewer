set(VIEW_SRCS
    src/benchmarkview.cpp
    src/chartviewwidget.cpp
    src/globals.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(view ${VIEW_SRCS})
add_library(app::view ALIAS view)

target_include_directories(view
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
target_link_libraries(view
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Charts
)
