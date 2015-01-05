cmake_minimum_required (VERSION 3.1)
project (hlredact)

set (CMAKE_CXX_STANDARD 11)

set (Boost_USE_STATIC_LIBS ON)
find_package (Boost 1.57.0 REQUIRED COMPONENTS chrono date_time system thread)
include_directories (${Boost_INCLUDE_DIR})

add_subdirectory (libhltas)

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
find_package (Qt5Widgets REQUIRED)

include_directories (src libhltas/src)

add_executable (hlredact
	src/autofdelegate.cpp
	src/framemodel.cpp
	src/frameview.cpp
	src/ftdelegate.cpp
	src/main.cpp
	src/mainwindow.cpp
	src/numrepdelegate.cpp
	src/strafedelegate.cpp
	src/toggledelegate.cpp
	src/yawdelegate.cpp)
target_link_libraries (hlredact hltas Qt5::Widgets ${Boost_LIBRARIES})
