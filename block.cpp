#include <SDL2/SDL.h>

#include "block.hpp"

Block::Block(int set_x, int set_y) {
    x = set_x;
    y = set_y;
    width = block_width;
    height = block_height;
    border = 3;
    rect.setPosition(x + border, y + border);
    rect.setSize(sf::Vector2f(width - 2 * border, height - 2 * border));
    rect.setFillColor(sf::Color(255, 0, 0));
    rect.setOutlineColor(sf::Color(150, 150, 150));
    rect.setOutlineThickness(border);
};
