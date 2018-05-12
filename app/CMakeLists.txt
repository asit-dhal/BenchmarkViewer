file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(BVR_HDR
    appconfig.h
    benchmark.h
    context.h
    helper.h
    measurement.h
)

set(BVR_MOC_HDR
    benchmarkdelegate.h
    benchmarkmodel.h
    benchmarkproxymodel.h
    benchmarkview.h
    chartviewwidget.h
    mainwindow.h
    parser.h
)

set(BVR_SRC
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

include_directories(${ADDITIONAL_INCLUDE_PATHS}
                ${Qt5Widgets_INCLUDE_DIRS}
                ${Qt5Charts_INCLUDE_DIRS}
                ${Qt5Core_INCLUDE_DIRS}
                 src)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Charts_DEFINITIONS})
add_definitions(${Qt5Core_DEFINITIONS})

add_executable( PROJECT_NAME ${BVR_SRC})

target_link_libraries( PROJECT_NAME
                    ${Qt5Widgets_LIBRARIES}
                    ${Qt5Charts_LIBRARIES}
                    ${Qt5Core_LIBRARIES}
                    )

qt5_use_modules(PROJECT_NAME Widgets Charts Core Gui)

