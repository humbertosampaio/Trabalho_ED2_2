cmake_minimum_required(VERSION 3.9)
project(Trabalho_ED2_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Trabalho_ED2_2
        Headers/Answer.h
        Headers/FileUtils.h
        Headers/Question.h
        Headers/Tag.h
        Source/Answer.cpp
        Source/FileUtils.cpp
        Source/Question.cpp
        Source/Tag.cpp
        main.cpp)
