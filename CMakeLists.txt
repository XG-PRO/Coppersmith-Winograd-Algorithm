cmake_minimum_required(VERSION 3.17)
project(Coppersmith_Winograd_Algorithm)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(.idea)

add_executable(Coppersmith_Winograd_Algorithm
        .idea/.gitignore
        .idea/Coppersmith-Winograd-Algorithm.iml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        LICENSE
        main.c
        README.md "Determinant v2.c")
