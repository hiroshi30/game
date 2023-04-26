#include <SDL2/SDL.h>

#include "camera.hpp"

Camera::Camera(int setX, int setY) {
	angelx = 0;
	angely = 0;
	x = setX;
	y = setY;
	speed_x = 5;
	speed_y = 5;
	circle.setRadius(5);
    circle.setPosition(x - circle.getRadius(), y - circle.getRadius());
	circle.setFillColor(sf::Color(0, 255, 0));
};

void Camera::move_forward() {
	y -= speed_y;
}

void Camera::move_backward() {
	y += speed_y;
}

void Camera::move_right() {
	x += speed_x;
}

void Camera::move_left() {
	x -= speed_x;
}

void Camera::update() {
    circle.setPosition(x - circle.getRadius(), y - circle.getRadius());
}