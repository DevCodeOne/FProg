project(FPROG C CXX)

cmake_minimum_required(VERSION 3.6.2)
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(EXECUTABLE_OUTPUT_PATH build)
# Kompiliere mit Standard 17
add_definitions(-std=c++14)

include_directories("src/testing/")
file(GLOB SOURCES_TESTING "src/testing/*cpp")
add_executable(testing_exe ${SOURCES_TESTING})

include_directories("src/day_one/")
file(GLOB SOURCES_DAY_ONE "src/day_one/*cpp")
add_executable(day_one_exe ${SOURCES_DAY_ONE})

include_directories("src/day_two/")
file(GLOB SOURCES_DAY_TWO "src/day_two/*cpp")
add_executable(day_two_exe ${SOURCES_DAY_TWO})

include_directories("src/day_three/")
file(GLOB SOURCES_DAY_THREE "src/day_three/*cpp")
add_executable(day_three_exe ${SOURCES_DAY_THREE})
