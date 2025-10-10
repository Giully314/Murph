Murph is a game engine based entirely on software without hardware acceleration.

# How to build
cmake -B build -S . -GNinja --fresh -DCMAKE_TOOLCHAIN_FILE=cmake/homebrew.cmake (if on macos and want to use homebrew clang).  
cmake --build build

# How to run tests
ctest --test-dir build