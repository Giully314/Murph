# Overview
Murph is a game engine written in C++26, based entirely on software rendering. The only third part libraries used are for displaying the buffer
representing the screen and the audio.

# How to build
cmake -B build -S . -GNinja --fresh  
cmake --build build

# How to run tests
ctest --test-dir build