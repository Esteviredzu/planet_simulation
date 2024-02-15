cmake_minimum_required(VERSION 3.10)
project(planets)

set(CMAKE_CXX_STANDARD 14)
include_directories(${CMAKE_SOURCE_DIR}/../SFML/include)
link_directories(${CMAKE_SOURCE_DIR}/../SFML/lib)

include_directories(../include)
file(GLOB SOURCES ../src/*.cpp)

add_executable(planets ${SOURCES})
target_link_libraries(planets sfml-graphics sfml-window sfml-system sfml-audio)
