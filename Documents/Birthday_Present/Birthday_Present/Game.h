#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Scene.h"

struct Game
{
	struct Window* window;
	Vec(struct Scene*) scenes;
	size_t selected_scene;
};

struct Game* Game_ctor(int width, int height);
void Game_add(struct Game* self, struct Scene* scene);
void Game_start(struct Game* self, void* user_data);
void Game_dtor(struct Game* self);

#endif
