#include <stdbool.h>
#include <time.h>

#include "math_a.h"


typedef struct Camera {
	double x, y, z, angle_x, angle_y, view_angle_x, view_angle_y, z_near, z_far, speed;
	struct timeval *time1;
	struct timeval *time2;
} Camera;

Camera *Camera_create(double x, double y, double z, double angle_x, double angle_y, double view_angle, double z_near, double z_far, double speed);
bool Camera_controls(Camera *camera);
void Camera_move_forward(Camera *camera);
void Camera_move_backward(Camera *camera);
void Camera_move_right(Camera *camera);
void Camera_move_left(Camera *camera);
void Camera_turn(Camera *camera, double x1, double y1);
void Camera_exit(Camera *camera);

void Camera_perspective_projection(Camera *camera, int count, Vector3f *triangles);
