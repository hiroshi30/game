#include <SDL2/SDL.h>
	
// #include <cmath>

class Camera {
private:
	int angelx;
	int angely;
	int x;
	int y;
	int speed_x;
	int speed_y;
public:
	Camera(int setX, int setY);
	sf::CircleShape circle;
	void move_forward();
	void move_backward();
	void move_right();
	void move_left();
	void update();
};