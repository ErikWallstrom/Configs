#include "Button.h"
#include "Game.h"
#include <assert.h>

const char* const BUTTON_NAME = "Button";
extern Game* game;

struct Button* Button_ctor(struct Button* self, enum Reg_Point r_point, struct Point pos, TTF_Font* font, char* text)
{
	assert(self);
	assert(font);
	assert(text);

	Label_ctor(
			(struct Label*)self, 
			r_point, 
			pos, 
			font, 
			text,
			Button_update);

	self->name = BUTTON_NAME;
	self->mouse_down = 0;
	self->presses = 0;

	return self;
}

void Button_update(struct Entity* e)
{
	struct Button* self = (struct Button*)e;
	if((self->r_point == REG_POINT_TOP_LEFT) ? 
			(game->mouse_x > self->pos.x &&
			game->mouse_x < self->pos.x + self->width &&
			game->mouse_y > self->pos.y &&
			game->mouse_y < self->pos.y + self->height) :
			(game->mouse_x > self->pos.x - self->width * 0.5 &&
			game->mouse_x < self->pos.x + self->width * 0.5 &&
			game->mouse_y > self->pos.y - self->height * 0.5 &&
			game->mouse_y < self->pos.y + self->height * 0.5))
	{
		SDL_SetTextureColorMod(
				self->texture->raw,
				255, 
				0, 
				0);
		if(game->mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))
			self->mouse_down = 1;
		else
			if(self->mouse_down)
			{
				self->mouse_down = 0;
				self->presses++;
			}
	}
	else
	{
		self->mouse_down = 0;
		SDL_SetTextureColorMod(
				self->texture->raw,
				255,
				255,
				255);
	}
}

void Button_dtor(struct Button* self)
{
	Label_dtor((struct Label*)self);
}
