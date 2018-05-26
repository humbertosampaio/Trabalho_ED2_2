cmake_minimum_required(VERSION 3.10)
project(Trabalho_ED2_2)

set(CMAKE_CXX_STANDARD 11)

include_directories(Headers)

add_executable(Trabalho_ED2_2
        Headers/Answer.h
        Headers/AvlNode.h
        Headers/AvlTree.h
        Headers/BinaryTree.h
        Headers/BTree.h
        Headers/CompareCount.h
        Headers/FileUtils.h
        Headers/Node.h
        Headers/NodeB.h
        Headers/NodeRB.h
        Headers/Question.h
        Headers/RBTree.h
        Headers/SplayTree.h
        Headers/Tag.h
        Source/BTree.cpp
        Source/CompareCount.cpp
        Source/NodeRB.cpp
        Source/RBTree.cpp
        Source/Answer.cpp
        Source/AvlNode.cpp
        Source/AvlTree.cpp
        Source/BinaryTree.cpp
        Source/FileUtils.cpp
        Source/Question.cpp
        Source/SplayTree.cpp
        Source/Tag.cpp
        main.cpp)
