#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

#include "block.hpp"
#include "camera.hpp"
// #include "ray_casting.hpp"

const int window_width = 500;
const int window_height = 500;


int** create_map(int width, int height, int count) {
    int** arr = new int*[count];
    for (int i = 0; i < count; ++i) {
        arr[i] = new int[2];
    }

    int x, y;
    for (int i = 0; i < count; ++i) {
        y = std::rand() % height;
        x = std::rand() % width;
        arr[i][0] = x;
        arr[i][1] = y;
    }

    return arr;
}



int main(int argv, char** args) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("ray_casting", 100, 100, window_width, window_height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    const int count = 10;

    int** map = create_map(window_width / block_width, window_height / block_height, count);
    Camera camera = Camera(window_width / 2, window_height / 2);

    Block blocks[count];
    for (int i = 0; i < count; ++i) {
        blocks[i] = Block(map[i][0] * block_width, map[i][1] * block_height);
    }

    SDL_Event event;
    bool go = true;
    bool update = true;

    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    while(go) {
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT or keyboardState[SDL_SCANCODE_ESCAPE]) {
                go = false;
            }

            if(event.type == SDL_MOUSEMOTION) {
                camera.turn(event.motion.xrel, event.motion.yrel);
                // std::cout << event.motion.xrel << ' ' << event.motion.yrel << std::endl;
                update = true;
            }

            if(keyboardState[SDL_SCANCODE_W]) {
                camera.move_forward();
                update = true;
            }
                            
            if(keyboardState[SDL_SCANCODE_S]) {
                camera.move_backward();
                update = true;
            }

            if(keyboardState[SDL_SCANCODE_A]) {
                camera.move_left();
                update = true;
            }

            if(keyboardState[SDL_SCANCODE_D]) {
                camera.move_right();
                update = true;
            }
        }

        if (update) {
            SDL_RenderClear(renderer);
            
            for (int i = 0; i < count; ++i) {
                blocks[i].draw(renderer);
            }

            camera.draw(renderer);
            double* coords = camera.ray_casting(window_width, window_height);
            camera.draw_line(renderer, coords[0], coords[1]);

            // SDL_Vertex vertices[] = {
            //     {{100, 100}, {255, 0, 0, 255}, {0}},
            //     {{150, 200}, {255, 0, 0, 255}, {0}},
            //     {{200, 100}, {255, 0, 0, 255}, {0}}
            // };

            // SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);

            SDL_RenderPresent(renderer);

            update = false;
        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    for (int i = 0; i < count; ++i) {
        delete [] map[i];
    }
    delete [] map;
    map = 0;

    return 0;
}
