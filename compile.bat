@echo off

g++ sdl.cpp -o main -std=c++23 -I C:\SDL2-2.26.5\x86_64-w64-mingw32\include -L C:\SDL2-2.26.5\x86_64-w64-mingw32\lib -l SDL2main -l SDL2