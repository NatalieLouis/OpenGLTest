cmake_minimum_required(VERSION 3.12)


project(OpenGL_Test)

set(CMAKE_CXX_STANDARD 17)

include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include
)

link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib
)

add_executable(OpenGL_Test "main.cpp" "glad.c")

target_link_libraries(OpenGL_Test glfw3.lib )