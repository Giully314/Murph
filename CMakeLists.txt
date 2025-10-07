cmake_minimum_required(VERSION 4.1)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD d0edc3af-4c50-42ea-a356-e2862fe7a444)

project(Murph LANGUAGES CXX)

set(CMAKE_CXX_MODULE_STD 1)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)


# TODO: set build or release

# TODO: set compiler flags

add_subdirectory(src)


# enable_testing()
# add_subdirectory(tests)

add_executable(main)
target_sources(main PRIVATE main.cpp)
# target_link_libraries(main PRIVATE tars)