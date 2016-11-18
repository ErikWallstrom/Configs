#include "Button.h"
#include <assert.h>

struct Button Button_init(struct Entity entity, char* label)
{
	assert(label);
	struct Button self = {
		entity,
		0, 0,
		String_new(label)
	};
	return self;
}

void Button_behavior(Entity entity, Game* game)
{
	assert(entity && game);
	Button self = (Button)entity;
	if(game->mouse_x > self->d_rect.x &&
	   game->mouse_x < self->d_rect.x + self->d_rect.w &&
	   game->mouse_y > self->d_rect.y &&
	   game->mouse_y < self->d_rect.y + self->d_rect.h) {
		if(self->texture)
			SDL_SetTextureColorMod(
				self->texture,
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
		if(self->texture)
			SDL_SetTextureColorMod(
				self->texture,
				255, 
				255, 
				255);
	}
}

void Button_delete(Button* self)
{
	assert(self && *self);
	String_delete(&(*self)->label);
	Entity_delete((Entity*)self);
}
