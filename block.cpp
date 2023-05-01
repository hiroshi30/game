#include <SDL2/SDL.h>

#include "block.hpp"

Block::Block(int set_x, int set_y) {
    x = set_x;
    y = set_y;
    width = block_width;
    height = block_height;
    border_width = 3;
    
    rect.x = x + border_width;
    rect.y = y + border_width;
    rect.w = width - 2 * border_width;
    rect.h = height - 2 * border_width;

    border.x = x;
    border.y = y;
    border.w = width;
    border.h = height;
};

const void Block::draw_rect(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

const void Block::draw_border(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderFillRect(renderer, &border);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

const void Block::draw(SDL_Renderer *renderer) {
    if (border_width > 0) draw_border(renderer);

    draw_rect(renderer);
}