set(PRESENTER_SRCS
    src/benchmarkproxymodel.cpp
    src/presenter_globals.cpp
    src/chartpresenter.cpp
    src/benchmarkdelegate.cpp
    src/benchmarkpresenter.cpp
    src/chartproxymodel.cpp
)

set(MOC_HEADERS
    include/presenter/benchmarkdelegate.h
    include/presenter/benchmarkpresenter.h
    include/presenter/chartpresenter.h
    include/presenter/chartproxymodel.h
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(presenter ${PRESENTER_SRCS} ${MOC_HEADERS})
add_library(app::presenter ALIAS presenter)

target_include_directories(presenter
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
    PRIVATE app::model
)

target_link_libraries(presenter
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Charts
    app::model
    app::view
)
