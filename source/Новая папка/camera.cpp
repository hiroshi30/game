#include <SDL2/SDL.h>
#include <cmath>

#define pi 3.14159265

#include "camera.hpp"
#include "block.hpp"

Camera::Camera(double set_x, double set_y) {
	x = set_x;
	y = set_y;
	radius = 200;
	angle_x = 90;
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
    double draw_radius = 5;
	for (int iy = y - draw_radius; iy <= y + draw_radius; ++iy) {
		for (int ix = x - draw_radius; ix <= x + draw_radius; ++ix) {
    		if ((ix - x) * (ix - x) + (iy - y) * (iy - y) <= draw_radius * draw_radius) {
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

double* Camera::ray_casting() {
	static double coords[2];
	double k = std::tan(pi * angle_x / 180);
	double l = y - k * x;
	double a = k * k + 1;
	double b = -2 * x + 2 * k * l - 2 * k * y;
	double c = x*x + l*l + y*y - 2 * l *y - radius*radius;
	double D = b*b - 4 * a * c;
	if (angle_x >= 90 && angle_x <= 270) {
		coords[0] = (-b + std::sqrt(D)) / (2 * a);
	} else {
		coords[0] = (-b - std::sqrt(D)) / (2 * a);
	}
    coords[1] = k * coords[0] + l;

    return coords;
}

double* Camera::ray_casting0(Block blocks[]) {
	static double coords[2];
	double k = std::tan(pi * angle_x / 180);
	double l = y - k * x;
	double a = k * k + 1;
	double b = -2 * x + 2 * k * l - 2 * k * y;
	double c = x*x + l*l + y*y - 2 * l *y - radius*radius;
	double D = b*b - 4 * a * c;
	if (angle_x >= 90 && angle_x <= 270) {
		coords[0] = (-b + std::sqrt(D)) / (2 * a);
	} else {
		coords[0] = (-b - std::sqrt(D)) / (2 * a);
	}
    coords[1] = k * coords[0] + l;

    for (int i = 0; i < sizeof(blocks) / sizeof(blocks[0]); ++i) {
    	
    }

    return coords;
}