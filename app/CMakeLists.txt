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
    parser.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME}
                    Qt5::Widgets
                    Qt5::Core
                    Qt5::Gui
                    Qt5::Charts
                    )

