cmake_minimum_required(VERSION 3.15)
project(MiniEngine)

set(CMAKE_CXX_STANDARD 17)

# Add libraries
add_subdirectory(libs/glfw)

include_directories(
    libs/glad/include
    libs/glfw/include
    libs/glm
)

# Source files

add_executable(MiniEngine
    src/main.cpp
    src/core/InputManager.cpp
    src/graphics/Shader.cpp
    libs/glad/src/glad.c
    src/graphics/Camera.cpp
)

# Link libraries
target_link_libraries(MiniEngine glfw)