cmake_minimum_required(VERSION 3.10)
project(proc)

# Variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HEADERS
  ${INCLUDE_DIR}/proc/proc.h
  )

set(SOURCE_FILES
  src/proc.c
  )


# PROC LIBRARY
add_library(proc STATIC ${SOURCE_FILES} ${HEADERS})
target_link_libraries(proc PUBLIC utils)
target_link_libraries(proc PUBLIC kmem)
target_include_directories(proc PUBLIC ${INCLUDE_DIR})
