cmake_minimum_required(VERSION 3.27)
project(rpg)

set(CMAKE_CXX_STANDARD 17)

add_executable(rpg main.cpp
        Character/Character.cpp
        Character/Character.h
        Player/Player.cpp
        Player/Player.h
        Enemy/Enemy.cpp
        Enemy/Enemy.h
        Utils.h
        Combat/Combat.cpp
        Combat/Combat.h
        Combat/Action.cpp
        Combat/Action.h
        Files/FileHandler.cpp
        Files/FileHandler.h
        Files/FileHandler.h)
