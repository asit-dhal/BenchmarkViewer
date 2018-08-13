set(VIEW_SRCS
    src/benchmarkview.cpp
    src/chartview.cpp
    src/globals.cpp
)

set(VIEW_MOC_HEADERS
    include/view/benchmarkview.h
    include/view/chartview.h
    )

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(view ${VIEW_SRCS} ${VIEW_MOC_HEADERS})
add_library(app::view ALIAS view)

target_include_directories(view
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
    PRIVATE app::presenter
    PRIVATE app::model
)
target_link_libraries(view
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Charts
    app::presenter
    app::model
)
