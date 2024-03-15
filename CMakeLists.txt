cmake_minimum_required(VERSION 3.24)

option(BUILD_CLIENT "Build Client" ON)
option(BUILD_SERVER "Build Client" ON)

include(${CMAKE_CURRENT_BINARY_DIR}/local_conf.cmake OPTIONAL)

project(videoStreamer VERSION 1.0 DESCRIPTION "" LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(GNUInstallDirs)

add_subdirectory(Utils)

if(BUILD_CLIENT)
	add_subdirectory(Client)
endif(BUILD_CLIENT)



if(BUILD_SERVER)
	add_subdirectory(Server)
endif(BUILD_SERVER)


