#include <stdio.h>
#include <math.h>

#include "engine2d.h"
#include "camera.h"
#include "globals.h"


#define MAX_THRESHOLD 0.01


Camera *Camera_create(double x, double y, double z, double angle_x, double angle_y, double view_angle, double z_near, double z_far, double speed) {
	Camera *camera = malloc(sizeof(Camera));

    camera->x = x;
    camera->y = y;
    camera->z = z;
    camera->angle_x = angle_x;
    camera->angle_y = angle_y;
	camera->view_angle_x = view_angle;
	camera->view_angle_y = view_angle / 16 * 9;
	camera->z_near = z_near;
	camera->z_far = z_far;
    camera->speed = speed;
    camera->time1 = (struct timeval *)malloc(sizeof(struct timeval));
    camera->time2 = (struct timeval *)malloc(sizeof(struct timeval));

	mingw_gettimeofday(camera->time1, NULL);
	return camera;
}

bool Camera_controls(Camera *camera) {
    bool update = false;
    
    if(EVENT.type == SDL_MOUSEMOTION) {
        Camera_turn(camera, EVENT.motion.xrel, EVENT.motion.yrel);
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

void Camera_move_forward(Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x += camera->speed * cos(PI * camera->angle_x / 180) * delta_time;
		camera->z += camera->speed * sin(PI * camera->angle_x / 180) * delta_time;
	} else {
		camera->x += camera->speed * cos(PI * camera->angle_x / 180) * MAX_THRESHOLD;
		camera->z += camera->speed * sin(PI * camera->angle_x / 180) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
}

void Camera_move_backward(Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x -= camera->speed * cos(PI * camera->angle_x / 180) * delta_time;
		camera->z -= camera->speed * sin(PI * camera->angle_x / 180) * delta_time;
	} else {
		camera->x -= camera->speed * cos(PI * camera->angle_x / 180) * MAX_THRESHOLD;
		camera->z -= camera->speed * sin(PI * camera->angle_x / 180) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
}

void Camera_move_right(Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x -= camera->speed * cos(PI * (camera->angle_x + 90) / 180) * delta_time;
		camera->z -= camera->speed * sin(PI * (camera->angle_x + 90) / 180) * delta_time;
	} else {
		camera->x -= camera->speed * cos(PI * (camera->angle_x + 90) / 180) * MAX_THRESHOLD;
		camera->z -= camera->speed * sin(PI * (camera->angle_x + 90) / 180) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
}

void Camera_move_left(Camera *camera) {
    mingw_gettimeofday(camera->time2, NULL);
	double delta_time = (double)(camera->time2->tv_usec - camera->time1->tv_usec) / 1000000 + (double)(camera->time2->tv_sec - camera->time1->tv_sec);
	if (delta_time < MAX_THRESHOLD) {
		camera->x += camera->speed * cos(PI * (camera->angle_x + 90) / 180) * delta_time;
		camera->z += camera->speed * sin(PI * (camera->angle_x + 90) / 180) * delta_time;
	} else {
		camera->x += camera->speed * cos(PI * (camera->angle_x + 90) / 180) * MAX_THRESHOLD;
		camera->z += camera->speed * sin(PI * (camera->angle_x + 90) / 180) * MAX_THRESHOLD;
	}
	camera->time1->tv_sec = camera->time2->tv_sec;
	camera->time1->tv_usec = camera->time2->tv_usec;
}

void Camera_turn(Camera *camera, double x1, double y1) {
	camera->angle_x -= x1;
	while (camera->angle_x < 0) camera->angle_x += 360;
	while (camera->angle_x >= 360) camera->angle_x -= 360;
	camera->angle_y -= y1;
	if (camera->angle_y >= 90) camera->angle_y = 89;
	if (camera->angle_y <= -90) camera->angle_y = -89;
}

void Camera_exit(Camera *camera) {
	free(camera->time1);
	free(camera->time2);
	free(camera);
}

// void Camera_perspective_projection(Camera *camera, Mesh *mesh) {
// 	Triangle *triangle;

// 	// fill(135, 200, 250);
// 	set_color(0, 0, 0);
// 	fill();

// 	// aspecrt ratio
// 	double a = WINDOW_HEIGHT / WINDOW_WIDTH;

// 	// field of view scaling factor
// 	double f = 1 / tan(PI * camera->view_angle_x / 2 / 180);

// 	// z normalization
// 	double lambda = camera->z_far / (camera->z_far - camera->z_near);
// 	// newX = a * f * x / z;
// 	// newY = f * y / z;
// 	// newZ = lambda * z - lambda * znear;

// 	double *matrix = malloc(sizeof(double *) * 4);
// 	matrix[0] = (double *){a * f, 0, 0, 0};
// 	matrix[0] = (double *){0, f, 0, 0};
// 	matrix[0] = (double *){0, 0, lambda, -lambda * camera->z_near};
// 	matrix[0] = (double *){0, 0, 1, 0};
// 	// double *ptr_matrix = matrix;
// 	Matrix perspectiveProjectionMatrix = {4, 4, matrix};

// 	for (int i = 0; i < count; ++i) {
// 		for (int j = 0; j < 3; ++j) {
// 			triangle.points[j] = Vector3F_mul_Matrix(mesh->triangles[i].points[j], perspectiveProjectionMatrix);
// 		}
		
// 		// set_color(0, 255, 0);
// 		// draw_polygon(3, triangle);
// 		set_color(200, 50, 0);
// 		for (int j = 0; j < 2; ++j) {
//         	draw_line(triangle.points[j].x, triangle.points[j].y, triangle.points[j + 1].x, triangle.points[j + 1].y);
//     	}
//     	draw_line(triangle.points[0].x, triangle.points[0].y, triangle.points[2].x, triangle.points[2].y);
// 	}

// 	free(triangle);
// }



void Camera_perspective_projection(Camera *camera, Mesh *mesh) {
	Vector4f *triangle = malloc(sizeof(Vector4f) * 3);

	// fill(135, 200, 250);
	set_color(0, 0, 0);
	fill();

	// aspecrt ratio
	double a = WINDOW_HEIGHT / WINDOW_WIDTH;

	// field of view scaling factor
	double f = 1 / tan(PI * camera->view_angle_x / 2 / 180);

	// z normalization
	double lambda = camera->z_far / (camera->z_far - camera->z_near);
	// newX = a * f * x / z;
	// newY = f * y / z;
	// newZ = lambda * z - lambda * znear;

	for (int i = 0; i < mesh->count; ++i) {
		for (int j = 0; j < 3; ++j) {
			triangle[j].x = a * f * mesh->triangles[i].points[j].x / mesh->triangles[i].points[j].z;
			triangle[j].y = f * mesh->triangles[i].points[j].y / mesh->triangles[i].points[j].z;
			triangle[j].z = (lambda * mesh->triangles[i].points[j].z - lambda * camera->z_near) / mesh->triangles[i].points[j].z;
		}
		
		set_color(200, 50, 0);
		for (int j = 0; j < 2; ++j) {
        	draw_line(triangle[j].x, triangle[j].y, triangle[j + 1].x, triangle[j + 1].y);
    	}
    	draw_line(triangle[0].x, triangle[0].y, triangle[2].x, triangle[2].y);
	}

	free(triangle);
}
