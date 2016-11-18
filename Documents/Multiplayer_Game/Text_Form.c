#include "Text_Form.h"
#include "Game.h"
#include <ctype.h>
#include <assert.h>

const char* const TEXT_FORM_NAME = "Text_Form";
extern Game* game;

struct Text_Form* Text_Form_ctor(struct Text_Form* self, enum Reg_Point r_point, struct Point pos, TTF_Font* font, char* default_text, enum Input_Type input_type, size_t input_max)
{
	assert(self);
	assert(font);
	assert(default_text);

	Button_ctor(
			(struct Button*)self, 
			r_point,
			pos,
			font,
			default_text);

	Vec_ctor(&self->default_text, 1, 0);
	Vec_ctor(&self->input, 1, input_max + 1);
	Vec_set(&self->default_text, default_text, strlen(default_text) + 1);
	Vec_set(&self->input, "", 1);

	self->behavior = Text_Form_update;
	self->input_type = input_type;
	self->input_max = input_max;
	self->name = TEXT_FORM_NAME;
	self->ret_pressed = 0;

	int max = 0;
	for(int i = 32; i < 127; i++)
	{
		int width;
		TTF_GlyphMetrics(
				font, 
				i, 
				NULL, 
				NULL, 
				NULL, 
				NULL, 
				&width);
		if(width > max)
			max = width;
	}
	self->max_width = max;
	return self;
}

void Text_Form_update(struct Entity* e)
{
	struct Text_Form* self = (struct Text_Form*)e;
	struct Point pos;
	Entity_get_real_pos(e, &pos);
	if(game->mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if(game->mouse_x > pos.x &&
				(size_t)game->mouse_x < pos.x + (self->input_max + self->default_text.size) * self->max_width / 2 && 
				game->mouse_y > pos.y &&
				game->mouse_y < pos.y + self->height)
		{
				self->mouse_down = 1;
				self->pressed = 1;
		}
		else
		{
			self->pressed = 0;
		}
	}
	else
		self->mouse_down = 0;

	static char prev_pressed[127 - 32] = {0};
	if(self->pressed)
	{
		for(char i = 32; i < 127; i++)
		{
			if(game->key_state[SDL_GetScancodeFromKey(i)])
			{
				if(!prev_pressed[i - 32])
				{
					if(self->input.size - 1 < self->input_max)
					{
						if(isdigit(i))
						{
							if(!(self->input_type & INPUT_NUM))
								continue;
						}

						if(isalpha(i))
						{
							if(!(self->input_type & INPUT_ALPHA))
								continue;
						}

						if(ispunct(i))
							if(!(self->input_type & INPUT_SYM))
								continue;

						Vec_pop_back(&self->input);
						if(game->key_state[SDL_SCANCODE_LSHIFT])
							Vec_push_back(&self->input, toupper(i));
						else
							Vec_push_back(&self->input, i);
						Vec_push_back(&self->input, '\0');
						prev_pressed[i - 32] = 1;
					}
				}
			}
		}
	}
	
	for(char i = 32; i < 127; i++)
		if(!game->key_state[SDL_GetScancodeFromKey(i)])
			if(prev_pressed[i - 32])
				prev_pressed[i - 32] = 0;

	Vec_set(
			&self->text, 
			self->default_text.buffer, 
			self->default_text.size);
	Vec_pop_back(&self->text);
	Vec_append(
			&self->text,
			self->input.buffer,
			self->input.size);
	Label_set_text((struct Label*) self, self->text.buffer);

	if(self->pressed)
	{
		SDL_SetTextureColorMod(
				self->texture->raw,
				255, 
				0, 
				0);
		SDL_SetRenderDrawColor(game->renderer, 
				255, 
				0, 
				0, 
				255);
		if(game->key_state[SDL_SCANCODE_BACKSPACE])
		{
			if(!self->ret_pressed && self->input.size > 1)
			{
				Vec_pop_back(&self->input);
				Vec_pop_back(&self->input);
				Vec_push_back(&self->input, '\0');
				self->ret_pressed = 1;
			}
		}
		if(!game->key_state[SDL_SCANCODE_BACKSPACE])
			self->ret_pressed = 0;
	}
	else
	{
		SDL_SetTextureColorMod(
				self->texture->raw,
				255,
				255,
				255);
		SDL_SetRenderDrawColor(
				game->renderer, 
				255, 
				255, 
				255, 
				255);
	}

	Point point;
	Entity_get_real_pos(e, &point);
	SDL_Rect rect = {
		point.x - 2, 
		point.y - 2,
		(self->input_max + self->default_text.size) * self->max_width / 2 + 2,
		self->height + 2
	};
	SDL_RenderDrawRect(game->renderer, &rect);
	SDL_SetRenderDrawColor(
			game->renderer, 
			0, 
			0, 
			0, 
			255);
}


void Text_Form_dtor(struct Text_Form* self)
{
	Button_dtor((struct Button*)self);
	Vec_dtor(&self->default_text);
	Vec_dtor(&self->input);
}
