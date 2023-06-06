#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "camera.h"

#define window_width 1000
#define window_height 700


int main(int argv, char **args) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("test", 100, 100, window_width, window_height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    struct Camera *camera = Camera_create(120.0, 200.0, 0.0, 0.0, 0.0, 45.0, 0.0, 650.0, window_width, window_height);

    SDL_Event event;
    bool go = true;
    bool update = true;

    const int triangles_count = 1;
    double triangles[triangles_count][9];
    triangles[0][0] = 100;
    triangles[0][1] = 250;
    triangles[0][2] = 100;
    triangles[0][3] = 200;
    triangles[0][4] = 250;
    triangles[0][5] = 100;
    triangles[0][6] = 300;
    triangles[0][7] = 250;
    triangles[0][8] = 150;

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
            Camera_cast(camera, renderer);
            
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            for (int i = 0; i < triangles_count; ++i) {
                for (int j = 0; j < 9; j += 3) {
                    SDL_RenderDrawPoint(renderer, triangles[i][j], window_height - triangles[i][j + 1]);
                }
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            // double **polygons = Camera_projection(camera, triangles_count, triangles);
            // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            // for (int i = 0; i < 3 - 1; ++i) {
            //     SDL_RenderDrawLine(renderer, polygons[i][0], window_height - polygons[i][1], polygons[i + 1][0], window_height - polygons[i + 1][1]);
            // }
            // SDL_RenderDrawLine(renderer, polygons[0][0], window_height - polygons[0][1], polygons[2][0], window_height - polygons[2][1]);
            // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            SDL_RenderPresent(renderer);

            // for (int i = 0; i < 3; ++i) {
            //     free(polygons[i]);
            // }
            // free(polygons);

            update = false;
        }
    }

    free(camera);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
