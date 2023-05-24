@echo off

rmdir build /q /s
mkdir build

cmake -S source -B build -G "MinGW Makefiles"
cmake --build build --config Release

copy .\build\main.exe .\main.exe

.\main.exe
