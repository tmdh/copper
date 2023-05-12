cmake_minimum_required(VERSION 3.16.0)
project(copper VERSION 0.1.0)

set(QT_MIN_VERSION "5.15.2")
set(KF5_MIN_VERSION "5.36.0")
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)


include(KDEClangFormat)
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})


find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Widgets
)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    TextEditor
)

add_executable(copper main.cpp mainwindow.cpp mainsplitter.cpp tab.cpp testcasewidget.cpp testcase.cpp)

target_link_libraries(copper
    Qt5::Widgets
    KF5::TextEditor
)
