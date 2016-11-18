#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Scene.h"
#include "Vec.h"

#define Game_add(self, scene) Vec_push_back(&(self)->scenes, scene)

typedef struct Game Game;
struct Game
{
	Vec(struct Scene*) scenes;
	SDL_Window* window;
	SDL_Renderer* renderer;
	const Uint8* key_state;
	SDL_Event event;
	Uint32 mouse_state;
	int width, height;
	int mouse_x, mouse_y;
	int delta;
	int done;
};

struct Game* Game_ctor(struct Game* self, int width, int height);
void Game_update(struct Game* self);
void Game_dtor(struct Game* self);

#endif
