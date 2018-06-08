cmake_minimum_required(VERSION 3.0)

project(miniraytracer)

# find external libraries
find_package(Boost REQUIRED)
add_definitions(${Boost_DEFINITIONS})
include_directories(${Boost_INCLUDE_DIRS})

# own libraries and executables
add_subdirectory(src)

# custom render target for easy testing
add_custom_target(
	render
	COMMAND ${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/scenes/cubicballs.txt 1024 768
	COMMENT "Rendering scene: cubicballs"
)
add_dependencies(render ${PROJECT_NAME})
