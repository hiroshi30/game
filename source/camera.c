#include <SDL2/SDL.h>
#include <math.h>

#define pi 3.14159265

#include "camera.h"

void move_forward(struct Camera *camera) {
	camera->x -= camera->speed * cos(pi * camera->angle_x / 180);
	camera->y -= camera->speed * sin(pi * camera->angle_x / 180);
}

void move_backward(struct Camera *camera) {
	camera->x += camera->speed * cos(pi * camera->angle_x / 180);
	camera->y += camera->speed * sin(pi * camera->angle_x / 180);
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
    double draw_radius = 5;
	for (int iy = camera->y - draw_radius; iy <= camera->y + draw_radius; ++iy) {
		for (int ix = camera->x - draw_radius; ix <= camera->x + draw_radius; ++ix) {
    		if ((ix - camera->x) * (ix - camera->x) + (iy - camera->y) * (iy - camera->y) <= draw_radius * draw_radius) {
    			SDL_RenderDrawPoint(renderer, ix, iy);
    		}
    	}
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void draw_line(SDL_Renderer *renderer, struct Camera *camera, double x1, double y1) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, camera->x, camera->y, x1, y1);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void turn(struct Camera *camera, double x1, double y1) {
	camera->angle_x += x1;
	while (camera->angle_x < 0) camera->angle_x += 360;
	while (camera->angle_x >= 360) camera->angle_x -= 360;
	camera->angle_y += y1;
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
		coords[1] = camera->y - camera->radius;
	} else if (camera->angle_x == 270) {
		coords[0] = camera->x;
		coords[1] = camera->y + camera->radius;
	} else if (camera->angle_x > 90 && camera->angle_x < 270) {
		coords[0] = (-b + sqrt(D)) / (2 * a);
    	coords[1] = k * coords[0] + l;
	} else {
		coords[0] = (-b - sqrt(D)) / (2 * a);
    	coords[1] = k * coords[0] + l;
	}

    return coords;
}

double** vertex(double[][3] verticies) {
	double **new_verticies[sizeof(verticies) / sizeof(verticies[0])];
	for (int i = 0; i < sizeof(verticies) / sizeof(verticies[0]); ++i) {
		double height = verticies[i][2] - camera->z0;
		double length = sqrt((camera->x0 - verticies[i][0])*(camera->x0 - verticies[i][0]) + (camera->y0 - verticies[i][1])*(camera->y0 - verticies[i][1]) + (camera->z0 - verticies[i][2])*(camera->z0 - verticies[i][2]));
		double new_length = -camera->z0 / height * length;

		// ax + by + c = z
		

		new_verticies[i] = {0, 0, 0};
		
	}
	return new_verticies;
}

// double* Camera::ray_casting0(Block blocks[]) {
// 	static double coords[2];
// 	double k = tan(pi * angle_x / 180);
// 	double l = y - k * x;
// 	double a = k * k + 1;
// 	double b = -2 * x + 2 * k * l - 2 * k * y;
// 	double c = x*x + l*l + y*y - 2 * l *y - radius*radius;
// 	double D = b*b - 4 * a * c;
// 	if (angle_x >= 90 && angle_x <= 270) {
// 		coords[0] = (-b + sqrt(D)) / (2 * a);
// 	} else {
// 		coords[0] = (-b - sqrt(D)) / (2 * a);
// 	}
//     coords[1] = k * coords[0] + l;

//     for (int i = 0; i < sizeof(blocks) / sizeof(blocks[0]); ++i) {
    	
//     }

//     return coords;
// }
