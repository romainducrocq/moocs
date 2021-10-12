cmake_minimum_required(VERSION 3.5)

project(exec)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/../src/")
set(HEADER_DIR "${PROJECT_SOURCE_DIR}/../include/")
set(EXEC_DIR "${PROJECT_SOURCE_DIR}/../bin/app/")
set(LINK_LIB "-lsfml-graphics -lsfml-window -lsfml-system")

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${HEADER_DIR}/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${LINK_LIB})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${EXEC_DIR}")
