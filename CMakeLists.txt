cmake_minimum_required(VERSION 3.23)

project(LearnC)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/cglm)
include_directories(vendor/glad/include)

file(GLOB SRC
    "src/**/**/*.c"
    "src/**/*.c"
    "src/*.c"
)

add_executable(LearnC
    ${SRC}
    vendor/glad/src/glad.c
)

# OpenGL
find_package(OpenGL REQUIRED)

target_link_libraries(LearnC PUBLIC glfw opengl32 cglm)