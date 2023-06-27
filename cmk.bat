@echo off

rmdir build /q /s
mkdir build

cmake -S . -B build -G "MinGW Makefiles"
cmake --build build --config Release

copy external\SDL2-2.26.5\x86_64-w64-mingw32\bin\SDL2.dll SDL2.dll
copy build\libEngine.dll libEngine.dll
copy build\main.exe main.exe
