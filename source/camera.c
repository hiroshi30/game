#include "camera.h"

#define MAX_THRESHOLD 0.01


struct Camera *Camera_create(double view_angle, double radius, double x, double y, double z, double angle_x, double angle_y, double speed) {
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
	// double camera_height = tan(pi / 2 - pi * (camera->view_angle / 2) / 180) * window_width / 2;

	// if (view_angle == NULL)
    // 	camera->view_angle = 120.0;
    // if (x == NULL)
    // 	camera->x=0.0;
    // if (y == NULL)
    // 	camera->y=0.0;
    // if (z == NULL)
    // 	camera->z=0.0;
    // if (angle_x == NULL)
    // 	camera->angle_x=45.0;
    // if (angle_y == NULL)
    // 	camera->angle_y=0.0;
    // if (speed == NULL)
    // 	camera->speed=500.0;
    // if (radius == NULL)
    // 	camera->radius=200.0;

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
    			SDL_RenderDrawPoint(renderer, ix, window_height - iy);
    		}
    	}
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Camera_draw_line(struct Camera *camera, SDL_Renderer *renderer, double x1, double y1) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, camera->x, window_height - camera->y, x1, window_height - y1);
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

double* Camera_ray_casting(struct Camera *camera) {
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

// double** Camera_vertex(struct Camera *camera, double vertices[][3]) {
// 	static double *new_vertices[sizeof(vertices) / sizeof(vertices[0])];
// 	for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); ++i) {
// 		double l3 = camera->y - tan(pi * camera->angle_x / 180) * camera->x;
		
// 	}
// 	return new_vertices;
// }
