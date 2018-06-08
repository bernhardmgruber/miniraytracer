cmake_minimum_required(VERSION 3.0)

project (MiniRayTracer)

add_subdirectory(src)

add_custom_target(
	Render
	COMMAND ${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/scenes/cubicballs.txt 1024 768
	COMMENT "Rendering scene: cubicballs"
)
add_dependencies(Render ${PROJECT_NAME})
