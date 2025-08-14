cmake_minimum_required(VERSION 3.16)
project(AlgorithmVisualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(APP_NAME "jj")

add_executable(${APP_NAME}
    src/main.cpp
    src/HelperParser/ParserInput.cpp
    src/Algorithms/SortingAlgorithms.cpp
    # (I’ll add more .cpp/ as I go)
)

target_link_libraries(${APP_NAME} PRIVATE
    sfml-graphics sfml-window sfml-system
)
