#ifndef SCENE_H
#define SCENE_H

#include "Vec.h"
enum Scene_Change
{
	SCENE_CHANGE_NONE,
	SCENE_CHANGE_PREV,
	SCENE_CHANGE_NEXT
};

struct Game;
struct Scene
{
	void(*update)(struct Scene* self, struct Game* game);
	enum Scene_Change change;
};

#endif

