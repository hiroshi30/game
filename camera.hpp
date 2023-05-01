#include <SDL2/SDL.h>

class Camera {
private:
	int x;
	int y;
	int radius;
	int angelx;
	int angely;
	int speed_x;
	int speed_y;
public:
	Camera(int setX, int setY);
	void move_forward();
	void move_backward();
	void move_right();
	void move_left();
	const void draw(SDL_Renderer *renderer);
};