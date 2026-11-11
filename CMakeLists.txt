cmake_minimum_required(VERSION 3.30)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ProgrammingTraining LANGUAGES C CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(MAIN_SOURCE_FILE_NAME "source")

add_compile_options(/W4 /WX /external:anglebrackets /external:W0)
add_link_options($<$<CONFIG:Debug>:/INCREMENTAL>)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(src/Assignment_1)
add_subdirectory(src/Assignment_2)
add_subdirectory(src/Assignment_3)
add_subdirectory(src/Assignment_4)
add_subdirectory(src/Assignment_4_2)
add_subdirectory(src/Assignment_5)
