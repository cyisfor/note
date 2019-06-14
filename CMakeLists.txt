cmake_minimum_required(VERSION 3.0)
project(note VERSION 0.1)

# just a dumb example to show how to use note

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}") 
  add_executable(example_note
	note.c example.c)
endif()
