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
	self->pressed = 0;

	return self;
}

void Button_update(struct Entity* e)
{
	struct Button* self = (struct Button*)e;
	struct Point pos;
	Entity_get_real_pos(e, &pos);
	if(game->mouse_x > pos.x &&
			game->mouse_x < pos.x + self->width &&
			game->mouse_y > pos.y &&
			game->mouse_y < pos.y + self->height)
	{
		SDL_SetTextureColorMod(
				self->texture->raw,
				255, 
				0, 
				0);
		if(game->mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			self->mouse_down = 1;
			SDL_SetTextureColorMod(
					self->texture->raw,
					255, 
					120, 
					80);
		}
		else
			if(self->mouse_down)
			{
				self->mouse_down = 0;
				self->pressed++;
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
