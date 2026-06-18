cmake_minimum_required(VERSION 3.21)

project(MyQtApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(MyQtApp main.cpp config.cpp)

target_link_libraries(MyQtApp PRIVATE Qt6::Widgets)
