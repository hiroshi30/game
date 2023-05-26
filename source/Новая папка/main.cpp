#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

#include "block.hpp"
#include "camera.hpp"

#define window_width 500
#define window_height 500


int main(int argv, char** args) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("ray_casting", 100, 100, window_width, window_height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    const int count = 10;

    Camera camera = Camera(window_width / 2, window_height / 2);
    Block blocks[count];

    for (int i = 0; i < count; ++i) {
        int x = std::rand() % window_width / block_width;
        int y = std::rand() % window_height / block_height;
        blocks[i] = Block(x * block_width, y * block_height);
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
            double* coords = camera.ray_casting();
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

    return 0;
}
