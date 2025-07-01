cmake_minimum_required(VERSION 3.15)
project(MiniEngine)

set(CMAKE_CXX_STANDARD 17)

# Add libraries
add_subdirectory(libs/glfw)

include_directories(
    libs/glad/include
    libs/glfw/include
    libs/glm
    libs/SimpleIni
)

# Source files

add_executable(MiniEngine
    src/main.cpp
    src/core/InputManager.cpp
    src/graphics/Shader.cpp
    src/graphics/Camera.cpp
    src/core/config/Config.cpp
    src/core/config/EngineSettings.cpp
    libs/glad/src/glad.c
)

# Link libraries
target_link_libraries(MiniEngine PRIVATE glfw)