cmake_minimum_required(VERSION 2.8)
project(Hive)

add_definitions(-std=c++0x)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

add_subdirectory(src)