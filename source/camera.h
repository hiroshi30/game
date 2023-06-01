#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define window_width 1000
#define window_height 700
#define pi 3.14159265


struct Camera {
	double view_angle;
	double radius;
	double x;
	double y;
	double z;
	double angle_x;
	double angle_y;
	double speed;
	struct timeval *time1;
	struct timeval *time2;
};

struct Camera *Camera_create(double view_angle, double radius, double x, double y, double z, double angle_x, double angle_y, double speed);
void Camera_move_forward(struct Camera *camera);
void Camera_move_backward(struct Camera *camera);
void Camera_move_right(struct Camera *camera);
void Camera_move_left(struct Camera *camera);
void Camera_draw(struct Camera *camera, SDL_Renderer *renderer);
void Camera_draw_line(struct Camera *camera, SDL_Renderer *renderer, double x1, double y1);
void Camera_turn(struct Camera *camera, double x1, double y1);
double* Camera_ray_casting(struct Camera *camera);
double** Camera_vertex(struct Camera *camera, double vertices[][3]);
