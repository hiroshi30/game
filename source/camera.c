#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "camera.h"

#define MAX_THRESHOLD 0.01
#define pi 3.14159265


struct Camera *Camera_create(double view_angle, double radius, double x, double y, double z, double angle_x, double angle_y, double speed, int window_width, int window_height) {
	struct Camera *camera = (struct Camera *)malloc(sizeof(struct Camera));

	camera->view_angle = view_angle;
    camera->x = x;
    camera->y = y;
    camera->z = z;
    camera->angle_x = angle_x;
    camera->angle_y = angle_y;
    camera->speed = speed;
    camera->radius = radius;
    camera->time1 = (struct timeval *)malloc(sizeof(struct timeval));
    camera->time2 = (struct timeval *)malloc(sizeof(struct timeval));
    camera->window_width = window_width;
    camera->window_height = window_height;
	camera->camera_height = tan(pi / 2 - pi * (camera->view_angle / 2) / 180) * camera->window_width / 2;

	mingw_gettimeofday(camera->time1, NULL);
	return camera;
}

void Camera_move_forward(struct Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x += camera->speed * cos(pi * camera->angle_x / 180) * delta_time;
		camera->y += camera->speed * sin(pi * camera->angle_x / 180) * delta_time;
	} else {
		camera->x += camera->speed * cos(pi * camera->angle_x / 180) * MAX_THRESHOLD;
		camera->y += camera->speed * sin(pi * camera->angle_x / 180) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
	// printf("%lf\n", delta_time);
}

void Camera_move_backward(struct Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x -= camera->speed * cos(pi * camera->angle_x / 180) * delta_time;
		camera->y -= camera->speed * sin(pi * camera->angle_x / 180) * delta_time;
	} else {
		camera->x -= camera->speed * cos(pi * camera->angle_x / 180) * MAX_THRESHOLD;
		camera->y -= camera->speed * sin(pi * camera->angle_x / 180) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
	// printf("%lf\n", delta_time);
}

void Camera_move_right(struct Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x -= camera->speed * cos(pi * (camera->angle_x + 90) / 180) * delta_time;
		camera->y -= camera->speed * sin(pi * (camera->angle_x + 90) / 180) * delta_time;
	} else {
		camera->x -= camera->speed * cos(pi * (camera->angle_x + 90) / 180) * MAX_THRESHOLD;
		camera->y -= camera->speed * sin(pi * (camera->angle_x + 90) / 180) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
	// printf("%lf\n", delta_time);
}

void Camera_move_left(struct Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x += camera->speed * cos(pi * (camera->angle_x + 90) / 180) * delta_time;
		camera->y += camera->speed * sin(pi * (camera->angle_x + 90) / 180) * delta_time;
	} else {
		camera->x += camera->speed * cos(pi * (camera->angle_x + 90) / 180) * MAX_THRESHOLD;
		camera->y += camera->speed * sin(pi * (camera->angle_x + 90) / 180) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
	// printf("%lf\n", delta_time);
}

void Camera_draw(struct Camera *camera, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (int iy = camera->y - 5; iy <= camera->y + 5; ++iy) {
		for (int ix = camera->x - 5; ix <= camera->x + 5; ++ix) {
    		if ((ix - camera->x) * (ix - camera->x) + (iy - camera->y) * (iy - camera->y) <= 5 * 5) {
    			SDL_RenderDrawPoint(renderer, ix, camera->window_height - iy);
    		}
    	}
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Camera_draw_line(struct Camera *camera, SDL_Renderer *renderer, double x1, double y1) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, camera->x, camera->window_height - camera->y, x1, camera->window_height - y1);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Camera_turn(struct Camera *camera, double x1, double y1) {
	camera->angle_x -= x1;
	while (camera->angle_x < 0) camera->angle_x += 360;
	while (camera->angle_x >= 360) camera->angle_x -= 360;
	camera->angle_y -= y1;
	while (camera->angle_y < 0) camera->angle_y += 360;
	while (camera->angle_y >= 360) camera->angle_y -= 360;
}

void Camera_cast(struct Camera *camera, SDL_Renderer *renderer) {
	double k = tan(pi * camera->angle_x / 180);
	double l = camera->y - k * camera->x;
	double a = k * k + 1;
	double b = -2 * camera->x + 2 * k * l - 2 * k * camera->y;
	double c = camera->x*camera->x + l*l + camera->y*camera->y - 2 * l * camera->y - camera->radius*camera->radius;
	double D = b*b - 4 * a * c;
	
	double x, y;
	if (camera->angle_x == 90) {
		x = camera->x;
		y = camera->y + camera->radius;
	} else if (camera->angle_x == 270) {
		x = camera->x;
		y = camera->y - camera->radius;
	} else if (camera->angle_x > 90 && camera->angle_x < 270) {
		x = (-b - sqrt(D)) / (2 * a);
    	y = k * x + l;
	} else {
		x = (-b + sqrt(D)) / (2 * a);
    	y = k * x + l;
	}
	
	Camera_draw_line(camera, renderer, x, y);
}

// double **Camera_projection(struct Camera *camera, int triangles_count, double triangles[][9]) {
// 	double **polygons = malloc(3 * sizeof(double *));

// 	for (int i = 0; i < triangles_count; ++i) {
// 		polygons[i] = (double *)malloc(2 * sizeof(double *));
// 		for (int j = 0; j < 3; ++j) {
// 			double k1 = -tan(pi * camera->angle_x / 180);
// 			double l1 = triangles[i][1] - k1 * triangles[i][0];
// 			double x2 = camera->x + cos(pi * camera->angle_x / 180) * camera->camera_height;
// 			double y2 = camera->y + sin(pi * camera->angle_x / 180) * camera->camera_height;
// 			double l2 = y2 - k1 * x2;
// 			double h = fabs((l2 - l1) * cos(pi * (camera->angle_x - 90) / 180));
// 			double x = camera->x + (x2 - camera->x) * camera->camera_height / (h + camera->camera_height);
// 			double y = camera->y + (y2 - camera->y) * camera->camera_height / (h + camera->camera_height);
// 			polygons[i][0] = x;
// 			polygons[i][1] = triangles[i][2];
// 		}
// 	}
// 	return polygons;
// }
