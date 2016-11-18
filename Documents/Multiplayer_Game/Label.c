#include "Label.h"
#include "Game.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

const char* const LABEL_NAME = "Label";
extern Game* game;

struct Label* Label_ctor(struct Label* self, enum Reg_Point r_point, struct Point pos, TTF_Font* font, char* text, Entity_Behavior behavior)
{
	assert(self);
	assert(font);
	assert(text);

	struct Texture* texture = Texture_from_font(
			malloc(sizeof *texture), 
			game->renderer,
			text,
			font,
			TEXTURE_SPEED_SLOW);
	Entity_ctor(
			(struct Entity*)self, 
			texture, 
			r_point,
			pos, 
			texture->width, 
			texture->height, 
			behavior);
	self->font = font;
	self->name = LABEL_NAME;
	size_t text_len = strlen(text) + 1;
	Vec_ctor(&self->text, 1, text_len);
	Vec_set(&self->text, text, text_len);
	return self;
}

void Label_set_text(struct Label* self, char* text)
{
	assert(self);
	assert(text);

	Texture_dtor(self->texture);
	struct Texture* texture = Texture_from_font(
			self->texture, 
			game->renderer,
			text,
			self->font,
			TEXTURE_SPEED_SLOW);

	Vec_set(&self->text, text, strlen(text) + 1);
	self->width = texture->width;
	self->height = texture->height;
	self->s_rect.w = texture->width;
	self->s_rect.h = texture->height;
}

void Label_dtor(struct Label* self)
{
	assert(self);
	Texture_dtor(self->texture);
	free(self->texture);
	Entity_dtor((struct Entity*)self);
	Vec_dtor(&self->text);
}
