project(miniraytracer)

add_subdirectory(imagewrite)
add_subdirectory(utils)

file(GLOB source_files *.cpp *.h *.hpp)
add_executable(${PROJECT_NAME} ${source_files})
source_group("" FILES ${source_files})

target_link_libraries(${PROJECT_NAME}
	imagewrite
	utils
	${Boost_LIBRARIES}
)

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

#target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
