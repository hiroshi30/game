@echo off

rmdir build /q /s
mkdir build

copy SDL2.dll build\SDL2.dll

cmake -S source -B build -G "MinGW Makefiles"
cmake --build build --config Release

.\build\main.exe
