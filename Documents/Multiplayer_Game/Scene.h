#ifndef SCENE_H
#define SCENE_H

#include "Vec.h"
#include "Entity.h"

#define Scene_add(self, entity) Vec_push_back(&(self)->content, entity)

typedef struct Scene Scene;
typedef void(*Scene_Behavior)(struct Scene*);
typedef void(*Scene_Content_Behavior)(struct Scene*, struct Entity*);
typedef void(*Scene_Clean_Up)(struct Scene*);

struct Scene
{
	Vec(struct Entity*) content;
	Scene_Content_Behavior content_behavior;
	Scene_Behavior behavior;
	Scene_Clean_Up clean_up;
	int done;
};

struct Scene* Scene_ctor(struct Scene* self, Scene_Content_Behavior content_behavior, Scene_Behavior behavior, Scene_Clean_Up clean_up);
void Scene_update(struct Scene* self);
void Scene_dtor(struct Scene* self);

#endif
