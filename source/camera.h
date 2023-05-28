#include <SDL2/SDL.h>

#define window_width 500
#define window_height 500
#define pi 3.14159265


struct Camera {
	double view_angle;
	double draw_radius;
	double x;
	double y;
	double z;
	double angle_x;
	double angle_y;
	double speed;
	double radius;
};

void move_forward(struct Camera *camera);
void move_backward(struct Camera *camera);
void move_right(struct Camera *camera);
void move_left(struct Camera *camera);
void draw(SDL_Renderer *renderer, struct Camera *camera);
void draw_line(SDL_Renderer *renderer, struct Camera *camera, double x1, double y1);
void turn(struct Camera *camera, double x1, double y1);
double* ray_casting(struct Camera *camera);
double** vertex(struct Camera *camera, double vertices[][3]);
// double* ray_casting0(Block blocks[]);
