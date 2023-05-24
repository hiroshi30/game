#include <SDL2/SDL.h>
#include <cmath>

#define pi 3.14159265

#include "camera.hpp"

Camera::Camera(int setX, int setY) {
	x = setX;
	y = setY;
	radius = 5;
	angle_x = 45;
	angle_y = 0;
	speed = 5;
};

void Camera::move_forward() {
	x -= speed * std::cos(pi * angle_x / 180);
	y -= speed * std::sin(pi * angle_x / 180);
}

void Camera::move_backward() {
	x += speed * std::cos(pi * angle_x / 180);
	y += speed * std::sin(pi * angle_x / 180);
}

void Camera::move_right() {
	x -= speed * std::cos(pi * (angle_x + 90) / 180);
	y -= speed * std::sin(pi * (angle_x + 90) / 180);
}

void Camera::move_left() {
	x += speed * std::cos(pi * (angle_x + 90) / 180);
	y += speed * std::sin(pi * (angle_x + 90) / 180);
}

void Camera::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (int iy = y - radius; iy <= y + radius; ++iy) {
		for (int ix = x - radius; ix <= x + radius; ++ix) {
    		if ((ix - x) * (ix - x) + (iy - y) * (iy - y) <= radius * radius) {
    			SDL_RenderDrawPoint(renderer, int(ix), int(iy));
    		}
    	}
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Camera::draw_line(SDL_Renderer *renderer, double x1, double y1) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, int(x), int(y), int(x1), int(y1));
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Camera::turn(double x1, double y1) {
	angle_x += x1;
	while (angle_x < 0) angle_x += 360;
	while (angle_x >= 360) angle_x -= 360;
	angle_y += y1;
	while (angle_y < 0) angle_y += 360;
	while (angle_y >= 360) angle_y -= 360;
}

double* Camera::ray_casting(int width, int height) {
	static double coords[2];
    if (angle_x > 0 and angle_x < 180) {
        coords[1] = 0;
        coords[0] = (coords[1] - y) / std::tan(pi * angle_x / 180) + x;
    } else if (angle_x > 180 and angle_x < 360) {
        coords[1] = height;
        coords[0] = (coords[1] - y) / std::tan(pi * angle_x / 180) + x;
    } else if (angle_x == 0) {
    	coords[1] = y;
    	coords[0] = 0;
    } else if (angle_x == 180) {
    	coords[1] = y;
    	coords[0] = width;
    }

    return coords;
}
