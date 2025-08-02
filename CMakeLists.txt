cmake_minimum_required(VERSION 3.16)
project(AlgorithmVisualizer LANGUAGES CXX) # Project name is AlgorithmVisualizer, but your executable is 'main'

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS Graphics Window System REQUIRED) # Use capitalized components as per SFML standard

set(APP_NAME "main")

add_executable(${APP_NAME}
    core/main.cpp
    core/visualizer/VisualizeEngine.cpp
    # (I’ll add more .cpp/ as I go)
)

target_include_directories(${APP_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${APP_NAME} PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
