@echo off
setlocal

set SDL_PATH=./external/SDL2-2.26.5/x86_64-w64-mingw32

g++ ./source/main.cpp ./source/block.hpp ./source/block.cpp ./source/camera.hpp ./source/camera.cpp -o main -std=c++23 -Wall -Wextra -Wpedantic -I %SDL_PATH%/include -L %SDL_PATH%/lib -l mingw32 -l SDL2main -l SDL2

endlocal
