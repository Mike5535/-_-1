cmake_minimum_required(VERSION 3.0.0)
project(products)

add_executable( ${PROJECT_NAME} main.c )

add_subdirectory(input)
add_subdirectory(output)

message("INPUT_LIB_INCLUDE_DIRS = ${INPUT_LIB_INCLUDE_DIRS}")
message("INPUT_LIB_LIBRARIES = ${INPUT_LIB_LIBRARIES}")

message("OUTPUT_LIB_INCLUDE_DIRS = ${OUTPUT_LIB_INCLUDE_DIRS}")
message("OUTPUT_LIB_LIBRARIES = ${OUTPUT_LIB_LIBRARIES}")



set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${INPUT_LIB_INCLUDE_DIRS}  ;${OUTPUT_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${INPUT_LIB_LIBRARIES} ;${OUTPUT_LIB_LIBRARIES})


add_subdirectory(tests)