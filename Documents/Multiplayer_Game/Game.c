#include "Game.h"
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define Game_error(msg) \
	do { \
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, __func__, msg, NULL); \
		abort(); \
	} while(0)

struct Game* Game_ctor(struct Game* self, int width, int height)
{
	assert(self);
	assert(width > 0);
	assert(height > 0);

	srand((unsigned)time(NULL));
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) ||
			!IMG_Init(IMG_INIT_PNG) ||
			SDLNet_Init() ||
			TTF_Init())
		Game_error(SDL_GetError());

	*self = (struct Game){
		.done = 0,
		.width = width,
		.height = height,
		.key_state = SDL_GetKeyboardState(NULL),
		.mouse_state = SDL_GetMouseState(
				&self->mouse_x, 
				&self->mouse_y)
	};

	Vec_ctor(&self->scenes, sizeof(struct Scene*), 0);
	self->window = SDL_CreateWindow(
			"Game Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width, height, 0);
	if(!self->window)
		Game_error(SDL_GetError());
	self->renderer = SDL_CreateRenderer(
			self->window,
			-1,
			SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC |
			SDL_RENDERER_TARGETTEXTURE);
	if(!self->renderer)
		Game_error(SDL_GetError());

	return self;
}

void Game_update(struct Game* self)
{
	assert(self);
	assert(self->scenes.buffer);

	static Uint32 time = 0;
	self->delta = SDL_GetTicks() - time;
	time = SDL_GetTicks();

	while(SDL_PollEvent(&self->event))
		if(self->event.type == SDL_QUIT)
			self->done = 1;
	self->mouse_state = SDL_GetMouseState(
			&self->mouse_x,
			&self->mouse_y);

	SDL_RenderClear(self->renderer);
	if(self->scenes.size)
		Scene_update(self->scenes.buffer[0]);
	SDL_RenderPresent(self->renderer);
}

void Game_dtor(struct Game* self)
{
	assert(self);

	SDL_DestroyRenderer(self->renderer);
	self->renderer = NULL;
	SDL_DestroyWindow(self->window);
	self->renderer = NULL;
	Vec_dtor(&self->scenes);

	SDLNet_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

