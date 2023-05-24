#include <SDL2/SDL.h>

const int block_width = 50;
const int block_height = 50;

class Block {
private:
	int x;
	int y;
	int width;
	int height;
	int border_width;
public:
	SDL_Rect rect;
	SDL_Rect border;
	Block() = default;
	Block(int x, int y);
	void draw_rect(SDL_Renderer *renderer);
	void draw_border(SDL_Renderer *renderer);
	void draw(SDL_Renderer *renderer);
};