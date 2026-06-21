cmake_minimum_required(VERSION 3.28)
project(Assignment_4 C)

set(CMAKE_C_STANDARD 99)

add_executable(Assignment_4 main.c
        BNode.c
        BSearchTree.c
        BNode.h
        BSearchTree.h)
