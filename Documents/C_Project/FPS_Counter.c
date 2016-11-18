#include "FPS_Counter.h"
#include <assert.h>

const char* const FPS_COUNTER_NAME = "FPS_Counter";

struct FPS_Counter* FPS_Counter_ctor(struct FPS_Counter* self, enum Reg_Point r_point, struct Point pos, TTF_Font* font)
{
	assert(self);
	assert(font);

	Label_ctor(
			(struct Label*)self, 
			r_point, 
			pos, 
			font, 
			"FPS: 0", 
			FPS_Counter_update);

	self->time = 0;
	self->frames = 0;
	self->name = FPS_COUNTER_NAME;
	return self;
}

void FPS_Counter_update(struct Entity* e)
{
	struct FPS_Counter* self = (struct FPS_Counter*)e;
	if(SDL_GetTicks() / 1000 > self->time)
	{
		static char buffer[sizeof(int) * 8 + 2 + 5] = "FPS: ";
		SDL_itoa(self->frames, buffer + 5, 10);

		Label_set_text((struct Label*)self, buffer);
		if(self->frames <= 30)
			SDL_SetTextureColorMod(self->texture->raw, 255, 0, 0);
		else if(self->frames <= 50)
			SDL_SetTextureColorMod(self->texture->raw, 255, 150, 0);
		else
			SDL_SetTextureColorMod(self->texture->raw, 0, 255, 0);

		self->time++;
		self->frames = 0;
	}

	self->frames++;
}

void FPS_Counter_dtor(struct FPS_Counter* self)
{
	assert(self);
	Label_dtor((struct Label*)self);
}
