project(BenchmarkViewer)

cmake_minimum_required(VERSION 3.2.2)

set(PROJECT_NAME "BenchmarkViewer")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

add_subdirectory(app)



