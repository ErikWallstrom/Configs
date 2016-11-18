#include "Scene.h"
#include "Game.h"
#include <stdio.h>
#include <assert.h>

extern Game* game;

struct Scene* Scene_ctor(struct Scene* self, Scene_Content_Behavior content_behavior, Scene_Behavior behavior, Scene_Clean_Up clean_up)
{
	assert(self);
	*self = (struct Scene){
		.content_behavior = content_behavior,
		.behavior = behavior,
		.clean_up = clean_up,
		.done = 0
	};

	Vec_ctor(&self->content, sizeof(struct Entity*), 0);
	return self;
}

void Scene_update(struct Scene* self)
{
	assert(self);
	assert(self->content.buffer);

	if(self->behavior)
		self->behavior(self);

	for(size_t i = 0; i < self->content.size; i++)
	{
		struct Entity* e = self->content.buffer[i];
		if(e->behavior)
			e->behavior(e);
		if(self->content_behavior)
			self->content_behavior(self, e);
		Entity_render(e, game->renderer);
	}
}

void Scene_dtor(struct Scene* self)
{
	assert(self);
	if(self->clean_up)
		self->clean_up(self);
	Vec_dtor(&self->content);
}

