cmake_minimum_required(VERSION 3.26.3 FATAL_ERROR)
project(main LANGUAGES C)

set(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
set(SDL_PATH ../external/SDL2-2.26.5/x86_64-w64-mingw32)
set(LIBRARIES SDL2main SDL2)
set(DEPENDENCIES mingw32)

add_library(Engine SHARED)
add_subdirectory(engine)

add_executable(main)
add_subdirectory(game)
