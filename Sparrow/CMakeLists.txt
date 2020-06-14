cmake_minimum_required(VERSION 3.10)
project(Sparrow)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
include_directories(include)
find_package(Threads REQUIRED)

add_executable(Sparrow src/main.cpp)
target_link_libraries(Sparrow ${CONAN_LIBS})