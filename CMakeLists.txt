cmake_minimum_required(VERSION 3.10)


# message("$ENV{PATH}")

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)

# compile static library for testing
# we don't have _exit, main, _start etc as we are in bare metal
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(rtos)

add_compile_options(-O2)
add_compile_options(-mcpu=cortex-m4)
add_compile_options(-fno-builtin)
# add_compile_options(-nostdlib)
# add_compile_options(-nostartfiles)
# add_compile_options(-no-stdlib)


add_subdirectory(src/common)
add_subdirectory(src/rcc)
add_subdirectory(src/gpio)
add_subdirectory(src/logging)
add_subdirectory(src/kmem)
add_subdirectory(src/usart)
add_subdirectory(src/debug_utils)
add_subdirectory(src/proc)
add_subdirectory(src/kernel)
  


