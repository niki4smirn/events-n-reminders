cmake_minimum_required(VERSION 3.21)
project(events_n_reminders)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

add_executable(events_n_reminders main.cpp main_window.cpp)

target_link_libraries(events_n_reminders
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        )
