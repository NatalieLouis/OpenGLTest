cmake_minimum_required(VERSION 3.12)


project(OpenGL_Test)

set(CMAKE_CXX_STANDARD 17)
file(GLOB ASSETS "./assets")

file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include
)

add_subdirectory(application)
add_subdirectory(glframework)


link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib
)

add_executable(OpenGL_Test "main.cpp" "glad.c" "wrapper/checkError.h")

target_link_libraries(OpenGL_Test glfw3.lib application fw )