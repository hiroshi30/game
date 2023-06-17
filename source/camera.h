#include <SDL2/SDL.h>
#include <time.h>


struct Camera {
	double view_angle;
	double x;
	double y;
	double z;
	double angle_x;
	double angle_y;
	double speed;
	double view_radius;
	struct timeval *time1;
	struct timeval *time2;
};

struct Camera *Camera_create(double x, double y, double z, double angle_x, double angle_y, double view_angle, double view_radius, double speed);
void Camera_move_forward(struct Camera *camera);
void Camera_move_backward(struct Camera *camera);
void Camera_move_right(struct Camera *camera);
void Camera_move_left(struct Camera *camera);
void Camera_turn(struct Camera *camera, double x1, double y1);
void Camera_cast(struct Camera *camera);
void Camera_projection(struct Camera *camera, int triangles_count, double *triangles);