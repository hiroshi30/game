#include <SDL2/SDL.h>
#include <cstdlib>
#include <cstdio>

#include "block.hpp"
#include "camera.hpp"

const int window_width = 500;
const int window_height = 500;

int[2] ray_casting(int x0, int y0, int angelx) {
    int[2] coords;
    if (anglex > 270 or (angelx > 0 and angelx < 90)) {

    }

    return coords;
} 

int** create_map(int width, int height, int count) {
    int** arr = new int*[height];
    for (int h = 0; h < height; ++h) {
        arr[h] = new int[width];
        for (int w = 0; w < width; ++w) {
            arr[h][w] = 0;
        }
    }

    int x, y;
    for (int i = 0; i < count; ++i) {
        y = std::rand() % height;
        x = std::rand() % width;
        while (arr[y][x] == 1 and i < width * height) {
            y = std::rand() % height;
            x = std::rand() % width;
        }
        arr[y][x] = 1;
    }

    return arr;
}



int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("test", 100, 100, window_width, window_height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int** map = create_map(window_width / block_width, window_height / block_height, 10);
    Camera camera = Camera(window_width / 2, window_height / 2);


    int len = 0;

    printf("{\n");
    for (int h = 0; h < window_height / block_height; ++h) {
        printf("    {");
        for (int w = 0; w < window_width / block_width; ++w) {
            printf("%i, ", map[h][w]);
            if (map[h][w] == 1) len += 1;
        }
        printf("},\n");
    }
    printf("}\n");

    Block arr[len];
    int index = 0;

    for (int h = 0; h < window_height / block_height; ++h) {
        for (int w = 0; w < window_width / block_width; ++w) {
            if (map[h][w] == 1) {
                arr[index] = Block(w * block_width, h * block_height);
                ++index;
            }
        }
    }

    SDL_Event event;
    bool go = true;
    bool update = true;

    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    while(go) {
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT) {
                go = false;
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
            
            for (int i = 0; i < len; ++i) {
                arr[i].draw(renderer);
            }

            camera.draw(renderer);
            camera.draw_line(renderer);

            SDL_RenderPresent(renderer);

            update = false;
            printf("update completes\n");
        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    for (int h = 0; h < window_height / block_height; ++h) {
        delete [] map[h];
    }
    delete [] map;
    map = 0;

    return 0;
}
