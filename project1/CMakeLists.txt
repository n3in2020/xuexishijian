cmake_minimum_required(VERSION 3.10)

Project(project1)
include_directories(include)
add_executable(project1
            src/main.cpp
            src/hero.cpp
            src/actor.cpp
            src/actor_plusarmor.cpp
            src/weapon.cpp
            src/thegame.cpp
            )