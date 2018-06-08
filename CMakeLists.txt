# have a look at https://github.com/lefticus/cpp_starter_project

cmake_minimum_required(VERSION 3.0)

# find external libraries
find_package(Boost REQUIRED COMPONENTS system filesystem)
add_definitions(${Boost_DEFINITIONS})
include_directories(${Boost_INCLUDE_DIRS})

# own libraries and executables
add_subdirectory(src)

# custom render target for easy testing
add_custom_target(
	render
	COMMAND miniraytracer ${CMAKE_CURRENT_SOURCE_DIR}/scenes/cubicballs.txt png 1024 768
	COMMENT "Rendering scene: cubicballs"
)
add_dependencies(render miniraytracer)
