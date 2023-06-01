#include <stdbool.h>

#include "camera.h"


int main(int argv, char** args) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("ray_casting", 100, 100, window_width, window_height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    struct Camera *camera = create_camera();

    // struct Camera camera = {
    //     .view_angle=120.0,
    //     .draw_radius=5.0,
    //     .x=0.0,
    //     .y=0.0,
    //     .z=0.0,
    //     .angle_x=45.0,
    //     .angle_y=0.0,
    //     .speed=500.0,
    //     .radius=200.0
    // };

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
                turn(camera, event.motion.xrel, event.motion.yrel);
                update = true;
                // printf("angle_x %f, angle_y %f\n", camera->angle_x, camera->angle_y);
            }

            if(keyboardState[SDL_SCANCODE_W]) {
                move_forward(camera);
                update = true;
                // printf("x %f, y %f\n", camera->x, camera->y);
            }
                            
            if(keyboardState[SDL_SCANCODE_S]) {
                move_backward(camera);
                update = true;
                // printf("x %f, y %f\n", camera->x, camera->y);
            }

            if(keyboardState[SDL_SCANCODE_A]) {
                move_left(camera);
                update = true;
                // printf("x %f, y %f\n", camera->x, camera->y);
            }

            if(keyboardState[SDL_SCANCODE_D]) {
                move_right(camera);
                update = true;
                // printf("x %f, y %f\n", camera->x, camera->y);
            }
        }

        if (update) {
            SDL_RenderClear(renderer);
        
            draw(camera, renderer);
            double *coords = ray_casting(camera);
            draw_line(camera, renderer, coords[0], coords[1]);

            SDL_RenderPresent(renderer);

            update = false;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
