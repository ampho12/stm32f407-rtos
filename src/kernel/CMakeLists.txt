cmake_minimum_required(VERSION 3.10)
project(kernel)

# Variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HEADERS
  )

set(SOURCE_FILES
  src/main.c
  )

set(LINKER_SCRIPT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/link.ld)

# kernel elf
add_executable(main.elf ${SOURCE_FILES})
target_link_libraries(main.elf PRIVATE
  proc
  kmem
  gpio
  rcc
  usart
  debug_utils
  logging
  )

target_link_options(main.elf PRIVATE -T ${LINKER_SCRIPT_PATH})
target_link_options(main.elf PRIVATE
  -nostdlib
  -nostartfiles
  )

set_target_properties(main.elf
  PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT_PATH}
  )

add_custom_command(
  TARGET main.elf POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:main.elf> ${CMAKE_BINARY_DIR}/main.bin
  COMMENT "Running objcopy on main.elf"
  COMMENT "Image: main.bin"
  DEPENDS main.elf
  )
  

