cmake_minimum_required(VERSION 3.26.3 FATAL_ERROR)
project(project_g LANGUAGES C)

set(SDL_PATH external/SDL2-2.26.5/x86_64-w64-mingw32)
set(LIBRARIES SDL2main SDL2)
set(DEPENDENCIES mingw32)

add_library(engine SHARED)
add_subdirectory(engine)

add_executable(main)
add_subdirectory(game)