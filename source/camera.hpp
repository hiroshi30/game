#include <SDL2/SDL.h>

class Camera {
private:
	double x;
	double y;
	double angle_x;
	double angle_y;
	double speed;

	double radius;

public:
	Camera(int setX, int setY);
	void move_forward();
	void move_backward();
	void move_right();
	void move_left();
	void draw(SDL_Renderer *renderer);
	void draw_line(SDL_Renderer *renderer, double x1, double y1);
	void turn(double x1, double y1);
	double* ray_casting(int width, int height);
};