# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Версия проекта Программы 2
project(program_2 VERSION 1.6)

# Добавление исполняемого файла
add_executable(program_2 program_2.cpp data_processor.cpp)

# Линковка с динамической библиотекой
find_library(MY_LIBRARY NAMES library PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../library)

# Связывание исполняемого файла с библиотекой
target_link_libraries(program_2 library)
