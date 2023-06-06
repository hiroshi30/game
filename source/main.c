#include <stdbool.h>

#include "camera.h"


int main(int argv, char** args) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("ray_casting", 100, 100, window_width, window_height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    struct Camera *camera = Camera_create(120.0, 200.0, 0.0, 0.0, 0.0, 45.0, 0.0, 650.0);

    SDL_Event event;
    bool go = true;
    bool update = true;

    int vertices[3][3] = {{0, 50, 0}, {100, 50, 0}, {50, 50, 50}};

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
                // printf("angle_x %f, angle_y %f\n", camera->angle_x, camera->angle_y);
            }

            if(keyboardState[SDL_SCANCODE_W]) {
                Camera_move_forward(camera);
                update = true;
                // printf("x %f, y %f\n", camera->x, camera->y);
            }
                            
            if(keyboardState[SDL_SCANCODE_S]) {
                Camera_move_backward(camera);
                update = true;
                // printf("x %f, y %f\n", camera->x, camera->y);
            }

            if(keyboardState[SDL_SCANCODE_A]) {
                Camera_move_left(camera);
                update = true;
                // printf("x %f, y %f\n", camera->x, camera->y);
            }

            if(keyboardState[SDL_SCANCODE_D]) {
                Camera_move_right(camera);
                update = true;
                // printf("x %f, y %f\n", camera->x, camera->y);
            }
        }

        if (update) {
            SDL_RenderClear(renderer);
        
            Camera_draw(camera, renderer);
            double *coords = Camera_ray_casting(camera);
            Camera_draw_line(camera, renderer, coords[0], coords[1]);

            SDL_RenderPresent(renderer);

            update = false;
        }
    }

    free(camera);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
