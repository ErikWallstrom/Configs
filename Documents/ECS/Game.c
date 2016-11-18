#include "Game.h"
#include "Error.h"
#include <time.h>
#include <assert.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

struct Game* Game_ctor(struct Game* self, int width, int height)
{
	assert(self);
	assert(width > 0);
	assert(height > 0);

	if(SDL_Init(SDL_INIT_VIDEO))
		error(SDL_GetError());
	if(!IMG_Init(IMG_INIT_PNG))
		error(SDL_GetError());
	if(TTF_Init())
		error(SDL_GetError());
	srand(time(NULL));
	
	Window_ctor(&self->window, "Game Window", width, height, WINDOW_RENDERER);
	Vec_ctor(&self->scenes, sizeof(struct Scene*), 0);
	self->selected_scene = 0;
	return self;
}

void Game_add(struct Game* self, struct Scene* scene)
{
	assert(self);
	assert(scene);

	Vec_push_back(&self->scenes, scene);
}

void Game_start(struct Game* self)
{
	assert(self);
	assert(self->selected_scene < self->scenes.size);

	while(Window_update(&self->window))
	{
		struct Scene* scene = self->scenes.buffer[self->selected_scene];
		scene->update(scene, self);
		switch(scene->change)
		{
		case SCENE_CHANGE_NEXT:
			assert(self->selected_scene + 1 < self->scenes.size);
			self->selected_scene++;
			break;
		case SCENE_CHANGE_PREV:
			assert(self->selected_scene > 0);
			self->selected_scene--;
			break;
		default:;
		}
	}
}

void Game_dtor(struct Game* self)
{
	assert(self);
	Window_dtor(&self->window);
	Vec_dtor(&self->scenes);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
