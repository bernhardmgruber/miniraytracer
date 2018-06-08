project(utils)

file(GLOB source_files *.cpp *.h *.hpp)
add_library(${PROJECT_NAME} STATIC ${source_files})
source_group("" FILES ${source_files})

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()
