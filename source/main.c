#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "engine.h"
#include "camera.h"

#define window_width 1000
#define window_height 700


int main(int argv, char **args) {

    Engine_init(window_width, window_height);

    struct Camera *camera = Camera_create(10.0, 10.0, 0.0, 30.0, 0.0, 100.0, 200.0, 650.0);

    SDL_Event event;
    bool go = true;
    bool update = true;

    const int triangles_count = 1;
    double triangles[] = {100, 250, 0, 200, 250, 0, 300, 250, 100};
    double *ptr_triangles = triangles;

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
            Camera_projection(camera, triangles_count, ptr_triangles);

            Engine_update();

            update = false;
        }
    }

    free(camera);

    Engine_exit();

    return 0;
}
