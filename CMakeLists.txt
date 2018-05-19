cmake_minimum_required(VERSION 3.9)
project(Trabalho_ED2_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Trabalho_ED2_2
        Headers/Answer.h
        Headers/BinaryTree.h
        Headers/FileUtils.h
        Headers/Node.h
        Headers/Question.h
        Headers/Tag.h
        Source/Answer.cpp
        Source/BinaryTree.cpp
        Source/FileUtils.cpp
        Source/Question.cpp
        Source/Tag.cpp
        main.cpp Source/AvlTree.cpp Headers/AvlTree.h Headers/NodeAvl.h)
