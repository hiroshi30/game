#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern SDL_Window *WINDOW;
extern SDL_Renderer *RENDERER;
Uint8 *KEYBOARD_STATE;

void Engine_init(int window_width, int window_height);
void Engine_keyboard_init(void);
void Engine_mouse_init(void);
void Engine_update(void);
bool Engine_event_exit(SDL_Event event);
void Engine_exit(void);

void fill(int r, int g, int b);
void draw_circle(double x, double y, double radius, int r, int g, int b);
void draw_line(double x1, double y1, double x2, double y2, int r, int g, int b);
void draw_line_math(double k, double l, int r, int g, int b);
void draw_polygon(int count, double *coords, int r, int g, int b);