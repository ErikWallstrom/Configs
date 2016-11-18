#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include "Vec.h" 

enum Window_Flags
{
	WINDOW_CONTEXT,
	WINDOW_RENDERER
};

struct Window
{
	Vec(SDL_Event) events;
	Vec(char) title;
	SDL_Window* raw;
	union {
		SDL_Renderer* renderer;
		SDL_GLContext* context;
	};

	const Uint8* key_state;
	Uint32 mouse_state;

	enum Window_Flags flags;
	int mouse_x, mouse_y;
	int width, height;
};

struct Window* Window_ctor(struct Window* self, char* title, int width, int height, enum Window_Flags flags);
int Window_update(struct Window* self);
void Window_dtor(struct Window* self);

#endif

