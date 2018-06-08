# have a look at https://github.com/lefticus/cpp_starter_project

file(GLOB source_files *.cpp *.h *.hpp)
add_executable(${PROJECT_NAME} ${source_files})

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /W4 /std:c++17)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)