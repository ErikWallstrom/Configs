#include "Sprite.h"
#include <assert.h>

const char* const SPRITE_NAME = "Sprite";

struct Sprite* Sprite_ctor(struct Sprite* self, struct Texture* texture, enum Reg_Point r_point, struct Point pos, int width, int height)
{
	assert(self);
	assert(texture);

	Entity_ctor(
			(struct Entity*)self,
			texture,
			r_point,
			pos,
			width,
			height,
			Sprite_update);
	self->selected_anim = 0;
	self->s_rect.w = width;
	self->s_rect.h = height;
	self->name = SPRITE_NAME;
	Vec_ctor(
			&self->animations, 
			sizeof(struct Animation), 0);
	return self;
}

void Sprite_update(struct Entity* e)
{
	struct Sprite* self = (struct Sprite*)e;
	if(self->animations.size)
	{
		struct Animation* a = &self->animations.buffer[self->selected_anim];
		if(SDL_GetTicks() - a->delay > a->time)
		{
			a->selected_frame++;
			if(a->selected_frame >= a->frames.size)
				a->selected_frame = 0;
			a->time = SDL_GetTicks();
		}

		self->s_rect.x = a->frames.buffer[a->selected_frame].x;
		self->s_rect.y = a->frames.buffer[a->selected_frame].y;
	}
}

void Sprite_dtor(struct Sprite* self)
{
	assert(self);
	Vec_dtor(&self->animations);
	Entity_dtor((struct Entity*)self);
}

