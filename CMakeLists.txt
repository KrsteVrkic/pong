cmake_minimum_required(VERSION 3.20)

project(Pong LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(pong
	src/main.cpp
	src/app/Game.cpp
	src/input/Input.cpp
	src/gameplay/GameLogic.cpp
	src/render/Divider.cpp
	src/render/Renderer.cpp
)

target_link_libraries(pong PRIVATE raylib)

add_custom_command(TARGET pong POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_SOURCE_DIR}/assets/audio"
		"$<TARGET_FILE_DIR:pong>/assets/audio"
)
