#include <SDL2/SDL.h>
#include <time.h>


struct Camera {
	double view_angle;
	double camera_height;
	double radius;
	double x;
	double y;
	double z;
	double angle_x;
	double angle_y;
	double speed;
	struct timeval *time1;
	struct timeval *time2;
	int window_width;
	int window_height;
};

struct Camera *Camera_create(double view_angle, double radius, double x, double y, double z, double angle_x, double angle_y, double speed, int window_width, int window_height);
void Camera_move_forward(struct Camera *camera);
void Camera_move_backward(struct Camera *camera);
void Camera_move_right(struct Camera *camera);
void Camera_move_left(struct Camera *camera);
void Camera_draw(struct Camera *camera, SDL_Renderer *renderer);
void Camera_draw_line(struct Camera *camera, SDL_Renderer *renderer, double x1, double y1);
void Camera_turn(struct Camera *camera, double x1, double y1);
void Camera_cast(struct Camera *camera, SDL_Renderer *renderer);
double **Camera_projection(struct Camera *camera, int triangles_count, double triangles[][9]);
