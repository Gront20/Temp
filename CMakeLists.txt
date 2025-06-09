
cmake_minimum_required(VERSION 3.10)
project(fakekeyboard-qt)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/wayland)

add_executable(fakekeyboard-qt
    main.cpp
    mainwindow.cpp
    inputmethod.cpp
)

target_link_libraries(fakekeyboard-qt Qt5::Widgets wayland-client)
