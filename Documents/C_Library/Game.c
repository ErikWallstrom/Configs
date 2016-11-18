#include "Game.h"
#include "Scene.h"
#include <time.h>
#include <assert.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

Game Game_new(int width, int height)
{	
	assert(width > 0 && height > 0);
	srand((unsigned)time(NULL));
	if(SDL_Init(SDL_INIT_EVERYTHING) ||
	   TTF_Init() || 
	   !IMG_Init(IMG_INIT_PNG))
		debug(SDL_GetError());

	Game self;
	self.width = width;
	self.height = height;
	self.done = 0;
	self.scenes = Array_new();
	self.window = SDL_CreateWindow(
		"Game Window", 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		width, 
		height, 
		SDL_WINDOW_SHOWN);
	if(!self.window)
		debug(SDL_GetError());
	self.renderer = SDL_CreateRenderer(
		self.window, 
		-1, 
		SDL_RENDERER_ACCELERATED | 
		SDL_RENDERER_PRESENTVSYNC | 
		SDL_RENDERER_TARGETTEXTURE);
	if(!self.renderer)
		debug(SDL_GetError());
	self.key_state = SDL_GetKeyboardState(NULL);
	self.mouse_state = SDL_GetMouseState(
		&self.mouse_x, 
		&self.mouse_y);
	return self;
}

void Game_update(Game* self)
{
	assert(self);
	SDL_Event event;
	while(SDL_PollEvent(&event))
		if(event.type == SDL_QUIT)
			self->done = 1;
	self->mouse_state = SDL_GetMouseState(
		&self->mouse_x, 
		&self->mouse_y);
	if(Array_len(self->scenes))
	{
		SDL_RenderClear(self->renderer);
		Scene_update(self->scenes[0], self); 
		SDL_RenderPresent(self->renderer);
	}
}

void Game_delete(Game* self)
{
	assert(self);
	SDL_DestroyRenderer(self->renderer);
	SDL_DestroyWindow(self->window);
	Array_delete(&self->scenes);

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
