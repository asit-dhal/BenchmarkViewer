set(PRESENTER_SRCS
    benchmarkproxymodel.cpp
    presenter_globals.cpp
    chartpresenter.cpp
    benchmarkdelegate.cpp
    benchmarkpresenter.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(presenter ${PRESENTER_SRCS})
add_library(app::presenter ALIAS presenter)

target_include_directories(presenter
    PUBLIC ${PROJECT_SOURCE_DIR} app::model
)

target_link_libraries(presenter
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Charts
    app::model
    app::view
)
