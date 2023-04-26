#include <SDL2/SDL.h>

// #pragma once

const int block_width = 50;
const int block_height = 50;

class Block {
private:
	int width;
	int height;
	int border;
	int x;
	int y;
public:
	Block(int x, int y);
	sf::RectangleShape rect;
};