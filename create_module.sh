#!/usr/bin/env bash


MODULE_NAME="$1"
mkdir -p src/${MODULE_NAME}/src
mkdir -p src/${MODULE_NAME}/include/${MODULE_NAME}
cp src/gpio/CMakeLists.txt src/${MODULE_NAME}/

echo "Note: Add \"add_subdirectory(src/${MODULE_NAME})\" to CMakeLists.txt"
