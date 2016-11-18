#include "Entity.h"
#include <assert.h>

struct Entity Entity_init(struct Texture texture, int x, int y, Entity_Behavior behavior)
{
	struct Entity self = {
		texture,
		{
			x - self.s_rect.w / 2, 
			y - self.s_rect.y / 2, 
			self.s_rect.w,
			self.s_rect.h
		},
		behavior
	};
	return self;
}

void Entity_render(Entity self, Game* game)
{
	assert(self && game);
	if(self->texture)
		SDL_RenderCopy(
			game->renderer,
			self->texture,
			&self->s_rect,
			&self->d_rect);
}

void Entity_delete(Entity* self)
{
	assert(self && *self);
	if((*self)->texture)
		SDL_DestroyTexture((*self)->texture);
	free(*self);
	*self = NULL;
}
