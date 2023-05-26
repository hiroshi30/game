#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

const int window_width = 500;
const int window_height = 500;




int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("ray_casting", 100, 100, window_width, window_height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Event event;
    bool go = true;
    bool update = true;

    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    static int x = window_width / 2;
    static int y = window_height / 2;

    while(go) {
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT or keyboardState[SDL_SCANCODE_ESCAPE]) {
                go = false;
            }

            if(event.type == SDL_MOUSEMOTION) {
                x += event.motion.xrel;
                y += event.motion.yrel;
                // std::cout << x << ' ' << y << std::endl;
                update = true;
            }
        }

        if (update) {
            SDL_RenderClear(renderer);

            SDL_Vertex vertices[] = {
                {{100, 100}, {255, 0, 0, 255}, {0}},
                {{150, 200}, {255, 0, 0, 255}, {0}},
                {{200, 100}, {255, 0, 0, 255}, {0}}
            };

            SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawPoint(renderer, x, y);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            
            update = false;

            SDL_RenderPresent(renderer);
        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
