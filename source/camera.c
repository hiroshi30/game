#include "camera.h"


// double camera_height = tan(pi / 2 - pi * (camera->view_angle / 2) / 180) * window_width / 2;

struct Camera *create_camera() {
	struct Camera *camera = (struct Camera *)malloc(sizeof(struct Camera));
	// static struct Camera *camera = &(struct Camera) {
        // .view_angle=120.0,
        // .x=0.0,
        // .y=0.0,
        // .z=0.0,
        // .angle_x=45.0,
        // .angle_y=0.0,
        // .speed=500.0,
        // .radius=200.0
	// };


    camera->view_angle=120.0;
    camera->x=0.0;
    camera->y=0.0;
    camera->z=0.0;
    camera->angle_x=45.0;
    camera->angle_y=0.0;
    camera->speed=500.0;
    camera->radius=200.0;

	mingw_gettimeofday(&camera->time1, NULL);
	return camera;
}

void move_forward(struct Camera *camera) {
    mingw_gettimeofday(&camera->time2, NULL);
	double delta_time = (double)(camera->time2.tv_usec - camera->time1.tv_usec) / 1000000 + (double)(camera->time2.tv_sec - camera->time1.tv_sec);
	camera->x += camera->speed * cos(pi * camera->angle_x / 180) * fmin(0.01, delta_time);
	camera->y += camera->speed * sin(pi * camera->angle_x / 180) * fmin(0.01, delta_time);
	camera->time1.tv_sec = camera->time2.tv_sec;
	camera->time1.tv_usec = camera->time2.tv_usec;
	// printf("%lf\n", delta_time);
}

void move_backward(struct Camera *camera) {
    mingw_gettimeofday(&camera->time2, NULL);
	double delta_time = (double)(camera->time2.tv_usec - camera->time1.tv_usec) / 1000000 + (double)(camera->time2.tv_sec - camera->time1.tv_sec);
	camera->x -= camera->speed * cos(pi * camera->angle_x / 180) * fmin(0.01, delta_time);
	camera->y -= camera->speed * sin(pi * camera->angle_x / 180) * fmin(0.01, delta_time);
	camera->time1.tv_sec = camera->time2.tv_sec;
	camera->time1.tv_usec = camera->time2.tv_usec;
	// printf("%lf\n", delta_time);
}

void move_right(struct Camera *camera) {
    mingw_gettimeofday(&camera->time2, NULL);
	double delta_time = (double)(camera->time2.tv_usec - camera->time1.tv_usec) / 1000000 + (double)(camera->time2.tv_sec - camera->time1.tv_sec);
	camera->x -= camera->speed * cos(pi * (camera->angle_x + 90) / 180) * fmin(0.01, delta_time);
	camera->y -= camera->speed * sin(pi * (camera->angle_x + 90) / 180) * fmin(0.01, delta_time);
	camera->time1.tv_sec = camera->time2.tv_sec;
	camera->time1.tv_usec = camera->time2.tv_usec;
	// printf("%lf\n", delta_time);
}

void move_left(struct Camera *camera) {
    mingw_gettimeofday(&camera->time2, NULL);
	double delta_time = (double)(camera->time2.tv_usec - camera->time1.tv_usec) / 1000000 + (double)(camera->time2.tv_sec - camera->time1.tv_sec);
	camera->x += camera->speed * cos(pi * (camera->angle_x + 90) / 180) * fmin(0.01, delta_time);
	camera->y += camera->speed * sin(pi * (camera->angle_x + 90) / 180) * fmin(0.01, delta_time);
	camera->time1.tv_sec = camera->time2.tv_sec;
	camera->time1.tv_usec = camera->time2.tv_usec;
	// printf("%lf\n", delta_time);
}

void draw(struct Camera *camera, SDL_Renderer *renderer) {
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

void draw_line(struct Camera *camera, SDL_Renderer *renderer, double x1, double y1) {
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

// double** vertex(struct Camera *camera, double vertices[][3]) {
// 	static double *new_vertices[sizeof(vertices) / sizeof(vertices[0])];
// 	for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); ++i) {
// 		double l3 = camera->y - tan(pi * camera->angle_x / 180) * camera->x;
		
// 	}
// 	return new_vertices;
// }
