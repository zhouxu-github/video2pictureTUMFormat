cmake_minimum_required(VERSION 3.17)
project(video2picture)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(video2picture main.cpp)
target_link_libraries(${PROJECT_NAME}
        ${OpenCV_LIBS})