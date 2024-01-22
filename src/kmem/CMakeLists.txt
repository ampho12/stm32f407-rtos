cmake_minimum_required(VERSION 3.10)
project(kmem)

# Variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HEADERS
  ${INCLUDE_DIR}/kmem/kmem.h
  )

set(SOURCE_FILES
  src/kmem.c
  )


# KMEM LIBRARY
add_library(kmem STATIC ${SOURCE_FILES} ${HEADERS})
target_link_libraries(kmem PUBLIC utils)
target_link_libraries(kmem PUBLIC logging)
target_include_directories(kmem PUBLIC ${INCLUDE_DIR})
