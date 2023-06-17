cmake_minimum_required(VERSION 3.26.3 FATAL_ERROR)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Release")

set(SDL_PATH ../external/SDL2-2.26.5/x86_64-w64-mingw32)
set(PROJECT_NAME main)

add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(${SDL_PATH}/include)
link_directories(${SDL_PATH}/lib)

set(LIBRARIES SDL2main SDL2)
set(DEPENDENCIES mingw32)

project(${PROJECT_NAME} LANGUAGES C)

add_executable(${PROJECT_NAME} main.c camera.h camera.c engine.h engine.c)

target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES} ${LIBRARIES})
