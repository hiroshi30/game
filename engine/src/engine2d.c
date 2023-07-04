#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "engine2d.h"


int WINDOW_WIDTH;
int WINDOW_HEIGHT;
SDL_Window *WINDOW;
SDL_Renderer *RENDERER;
SDL_Event EVENT;
const Uint8 *KEYBOARD_STATE;
int R = 0, G = 0, B = 0, A = 255;


void Engine_init(int window_width, int window_height) {
    SDL_Init(SDL_INIT_VIDEO);

    WINDOW = SDL_CreateWindow("main", 0, 25, window_width, window_height, SDL_WINDOW_SHOWN);
    RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    WINDOW_WIDTH = window_width;
    WINDOW_HEIGHT = window_height;
}

void Engine_keyboard_init(void) {
    KEYBOARD_STATE = SDL_GetKeyboardState(NULL);
}

void Engine_mouse_init(void) {
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Engine_update(void) {
	SDL_RenderPresent(RENDERER);
}

bool Engine_event_status(void) {
    if (SDL_PollEvent(&EVENT) != 0) {
        return true;
    }
    return false;
}

bool Engine_event_exit() {
    if(EVENT.type == SDL_QUIT || KEYBOARD_STATE[SDL_SCANCODE_ESCAPE]) {
        return false;
    }
    return true;
}

void Engine_exit(void) {
	SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();
}


void set_color(int r, int g, int b) {
    R = r;
    G = g;
    B = b;
    SDL_SetRenderDrawColor(RENDERER, r, g, b, 255);
}

void fill(void) {
	SDL_RenderClear(RENDERER);
}

void draw_circle(double x, double y, double radius) {
	for (int i = y - radius; i <= y + radius; ++i) {
		for (int j = x - radius; j <= x + radius; ++j) {
    		if ((j - x) * (j - x) + (i - y) * (i - y) <= radius * radius) {
    			SDL_RenderDrawPoint(RENDERER, j, WINDOW_HEIGHT - i);
    		}
    	}
    }
}

void draw_line(double x1, double y1, double x2, double y2) {
    SDL_RenderDrawLine(RENDERER, x1, WINDOW_HEIGHT - y1, x2, WINDOW_HEIGHT - y2);
}

void draw_line_alpha(double k, double b) {
    if (k >= tan(PI * 90 / 180)) {
        draw_line(-b / k, 0, -b / k, WINDOW_HEIGHT);
    } else {
        draw_line(0, b, WINDOW_WIDTH, k * WINDOW_WIDTH + b);
    }
}

void draw_polygon(int count, Vector4f *vect) {
    SDL_Vertex polygon[count];
    for (int i = 0; i < count; ++i) {
        polygon[i] = (SDL_Vertex){{vect[i].x, WINDOW_HEIGHT - vect[i].y}, {R, G, B, A}, {0, 0}};
    }
    SDL_RenderGeometry(RENDERER, NULL, polygon, count, NULL, 0);
}
