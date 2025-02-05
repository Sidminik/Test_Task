# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10) 

# Версия проекта библиотеки
project(library VERSION 1.5) 

# Создание динамической библиотеки
add_library(library SHARED library.cpp)

# Указание директории с заголовочными файлами
target_include_directories(library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})