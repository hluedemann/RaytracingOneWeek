cmake_minimum_required(VERSION 3.14)

# Target
add_executable(raytracing
    "main.cpp"
    "vec3.h"
    "ray.h" "ray.cpp")

target_compile_features(raytracing
    PRIVATE
        cxx_std_17)

target_include_directories(raytracing
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src")

# Installation

# install(
#     TARGET raytracing
#     DESTINATION "bin"
# )
