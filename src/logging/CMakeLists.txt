cmake_minimum_required(VERSION 3.10)
project(logging)

# Variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HEADERS
  ${INCLUDE_DIR}/logging/logging.h
  )

set(SOURCE_FILES
  src/printk.c
  )


# LOGGING LIBRARY
add_library(logging STATIC ${SOURCE_FILES} ${HEADERS})
target_link_libraries(logging PUBLIC utils)
target_include_directories(logging PUBLIC ${INCLUDE_DIR})
