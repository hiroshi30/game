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

double tan_sum(double tan_alpha, double tan_beta);
double tan_dif(double tan_alpha, double tan_beta);
void draw_circle(SDL_Renderer *renderer, int window_height, double x, double y, double radius, int r, int g, int b);

struct Camera *Camera_create(double x, double y, double z, double angle_x, double angle_y, double view_angle, double view_radius, double speed);
void Camera_move_forward(struct Camera *camera);
void Camera_move_backward(struct Camera *camera);
void Camera_move_right(struct Camera *camera);
void Camera_move_left(struct Camera *camera);
void Camera_turn(struct Camera *camera, double x1, double y1);
void Camera_cast(struct Camera *camera, SDL_Renderer *renderer, int window_height);
void Camera_projection(struct Camera *camera, SDL_Renderer *renderer, int window_width, int window_height, int triangles_count, double *triangles);
