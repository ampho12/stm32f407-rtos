# Introduction

A simple RTOS for stm32f407 arm mcu. Currently a work in progress. The following features have been implemented in some capacity


- Clock Control (RCC)
- USART
- GPIO
- Memory Management
- Task Management
- Logging (`printf` like printing)
- Debugging (stack dump, memory dump, register dump over usart)


# Build

cmake based build

```
mkdir build
cd build
cmake ..
make
```

The file to be flashed is `build/main.bin`


# Editing

## Creating Modules

Use `create_module.sh` script to create a new cmake module. For example, to create `usart` module use `create_module.sh usart` in the project root directory.

A dummy `CMakeLists.txt` file will be created in the module root (i.e `src/usart/CMakeLists.txt')

Don't forget to add `add_subdirectory(src/usart)` to CMakeLists.txt in the project root.

