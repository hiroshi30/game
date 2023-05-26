#include <SDL2/SDL.h>

#include "block.hpp"

class Camera {
private:
	double x;
	double y;
	double angle_x;
	double angle_y;
	double speed;
	double radius;

public:
	Camera(double set_x, double set_y);
	void move_forward();
	void move_backward();
	void move_right();
	void move_left();
	void draw(SDL_Renderer *renderer);
	void draw_line(SDL_Renderer *renderer, double x1, double y1);
	void turn(double x1, double y1);
	double* ray_casting();
	double* ray_casting0(Block blocks[]);
};