@echo off
setlocal

set SDL_PATH=./external/SDL2-2.26.5/x86_64-w64-mingw32

gcc ./source/camera.h ./source/main.c ./source/camera.c -o main -std=c2x -Wall -Wextra -Wpedantic -I %SDL_PATH%/include -L %SDL_PATH%/lib -l mingw32 -l SDL2main -l SDL2

endlocal
