#include <SDL2/SDL.h>
#include <math.h>

#include "engine.h"


double tan_sum(double tan_alpha, double tan_beta) {
	return (tan_alpha + tan_beta) / (1 - tan_alpha / tan_beta);
}

double tan_dif(double tan_alpha, double tan_beta) {
	return (tan_alpha - tan_beta) / (1 + tan_alpha / tan_beta);
}


void Engine_init(int window_width, int window_height) {
    SDL_Init(SDL_INIT_VIDEO);

    WINDOW = SDL_CreateWindow("main", 0, 25, window_width, window_height, SDL_WINDOW_SHOWN);
    RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    WINDOW_WIDTH = window_width;
    WINDOW_HEIGHT = window_height;
}

void Engine_update(void) {
	SDL_RenderPresent(RENDERER);
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