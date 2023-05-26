#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "camera.h"

#define window_width 500
#define window_height 500


int main(int argv, char** args) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("ray_casting", 100, 100, window_width, window_height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // const int count = 10;

    struct Camera *camera = &(struct Camera) {
        .view_angle=120,
        .x0=(double)(window_width / 2),
        .y0=(double)(window_height / 2),
        .x=(double)(window_width / 2),
        .y=(double)(window_height / 2),
        .angle_x=0.0,
        .angle_y=0.0,
        .speed=4.0,
        .radius=200.0
    };

    camera->z0 = -ctan(camera->view_angle / 2) * window_width / 2;

    SDL_Event event;
    bool go = true;
    bool update = true;

    int verticies[3][2] = {{0, 0}, {100, 0}, {50, 50}};

    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    // SDL_SetRelativeMouseMode(SDL_TRUE);

    while(go) {
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT || keyboardState[SDL_SCANCODE_ESCAPE]) {
                go = false;
                update = false;
            }

            if(event.type == SDL_MOUSEMOTION) {
                turn(camera, event.motion.xrel, event.motion.yrel);
                update = true;
            }

            if(keyboardState[SDL_SCANCODE_W]) {
                move_forward(camera);
                update = true;
            }
                            
            if(keyboardState[SDL_SCANCODE_S]) {
                move_backward(camera);
                update = true;
            }

            if(keyboardState[SDL_SCANCODE_A]) {
                move_left(camera);
                update = true;
            }

            if(keyboardState[SDL_SCANCODE_D]) {
                move_right(camera);
                update = true;
            }
        }

        if (update) {
            SDL_RenderClear(renderer);
        
            draw(renderer, camera);
            double *coords = ray_casting(camera);
            draw_line(renderer, camera, coords[0], coords[1]);

            SDL_RenderPresent(renderer);

            update = false;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
