#include "engine2d.h"


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

bool Engine_event_exit(SDL_Event event) {
    if(event.type == SDL_QUIT || KEYBOARD_STATE[SDL_SCANCODE_ESCAPE]) {
        return false;
    }
    return true;
}

void Engine_exit(void) {
	SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();
}


void fill(int r, int g, int b) {
	SDL_SetRenderDrawColor(RENDERER, r, g, b, 255);
	SDL_RenderClear(RENDERER);
}

void draw_circle(double x, double y, double radius, int r, int g, int b) {
    SDL_SetRenderDrawColor(RENDERER, r, g, b, 255);
	for (int i = y - radius; i <= y + radius; ++i) {
		for (int j = x - radius; j <= x + radius; ++j) {
    		if ((j - x) * (j - x) + (i - y) * (i - y) <= radius * radius) {
    			SDL_RenderDrawPoint(RENDERER, j, WINDOW_HEIGHT - i);
    		}
    	}
    }
}

void draw_line(double x1, double y1, double x2, double y2, int r, int g, int b) {
    SDL_SetRenderDrawColor(RENDERER, r, g, b, 255);
    SDL_RenderDrawLine(RENDERER, x1, WINDOW_HEIGHT - y1, x2, WINDOW_HEIGHT - y2);
}

void draw_line_math(double k, double l, int r, int g, int b) {
    for (int x = 0; x < WINDOW_WIDTH; ++x) {
        double y = k * x + l;
        if (y >= 0 && y < WINDOW_HEIGHT) {
            draw_line(x, y, r, g, b);
        } else if (y >= WINDOW_HEIGHT) {
            break;
        }
    }
}

void draw_polygon(int count, double **coords, int r, int g, int b) {
    SDL_Vertex polygon[count];
    for (int i = 0; i < count; ++i) {
        polygon[i] = (SDL_Vertex){{coords[i][0], coords[i][1]}, {r, g, b, 255}, {0, 0}};
    }
    SDL_RenderGeometry(RENDERER, NULL, polygon, 3, NULL, 0);
}