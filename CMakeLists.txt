cmake_minimum_required(VERSION 3.0.0)
project(copper VERSION 0.1.0)

set(QT_MIN_VERSION "5.15.2")

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Widgets
)

add_executable(copper main.cpp)

target_link_libraries(copper
    Qt5::Widgets
)
