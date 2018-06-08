# have a look at https://github.com/lefticus/cpp_starter_project

project(imagewrite)

file(GLOB source_files *.cpp *.h *.hpp)
add_library(${PROJECT_NAME} SHARED ${source_files})
source_group("" FILES ${source_files})

target_link_libraries(${PROJECT_NAME}
	${Boost_LIBRARIES}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_SHARED_LIBRARY)

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()
