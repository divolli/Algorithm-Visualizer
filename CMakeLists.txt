cmake_minimum_required(VERSION 3.16)
project(AlgorithmVisualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Where your source files live
add_executable(algorithm_visualizer
    core/main.cpp
    # (I’ll add more .cpp/.hpp as I go)
)

# Link SFML libraries
target_link_libraries(algorithm_visualizer
    PRIVATE sfml-graphics sfml-window sfml-system
)
