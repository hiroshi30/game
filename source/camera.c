#include <SDL2/SDL.h>
#include <math.h>

#include "camera.h"


void move_forward(struct Camera *camera) {
	camera->x += camera->speed * cos(pi * camera->angle_x / 180);
	camera->y += camera->speed * sin(pi * camera->angle_x / 180);
}

void move_backward(struct Camera *camera) {
	camera->x -= camera->speed * cos(pi * camera->angle_x / 180);
	camera->y -= camera->speed * sin(pi * camera->angle_x / 180);
}

void move_right(struct Camera *camera) {
	camera->x -= camera->speed * cos(pi * (camera->angle_x + 90) / 180);
	camera->y -= camera->speed * sin(pi * (camera->angle_x + 90) / 180);
}

void move_left(struct Camera *camera) {
	camera->x += camera->speed * cos(pi * (camera->angle_x + 90) / 180);
	camera->y += camera->speed * sin(pi * (camera->angle_x + 90) / 180);
}

void draw(SDL_Renderer *renderer, struct Camera *camera) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (int iy = camera->y - camera->draw_radius; iy <= camera->y + camera->draw_radius; ++iy) {
		for (int ix = camera->x - camera->draw_radius; ix <= camera->x + camera->draw_radius; ++ix) {
    		if ((ix - camera->x) * (ix - camera->x) + (iy - camera->y) * (iy - camera->y) <= camera->draw_radius * camera->draw_radius) {
    			SDL_RenderDrawPoint(renderer, ix, window_height - iy);
    		}
    	}
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void draw_line(SDL_Renderer *renderer, struct Camera *camera, double x1, double y1) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, camera->x, window_height - camera->y, x1, window_height - y1);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void turn(struct Camera *camera, double x1, double y1) {
	camera->angle_x -= x1;
	while (camera->angle_x < 0) camera->angle_x += 360;
	while (camera->angle_x >= 360) camera->angle_x -= 360;
	camera->angle_y -= y1;
	while (camera->angle_y < 0) camera->angle_y += 360;
	while (camera->angle_y >= 360) camera->angle_y -= 360;
}

double* ray_casting(struct Camera *camera) {
	static double coords[2];
	double k = tan(pi * camera->angle_x / 180);
	double l = camera->y - k * camera->x;
	double a = k * k + 1;
	double b = -2 * camera->x + 2 * k * l - 2 * k * camera->y;
	double c = camera->x*camera->x + l*l + camera->y*camera->y - 2 * l * camera->y - camera->radius*camera->radius;
	double D = b*b - 4 * a * c;
	
	if (camera->angle_x == 90) {
		coords[0] = camera->x;
		coords[1] = camera->y + camera->radius;
	} else if (camera->angle_x == 270) {
		coords[0] = camera->x;
		coords[1] = camera->y - camera->radius;
	} else if (camera->angle_x > 90 && camera->angle_x < 270) {
		coords[0] = (-b - sqrt(D)) / (2 * a);
    	coords[1] = k * coords[0] + l;
	} else {
		coords[0] = (-b + sqrt(D)) / (2 * a);
    	coords[1] = k * coords[0] + l;
	}

    return coords;
}

double** vertex(struct Camera *camera, double vertices[][3]) {
	static double *new_vertices[sizeof(vertices) / sizeof(vertices[0])];
	for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); ++i) {
		double camera_height = tan(pi / 2 - pi * (camera->view_angle / 2) / 180) * window_width / 2;
		double height = vertices[i][2] - camera->z0;vertices;
		double length = sqrt((camera->x0 - vertices[i][0])*(camera->x0 - vertices[i][0]) + (camera->y0 - vertices[i][1])*(camera->y0 - vertices[i][1]) + (camera->z0 - vertices[i][2])*(camera->z0 - vertices[i][2]));
		double new_length = -camera->z0 / height * length;

		// ax + by + c = z
		

		new_vertices[i] = {0, 0, 0};
		
	}
	return new_vertices;
}
