#include <SDL2/SDL.h>


extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern SDL_Window *WINDOW;
extern SDL_Renderer *RENDERER;

double tan_sum(double tan_alpha, double tan_beta);
double tan_dif(double tan_alpha, double tan_beta);

void Engine_init(int window_width, int window_height);
void Engine_update(void);
void Engine_exit(void);

void fill(int r, int g, int b);
void draw_circle(double x, double y, double radius, int r, int g, int b);
void draw_line(double x1, double y1, double x2, double y2, int r, int g, int b);
void draw_line_math(double k, double l, int r, int g, int b);
void draw_polygon(int count, double *coords, int r, int g, int b);