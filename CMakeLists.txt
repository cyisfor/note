cmake_minimum_required(VERSION 3.0)
project(note VERSION 0.1)

add_library(note note.c)
target_include_directories(note PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# just a dumb example to show how to use note

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}") 
  add_executable(example_note
	example.c)
  target_link_libraries(example_node PRIVATE note)
endif()
