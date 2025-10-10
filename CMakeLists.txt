cmake_minimum_required(VERSION 4.1)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD d0edc3af-4c50-42ea-a356-e2862fe7a444)

project(Murph LANGUAGES CXX)

set(CMAKE_CXX_MODULE_STD 1)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)


include(FetchContent)

FetchContent_Declare(
    minifb
    GIT_REPOSITORY https://github.com/emoon/minifb.git
    GIT_TAG master
)

FetchContent_MakeAvailable(minifb)

# TODO: set build or release

# TODO: set compiler flags
# enable_testing()
# add_subdirectory(tests)

add_subdirectory(src)
add_executable(main)
target_sources(main PRIVATE main.cpp)
target_link_libraries(main PRIVATE minifb murph murph_canvas)


