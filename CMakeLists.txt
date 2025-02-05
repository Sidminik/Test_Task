cmake_minimum_required(VERSION 3.10)

project(test_task_1.7)
#library   VERSION 1.5
#program_1 VERSION 1.7
#program_2 VERSION 1.6

find_package(Boost REQUIRED)

# Добавляем подкаталоги с библиотекой и программой
add_subdirectory(library)
add_subdirectory(program_1)
add_subdirectory(program_2)
