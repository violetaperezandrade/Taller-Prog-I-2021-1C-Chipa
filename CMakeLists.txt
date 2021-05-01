cmake_minimum_required(VERSION 3.19)
project(DonkeyKong)

set(CMAKE_CXX_STANDARD 11)

add_executable(DonkeyKong src/main.cpp src/model/Stair.cpp src/model/Stair.h src/model/Barrel.cpp src/model/Barrel.h)