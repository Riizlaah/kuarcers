cmake_minimum_required(VERSION 3.10)
project(Kuarcers)

set(CMAKE_C_STANDARD 99)

# Atur output ke folder bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Cari library Raylib
find_package(raylib REQUIRED)

# Kumpulkan semua file sumber dari folder src/
file(GLOB SOURCES "src/*.c")

# Buat executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Tautkan Raylib
target_link_libraries(${PROJECT_NAME} raylib m)