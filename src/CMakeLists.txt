cmake_minimum_required(VERSION 3.12) 

message(STATUS "Creating build system for smolTankeryGame...")

add_library(smolTankeryGame "smolTankeryGame.cpp")
add_executable(smolTankeryGame_Exec "smolTankeryGame.cpp")