# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Версия проекта
project(test_task_1.7)
#library   VERSION 1.5
#program_1 VERSION 1.7
#program_2 VERSION 1.6

# Поиск и подключение библиотек Boost 
find_package(Boost REQUIRED)

# Добавляем подкаталоги с библиотекой и программой
add_subdirectory(library)
add_subdirectory(program_1)
add_subdirectory(program_2)
