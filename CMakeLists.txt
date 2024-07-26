cmake_minimum_required(VERSION 3.10)
project(PongRaylibC)

# Set the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Find the Raylib include path
find_path(RL_INCLUDE_DIR raylib.h /opt/homebrew/opt/raylib/include)
include_directories(${RL_INCLUDE_DIR})

# Find the Raylib library
find_library(RL_LIBRARY raylib /opt/homebrew/opt/raylib/lib)

# Add your source files
add_executable(${PROJECT_NAME} main.c)  # Replace 'main.c' with your source files

# Link Raylib to your project
target_link_libraries(${PROJECT_NAME} ${RL_LIBRARY})
