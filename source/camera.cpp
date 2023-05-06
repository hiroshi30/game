#include <SDL2/SDL.h>

#include "camera.hpp"

Camera::Camera(int setX, int setY) {
	x = setX;
	y = setY;
	radius = 5;
	angelx = 0;
	angely = 0;
	speed_x = 5;
	speed_y = 5;
};

void Camera::move_forward() {
	y -= speed_y;
}

void Camera::move_backward() {
	y += speed_y;
}

void Camera::move_right() {
	x += speed_x;
}

void Camera::move_left() {
	x -= speed_x;
}

const void Camera::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (int iy = y - radius; iy <= y + radius; ++iy) {
		for (int ix = x - radius; ix <= x + radius; ++ix) {
    		if ((ix - x) * (ix - x) + (iy - y) * (iy - y) <= radius * radius) {
    			SDL_RenderDrawPoint(renderer, ix, iy);}
    	}
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

const void Camera::draw_line(SDL_Renderer *renderer, int x2, int y2) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, x, y, 0, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
