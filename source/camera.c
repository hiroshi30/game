#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "camera.h"

#define MAX_THRESHOLD 0.01
#define PI 3.14159265
#define DEG_TO_RAD PI / 180


struct Camera *Camera_create(double x, double y, double z, double angle_x, double angle_y, double view_angle, double view_radius, double radius, double speed) {
	struct Camera *camera = (struct Camera *)malloc(sizeof(struct Camera));

    camera->x = x;
    camera->y = y;
    camera->z = z;
    camera->angle_x = angle_x;
    camera->angle_y = angle_y;
	camera->view_angle = view_angle;
	camera->view_radius = view_radius;
    camera->radius = radius;
    camera->speed = speed;
    camera->time1 = (struct timeval *)malloc(sizeof(struct timeval));
    camera->time2 = (struct timeval *)malloc(sizeof(struct timeval));
    camera->window_width = sqrt(2 * radius * radius * (1 - cos(DEG_TO_RAD * (360 - 2 * view_angle))));
    camera->window_height = camera->window_width;
	camera->camera_height = camera->window_width / 2 * tan(PI / 2 - DEG_TO_RAD * (camera->view_angle / 2));

	mingw_gettimeofday(camera->time1, NULL);
	return camera;
}

void Camera_move_forward(struct Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x += camera->speed * cos(DEG_TO_RAD * camera->angle_x) * delta_time;
		camera->y += camera->speed * sin(DEG_TO_RAD * camera->angle_x) * delta_time;
	} else {
		camera->x += camera->speed * cos(DEG_TO_RAD * camera->angle_x) * MAX_THRESHOLD;
		camera->y += camera->speed * sin(DEG_TO_RAD * camera->angle_x) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
}

void Camera_move_backward(struct Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x -= camera->speed * cos(DEG_TO_RAD * camera->angle_x) * delta_time;
		camera->y -= camera->speed * sin(DEG_TO_RAD * camera->angle_x) * delta_time;
	} else {
		camera->x -= camera->speed * cos(DEG_TO_RAD * camera->angle_x) * MAX_THRESHOLD;
		camera->y -= camera->speed * sin(DEG_TO_RAD * camera->angle_x) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
}

void Camera_move_right(struct Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x -= camera->speed * cos(DEG_TO_RAD * (camera->angle_x + 90)) * delta_time;
		camera->y -= camera->speed * sin(DEG_TO_RAD * (camera->angle_x + 90)) * delta_time;
	} else {
		camera->x -= camera->speed * cos(DEG_TO_RAD * (camera->angle_x + 90)) * MAX_THRESHOLD;
		camera->y -= camera->speed * sin(DEG_TO_RAD * (camera->angle_x + 90)) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
}

void Camera_move_left(struct Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x += camera->speed * cos(DEG_TO_RAD * (camera->angle_x + 90)) * delta_time;
		camera->y += camera->speed * sin(DEG_TO_RAD * (camera->angle_x + 90)) * delta_time;
	} else {
		camera->x += camera->speed * cos(DEG_TO_RAD * (camera->angle_x + 90)) * MAX_THRESHOLD;
		camera->y += camera->speed * sin(DEG_TO_RAD * (camera->angle_x + 90)) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
}

void Camera_turn(struct Camera *camera, double x1, double y1) {
	camera->angle_x -= x1;
	while (camera->angle_x < 0) camera->angle_x += 360;
	while (camera->angle_x >= 360) camera->angle_x -= 360;
	camera->angle_y -= y1;
	while (camera->angle_y < 0) camera->angle_y += 360;
	while (camera->angle_y >= 360) camera->angle_y -= 360;
}

void Camera_draw(struct Camera *camera, SDL_Renderer *renderer, int window_height) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (int iy = camera->y - camera->radius; iy <= camera->y + camera->radius; ++iy) {
		for (int ix = camera->x - camera->radius; ix <= camera->x + camera->radius; ++ix) {
    		if ((ix - camera->x) * (ix - camera->x) + (iy - camera->y) * (iy - camera->y) <= camera->radius * camera->radius) {
    			SDL_RenderDrawPoint(renderer, ix, window_height - iy);
    		}
    	}
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Camera_draw_line(struct Camera *camera, SDL_Renderer *renderer, int window_height, double x1, double y1) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, camera->x, window_height - camera->y, x1, window_height - y1);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Camera_cast(struct Camera *camera, SDL_Renderer *renderer, int window_height) {
	double k = tan(DEG_TO_RAD * camera->angle_x);
	double l = camera->y - k * camera->x;
	double a = k * k + 1;
	double b = -2 * camera->x + 2 * k * l - 2 * k * camera->y;
	double c = camera->x*camera->x + l*l + camera->y*camera->y - 2 * l * camera->y - camera->view_radius*camera->view_radius;
	double D = b*b - 4 * a * c;
	
	double x, y;
	if (camera->angle_x == 90) {
		x = camera->x;
		y = camera->y + camera->view_radius;
	} else if (camera->angle_x == 270) {
		x = camera->x;
		y = camera->y - camera->view_radius;
	} else if (camera->angle_x > 90 && camera->angle_x < 270) {
		x = (-b - sqrt(D)) / (2 * a);
    	y = k * x + l;
	} else {
		x = (-b + sqrt(D)) / (2 * a);
    	y = k * x + l;
	}

	Camera_draw_line(camera, renderer, window_height, x, y);
}

void Camera_projection(struct Camera *camera, SDL_Renderer *renderer, int window_width, int window_height, int triangles_count, double *triangles) {
	double polygons[6];

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (int i = 0; i < triangles_count; ++i) {
		for (int j = 0; j < 3; ++j) {
			double k1 = tan(DEG_TO_RAD * camera->angle_x);
			double k3;
			if (triangles[i * 9 + j * 3 + 0] == camera->x) {
				k3 = 0;
			} else {
				double k2 = (triangles[i * 9 + j * 3 + 1] - camera->y) / (triangles[i * 9 + j * 3 + 0] - camera->x);
				k3 = (k2 - k1) / (1 + k2 * k1);
			}
			polygons[j * 2 + 0] = (camera->window_width / 2 - k3 * camera->camera_height) * (window_width / camera->window_width);

			k1 = tan(DEG_TO_RAD * camera->angle_y);
			if (triangles[i * 9 + j * 3 + 1] == camera->y) {
				k3 = 0;
			} else {
				double k2 = (triangles[i * 9 + j * 3 + 2] - camera->z) / (triangles[i * 9 + j * 3 + 1] - camera->y);
				k3 = (k2 - k1) / (1 + k2 * k1);
			}
			polygons[j * 2 + 1] = (camera->window_height / 2 + k3 * camera->camera_height) * (window_height / camera->window_height);
		}
		for (int j = 0; j < 2; ++j) {
        	SDL_RenderDrawLine(renderer, polygons[j * 2 + 0], window_height - polygons[j * 2 + 1], polygons[(j + 1) * 2 + 0], window_height - polygons[(j + 1) * 2 + 1]);
    	}
    	SDL_RenderDrawLine(renderer, polygons[4], window_height - polygons[5], polygons[0], window_height - polygons[1]);
	}
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
