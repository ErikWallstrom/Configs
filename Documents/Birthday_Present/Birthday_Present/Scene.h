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
struct Scene;

typedef void(*Scene_Update)(struct Scene*, struct Game*, void*);

struct Scene
{
	Scene_Update update;
	enum Scene_Change change;
};

#endif

