cmake_minimum_required(VERSION 3.10)
project(usart)

# Variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HEADERS
  ${INCLUDE_DIR}/usart/usart.h
  )

set(SOURCE_FILES
  src/usart.c
  )


# USART LIBRARY
add_library(usart STATIC ${SOURCE_FILES} ${HEADERS})
target_link_libraries(usart PUBLIC
  utils
  rcc
  gpio
  )
target_include_directories(usart PUBLIC ${INCLUDE_DIR})
