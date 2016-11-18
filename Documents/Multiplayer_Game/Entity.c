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

	struct Point pos;
	Entity_get_real_pos(self, &pos);
	SDL_Rect d_rect = {
		pos.x, 
		pos.y, 
		self->width, 
		self->height
	};

	SDL_RendererFlip flip = (
			((self->flip_x) 
				? SDL_FLIP_HORIZONTAL 
				: SDL_FLIP_NONE) |
			((self->flip_y)
				? SDL_FLIP_VERTICAL 
				: SDL_FLIP_NONE));

	SDL_RenderCopyEx(
			renderer,
			self->texture->raw,
			&self->s_rect,
			&d_rect,
			0.0,
			NULL,
			flip);
}

void Entity_get_real_pos(struct Entity* self, struct Point* dest)
{
	assert(self);
	assert(dest);

	switch(self->r_point)
	{
	case REG_POINT_CENTER:
		dest->x = self->pos.x - self->width / 2;
		dest->y = self->pos.y - self->height / 2;
		break;
	case REG_POINT_TOP_LEFT:
		dest->x = self->pos.x;
		dest->y = self->pos.y;
		break;
	case REG_POINT_TOP_RIGHT:
		dest->x = self->pos.x - self->width;
		dest->y = self->pos.y;
		break;
	case REG_POINT_BOTTOM_LEFT:
		dest->x = self->pos.x;
		dest->y = self->pos.y - self->height;
		break;
	case REG_POINT_BOTTOM_RIGHT:
		dest->x = self->pos.x - self->width;
		dest->y = self->pos.y - self->height;
		break;
	default:
		assert(!"Invalid Reg_Point");
	}
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
