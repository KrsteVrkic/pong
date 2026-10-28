cmake_minimum_required(VERSION 3.20)

project(Pong LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib CONFIG REQUIRED)

add_executable(pong
	src/main.cpp
	src/Game.cpp
)

target_link_libraries(pong PRIVATE raylib)
