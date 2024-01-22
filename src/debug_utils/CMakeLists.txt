cmake_minimum_required(VERSION 3.10)
project(debug_utils)

# Variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HEADERS
  ${INCLUDE_DIR}/debug_utils/debug_utils.h
  )

set(SOURCE_FILES
  src/regdump.S
  src/stackdump.S
  )



# DEBUG LIBRARY
add_library(debug_utils STATIC ${SOURCE_FILES} ${HEADERS})
target_link_libraries(debug_utils PUBLIC logging)
target_include_directories(debug_utils PUBLIC ${INCLUDE_DIR})
set_target_properties(debug_utils PROPERTIES LINKER_LANGUAGE C)
