enable_testing()

set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

set(TEST_SRCS main.cpp model_test.cpp)

add_executable(benchmarkTest ${TEST_SRCS})

add_test(benchmarkTest benchmarkTest)

target_link_libraries(benchmarkTest
    Qt5::Test
    app::model
)
