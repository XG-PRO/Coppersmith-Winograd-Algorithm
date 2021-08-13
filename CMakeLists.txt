cmake_minimum_required(VERSION 3.19)
project(Coppersmith_Winograd_Algorithm)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(.idea)

add_executable(Coppersmith_Winograd_Algorithm
        .idea/.gitignore
        .idea/Coppersmith-Winograd-Algorithm.iml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        LICENSE
        main.cpp
        README.md)