#include "Sprite.h"

void Sprite_behavior(Entity entity, Game* game)
{
	Sprite self = (Sprite)entity;
	Animation a = self->animations[self->selected_animation];

	if(SDL_GetTicks() - a->delay > a->time)
	{
		if(++a->selected_frame >= Array_len(a->frames))	
			a->selected_frame = 0;
		a->time = SDL_GetTicks();
	}

	SDL_Rect frame = *(SDL_Rect*)a->frames[a->selected_frame];
	self->s_rect = frame;
}
