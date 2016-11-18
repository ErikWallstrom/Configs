#include "Scene.h"
#include <assert.h>

struct Scene Scene_init(Scene_Behavior behavior, Scene_Clean_up clean_up)
{
	struct Scene self = {
		behavior,
		clean_up,
		Array_new(),
		0
	};
	return self;
}

void Scene_update(Scene self, Game* game)
{
	assert(self && game);
	if(self->behavior)
		self->behavior(self, game);

	for_each(self->content, i)
	{
		Entity e = self->content[i];
		if(e->behavior)
			e->behavior(e, game);
		Entity_render(e, game);
	}
}

void Scene_delete(Scene* self)
{
	assert(self && *self);
	if((*self)->clean_up)
		(*self)->clean_up(*self);
	
	Array_delete(&(*self)->content);
	free(*self);
	*self = NULL;
}
