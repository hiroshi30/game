#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define window_width 1000
#define window_height 700
#define pi 3.14159265


struct Camera {
	double view_angle;
	double x;
	double y;
	double z;
	double angle_x;
	double angle_y;
	double speed;
	double radius;
	struct timeval time1;
	struct timeval time2;
};

struct Camera *create_camera();
void move_forward(struct Camera *camera);
void move_backward(struct Camera *camera);
void move_right(struct Camera *camera);
void move_left(struct Camera *camera);
void draw(struct Camera *camera, SDL_Renderer *renderer);
void draw_line(struct Camera *camera, SDL_Renderer *renderer, double x1, double y1);
void turn(struct Camera *camera, double x1, double y1);
double* ray_casting(struct Camera *camera);
double** vertex(struct Camera *camera, double vertices[][3]);
