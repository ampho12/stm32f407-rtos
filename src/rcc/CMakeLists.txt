cmake_minimum_required(VERSION 3.10)
project(rcc)

# Variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HEADERS ${INCLUDE_DIR}/rcc/rcc.h)
set(SOURCE_FILES src/rcc.c)


# RCC LIBRARY
add_library(rcc STATIC ${SOURCE_FILES} ${HEADERS})
target_link_libraries(rcc PUBLIC utils)
target_include_directories(rcc PUBLIC ${INCLUDE_DIR})
