#include "Game.h"
#include "Error.h"
#include <time.h>
#include <assert.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

struct Game* Game_ctor(int width, int height)
{
	struct Game* self = malloc(sizeof(struct Game));
	assert(self);

	if(SDL_Init(SDL_INIT_VIDEO))
		error(SDL_GetError());
	if(!IMG_Init(IMG_INIT_PNG))
		error(SDL_GetError());
	if(TTF_Init())
		error(SDL_GetError());
	srand(time(NULL));
	
	self->window = Window_ctor("Game Window", width, height, WINDOW_RENDERER);
	self->scenes = Vec_ctor(sizeof(struct Scene*), 0);
	self->selected_scene = 0;
	return self;
}

void Game_add(struct Game* self, struct Scene* scene)
{
	assert(self);
	assert(scene);

	Vec_push_back(&self->scenes, scene);
}

void Game_start(struct Game* self, void* user_data)
{
	assert(self);
	assert(self->selected_scene < Vector(&self->scenes).size);

	while(Window_update(self->window))
	{
		if(Vector(&self->scenes).size)
		{
			struct Scene* scene = self->scenes[self->selected_scene];
			if(scene->update)
				scene->update(scene, self, user_data);

			switch(scene->change)
			{
			case SCENE_CHANGE_NEXT:
				assert(self->selected_scene + 1 < Vector(&self->scenes).size);
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
}

void Game_dtor(struct Game* self)
{
	assert(self);
	Window_dtor(self->window);
	Vec_dtor(&self->scenes);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	free(self);
}
