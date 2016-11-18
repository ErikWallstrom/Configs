#include "Entity.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>

const char* const ENTITY_NAME = "Enitity";

struct Entity* Entity_ctor(struct Entity* self, struct Texture* texture, enum Reg_Point r_point, struct Point pos, int width, int height, Entity_Behavior behavior)
{
	assert(self);
	assert(texture);

	*self = (struct Entity){
		.texture = texture,
		.behavior = behavior,
		.name = ENTITY_NAME,
		.pos = pos,
		.flip_x = 0,
		.flip_y = 0,
		.width = width,
		.height = height,
		.r_point = r_point,
		.s_rect = {
			.x = 0, 
			.y = 0, 
			.w = texture->width, 
			.h = texture->height
		}
	};

	return self;
}

void Entity_render(struct Entity* self, SDL_Renderer* renderer)
{
	assert(self);
	assert(renderer);
	assert(self->texture);

	SDL_Rect d_rect = {0, 0, self->width, self->height};
	switch(self->r_point)
	{
	case REG_POINT_TOP_LEFT:
		d_rect.x = roundf(self->pos.x);
		d_rect.y = roundf(self->pos.y);
		break;
	case REG_POINT_CENTER:
		d_rect.x = roundf(
				self->pos.x - self->width * 0.5f);
		d_rect.y = roundf(
				self->pos.y - self->height * 0.5f);
		break;
	default:
		assert(!"Invalid Reg_Point");
	}

	SDL_RendererFlip flip = (self->flip_x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) | 
			(self->flip_y ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
	SDL_RenderCopyEx(
			renderer,
			self->texture->raw,
			&self->s_rect,
			&d_rect,
			0.0,
			NULL,
			flip);
}

void Entity_print(struct Entity* self)
{
	assert(self);
	printf("[Entity] {w: %i}, {h: %i}, {s_rect: %i, %i, %i, %i} \n", 
			self->width, 
			self->height, 
			self->s_rect.x, 
			self->s_rect.y, 
			self->s_rect.w, 
			self->s_rect.h);
	putchar('\t');
	Texture_print(self->texture);
	putchar('\t');
	Point_print(&self->pos);
}

void Entity_dtor(struct Entity* self)
{
	self->texture = NULL;
}
