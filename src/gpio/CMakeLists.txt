cmake_minimum_required(VERSION 3.10)
project(gpio)

# Variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HEADERS
  ${INCLUDE_DIR}/gpio/gpio.h
  ${INCLUDE_DIR}/gpio/pinmap.h
  )

set(SOURCE_FILES
  src/gpio.c
  )


# GPIO LIBRARY
add_library(gpio STATIC ${SOURCE_FILES} ${HEADERS})
target_link_libraries(gpio PUBLIC utils)
target_include_directories(gpio PUBLIC ${INCLUDE_DIR})
