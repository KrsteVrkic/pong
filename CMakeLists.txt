cmake_minimum_required(VERSION 3.20)

project(Pong LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Do not build raylib examples" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "Do not build raylib games" FORCE)

FetchContent_Declare(
	raylib
	URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
	DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(raylib)

add_executable(pong
	src/main.cpp
	src/app/Game.cpp
	src/input/Input.cpp
	src/gameplay/GameLogic.cpp
	src/render/Divider.cpp
	src/render/Renderer.cpp
)

target_link_libraries(pong PRIVATE raylib)
target_link_options(pong PRIVATE -static-libstdc++ -static-libgcc)
