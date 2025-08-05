cmake_minimum_required(VERSION 3.16)
project(AlgorithmVisualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(APP_NAME "main")

add_executable(${APP_NAME}
    core/main.cpp
    core/visualizer/VisualizeEngine.cpp
    algorithms/sorting/BubbleSortVisualizer.cpp
    sfml_ui/UI.cpp
    # (I’ll add more .cpp/ as I go)
)

target_include_directories(${APP_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/algorithms
)

target_link_libraries(${APP_NAME} PRIVATE
    sfml-graphics sfml-window sfml-system
)
