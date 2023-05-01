@echo off
setlocal

set SDL_PATH=C:/SDL2-2.26.5/x86_64-w64-mingw32

g++ main.cpp block.hpp block.cpp camera.hpp camera.cpp -o main -std=c++23 -Wall -I %SDL_PATH%/include -L %SDL_PATH%/lib -l mingw32 -l SDL2main -l SDL2

endlocal
