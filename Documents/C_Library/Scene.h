#ifndef SCENE_H
#define SCENE_H

#include "Entity.h"

typedef struct Scene* Scene;
typedef void(*Scene_Behavior)(Scene, Game*);
typedef void(*Scene_Clean_up)(Scene);
struct Scene
{
	Scene_Behavior behavior;
	Scene_Clean_up clean_up;
	Array content;
	int done;
};

struct Scene Scene_init(Scene_Behavior behavior, Scene_Clean_up clean_up);
void Scene_update(Scene scene, Game* game);
void Scene_delete(Scene* scene);

#endif
