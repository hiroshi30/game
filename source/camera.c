#include "camera.h"

#define MAX_THRESHOLD 0.01
#define PI 3.14159265


struct Camera *Camera_create(double x, double y, double z, double angle_x, double angle_y, double view_angle, double view_radius, double speed) {
	struct Camera *camera = (struct Camera *)malloc(sizeof(struct Camera));

    camera->x = x;
    camera->y = y;
    camera->z = z;
    camera->angle_x = angle_x;
    camera->angle_y = angle_y;
	camera->view_angle = view_angle;
	camera->view_radius = view_radius;
    camera->speed = speed;
    camera->time1 = (struct timeval *)malloc(sizeof(struct timeval));
    camera->time2 = (struct timeval *)malloc(sizeof(struct timeval));

	mingw_gettimeofday(camera->time1, NULL);
	return camera;
}

bool Camera_controls(struct Camera *camera, SDL_Event event) {
    bool update = false;
    
    if(event.type == SDL_MOUSEMOTION) {
        Camera_turn(camera, event.motion.xrel, event.motion.yrel);
        update = true;
    }

    if(KEYBOARD_STATE[SDL_SCANCODE_W]) {
        Camera_move_forward(camera);
        update = true;
    }
                    
    if(KEYBOARD_STATE[SDL_SCANCODE_S]) {
        Camera_move_backward(camera);
        update = true;
    }

    if(KEYBOARD_STATE[SDL_SCANCODE_A]) {
        Camera_move_left(camera);
        update = true;
    }

    if(KEYBOARD_STATE[SDL_SCANCODE_D]) {
        Camera_move_right(camera);
        update = true;
    }

    return update;
}

void Camera_move_forward(struct Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x += camera->speed * cos(PI * camera->angle_x / 180) * delta_time;
		camera->y += camera->speed * sin(PI * camera->angle_x / 180) * delta_time;
	} else {
		camera->x += camera->speed * cos(PI * camera->angle_x / 180) * MAX_THRESHOLD;
		camera->y += camera->speed * sin(PI * camera->angle_x / 180) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
}

void Camera_move_backward(struct Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x -= camera->speed * cos(PI * camera->angle_x / 180) * delta_time;
		camera->y -= camera->speed * sin(PI * camera->angle_x / 180) * delta_time;
	} else {
		camera->x -= camera->speed * cos(PI * camera->angle_x / 180) * MAX_THRESHOLD;
		camera->y -= camera->speed * sin(PI * camera->angle_x / 180) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
}

void Camera_move_right(struct Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x -= camera->speed * cos(PI * (camera->angle_x + 90) / 180) * delta_time;
		camera->y -= camera->speed * sin(PI * (camera->angle_x + 90) / 180) * delta_time;
	} else {
		camera->x -= camera->speed * cos(PI * (camera->angle_x + 90) / 180) * MAX_THRESHOLD;
		camera->y -= camera->speed * sin(PI * (camera->angle_x + 90) / 180) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
}

void Camera_move_left(struct Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x += camera->speed * cos(PI * (camera->angle_x + 90) / 180) * delta_time;
		camera->y += camera->speed * sin(PI * (camera->angle_x + 90) / 180) * delta_time;
	} else {
		camera->x += camera->speed * cos(PI * (camera->angle_x + 90) / 180) * MAX_THRESHOLD;
		camera->y += camera->speed * sin(PI * (camera->angle_x + 90) / 180) * MAX_THRESHOLD;
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

void Camera_cast(struct Camera *camera) {
	double k = tan(PI * camera->angle_x / 180);
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

	draw_line(camera->x, camera->y, x, y, 0, 255, 0);
}

void Camera_projection(struct Camera *camera, int triangles_count, double *triangles) {
	SDL_Vertex triangle[3];
	// double **triangle = malloc(sizeof(double *) * 3);
	// triangle[0] = malloc(sizeof(double) * 2);
	// triangle[1] = malloc(sizeof(double) * 2);
	// triangle[2] = malloc(sizeof(double) * 2);

	// fill(135, 200, 250);
	fill(0, 0, 0);

	draw_circle(camera->x, camera->y, 5, 0, 255, 0);
	camera->angle_x += camera->view_angle / 2;
	Camera_cast(camera);
	camera->angle_x -= camera->view_angle;
	Camera_cast(camera);
	camera->angle_x += camera->view_angle / 2;
	Camera_cast(camera);

	for (int i = 0; i < triangles_count; ++i) {
		for (int j = 0; j < 3; ++j) {

			double k1, k2, k3, k4;
			double b1, b2, b3, b4;
			double x2, y2, z2;
			double x4, y4, z4;
			double length1, half, length2;
			double x, y;

			k1 = tan(PI * camera->angle_x / 180);
			k2 = -1 / k1;
			k3 = (triangles[i * 9 + j * 3 + 1] - camera->y) / (triangles[i * 9 + j * 3 + 0] - camera->x);
			k4 = tan(PI * (camera->angle_x + camera->view_angle / 2) / 180);

			b1 = camera->y - k1 * camera->x;
			b2 = triangles[i * 9 + j * 3 + 1] - k2 * triangles[i * 9 + j * 3 + 0];
			b3 = camera->y - k3 * camera->x;
			b4 = camera->y - k4 * camera->x;

			x2 = (b2 - b1) / (k1 - k2);
			y2 = k1 * x2 + b1;

			x4 = (b4 - b2) / (k2 - k4);
			y4 = k4 * x4 + b4;

			length1 = sqrt((y2 - camera->y) * (y2 - camera->y) + (x2 - camera->x) * (x2 - camera->x));
			half = tan(PI * camera->view_angle / 2 / 180) * length1;
			length2 = sqrt((y2 - triangles[i * 9 + j * 3 + 1]) * (y2 - triangles[i * 9 + j * 3 + 1]) + (x2 - triangles[i * 9 + j * 3 + 0]) * (x2 - triangles[i * 9 + j * 3 + 0]));
			
			if (y2 - y4 > 0) {
				if (triangles[i * 9 + j * 3 + 1] - y2 > 0) {
					x = half + length2;
				} else {
					x = half - length2;
				}
			} else {
				if (triangles[i * 9 + j * 3 + 1] - y2 < 0) {
					x = half + length2;
				} else {
					x = half - length2;
				}
			}
			x = x / half / 2 * WINDOW_WIDTH;

			draw_line_math(k1, b1, 187, 87, 223);
			draw_line_math(k2, b2, 201, 223, 87);
			draw_line_math(k3, b3, 249, 0, 223);
			// for (int xx = 0; xx < WINDOW_WIDTH; ++xx) {
			// 	draw_circle(xx, k1 * xx + b1, 1, 187, 87, 223);
			// 	draw_circle(xx, k2 * xx + b2, 1, 201, 223, 87);
			// 	draw_circle(xx, k3 * xx + b3, 1, 249, 0, 220);
			// }

			draw_circle(x4, y4, 5, 0, 0, 255);
			draw_circle(triangles[i * 9 + j * 3 + 0], triangles[i * 9 + j * 3 + 1], 5, 0, 0, 255);

			// printf("angle_x %lf angle_y %lf\n", camera->angle_x, camera->angle_y);

			k1 = tan(PI * camera->angle_y / 180);
			k2 = -1 / k1;
			k3 = (triangles[i * 9 + j * 3 + 2] - camera->z) / (triangles[i * 9 + j * 3 + 1] - camera->y);
			k4 = tan(PI * (camera->angle_y + camera->view_angle / 2) / 180);

			b1 = camera->z - k1 * camera->y;
			b2 = triangles[i * 9 + j * 3 + 2] - k2 * triangles[i * 9 + j * 3 + 1];
			b3 = camera->z - k3 * camera->y;
			b4 = camera->z - k4 * camera->y;

			y2 = (b2 - b1) / (k1 - k2);
			z2 = k1 * y2 + b1;

			y4 = (b4 - b2) / (k2 - k4);
			z4 = k4 * y4 + b4;

			length1 = sqrt((z2 - camera->z) * (z2 - camera->z) + (y2 - camera->y) * (y2 - camera->y));
			half = tan(PI * camera->view_angle / 2 / 180) * length1;
			length2 = sqrt((z2 - triangles[i * 9 + j * 3 + 2]) * (z2 - triangles[i * 9 + j * 3 + 2]) + (y2 - triangles[i * 9 + j * 3 + 1]) * (y2 - triangles[i * 9 + j * 3 + 1]));
			
			if (z2 - z4 > 0) {
				if (triangles[i * 9 + j * 3 + 2] - z2 > 0) {
					y = half + length2;
				} else {
					y = half - length2;
				}
			} else {
				if (triangles[i * 9 + j * 3 + 2] - z2 < 0) {
					y = half + length2;
				} else {
					y = half - length2;
				}
			}
			y = y / half / 2 * WINDOW_HEIGHT;
			
			triangle[j] = (SDL_Vertex){{x, WINDOW_HEIGHT - y}, {0, 255, 0, 255}, {0, 0}};
		}
		
		SDL_RenderGeometry(RENDERER, NULL, triangle, 3, NULL, 0);
		// draw_polygon(triangle, 3);
		for (int j = 0; j < 2; ++j) {
        	draw_line(triangle[j].position.x, triangle[j].position.y, triangle[j + 1].position.x, triangle[j + 1].position.y, 200, 50, 0);
    	}
    	draw_line(triangle[0].position.x, triangle[0].position.y, triangle[2].position.x, triangle[2].position.y, 200, 50, 0);
	}
}
