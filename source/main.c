#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "camera.h"

#define window_width 1000
#define window_height 700


int main(int argv, char **args) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("main", 0, 25, window_width, window_height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    struct Camera *camera = Camera_create(10.0, 10.0, 0.0, 30.0, 0.0, 100.0, 200.0, 650.0);

    SDL_Event event;
    bool go = true;
    bool update = true;

    const int triangles_count = 1;
    double *triangles = malloc(triangles_count * 9 * sizeof(double));
    triangles[0] = 100;
    triangles[1] = 250;
    triangles[2] = 0;

    triangles[3] = 200;
    triangles[4] = 250;
    triangles[5] = 0;

    triangles[6] = 300;
    triangles[7] = 250;
    triangles[8] = 100;


    // triangles[9] = 100;
    // triangles[10] = 250;
    // triangles[11] = 0;

    // triangles[12] = 150;
    // triangles[13] = 200;
    // triangles[14] = 250;

    // triangles[15] = 300;
    // triangles[16] = 250;
    // triangles[17] = 100;

    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    while(go) {
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT || keyboardState[SDL_SCANCODE_ESCAPE]) {
                go = false;
            }

            if(event.type == SDL_MOUSEMOTION) {
                Camera_turn(camera, event.motion.xrel, event.motion.yrel);
                update = true;
            }

            if(keyboardState[SDL_SCANCODE_W]) {
                Camera_move_forward(camera);
                update = true;
            }
                            
            if(keyboardState[SDL_SCANCODE_S]) {
                Camera_move_backward(camera);
                update = true;
            }

            if(keyboardState[SDL_SCANCODE_A]) {
                Camera_move_left(camera);
                update = true;
            }

            if(keyboardState[SDL_SCANCODE_D]) {
                Camera_move_right(camera);
                update = true;
            }
        }

        if (update) {
            
            Camera_projection(camera, renderer, window_width, window_height, triangles_count, triangles);

            SDL_RenderPresent(renderer);

            update = false;
        }
    }

    free(triangles);
    free(camera);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
