#include "Texture.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

#define Texture_error(msg) \
	do { \
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", msg, NULL); \
		abort(); \
	} while(0)

struct Texture* Texture_from_image(struct Texture* self, SDL_Renderer* renderer, char* file)
{
	assert(self);
	assert(renderer);
	assert(file);

	self->raw = IMG_LoadTexture(renderer, file);
	if(!self->raw)
		Texture_error(IMG_GetError());
	SDL_QueryTexture(
			self->raw, 
			NULL, 
			NULL, 
			&self->width,
			&self->height);
	return self;
}

struct Texture* Texture_from_font(struct Texture* self, SDL_Renderer* renderer, char* text, TTF_Font* font, enum Texture_Speed speed)
{
	assert(self);
	assert(renderer);
	assert(text);
	assert(font);
	
	SDL_Color color = {255, 255, 255, 255}; //White
	SDL_Surface* surface;
	switch(speed)
	{
	case TEXTURE_SPEED_FAST:
		surface = TTF_RenderText_Solid(font, text, color);
		break;
	case TEXTURE_SPEED_SLOW:
		surface = TTF_RenderText_Blended(font, text, color);
		break;
	default:
		Texture_error("Invalid speed");
	}

	if(!surface)
		Texture_error(TTF_GetError());
	self->raw = SDL_CreateTextureFromSurface(renderer, surface);
	TTF_SizeText(
			font,
			text,
			&self->width,
			&self->height);
	SDL_FreeSurface(surface);
	return self;
}

struct Texture* Texture_copy(struct Texture* self, struct Texture* dest, SDL_Renderer* renderer)
{
	assert(self);
	assert(dest);

	dest->width = self->width;
	dest->height = self->height;

	Uint32 format;
	SDL_QueryTexture(self->raw, &format, NULL, NULL, NULL);
	dest->raw = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, self->width, self->height);
	if(!dest->raw)
		Texture_error(SDL_GetError());

	SDL_SetTextureBlendMode(dest->raw, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, dest->raw);
	SDL_RenderClear(renderer);
	SDL_Rect s_rect = {0, 0, self->width, self->height};
	SDL_Rect d_rect = {0, 0, self->width, self->height};
	SDL_RenderCopy(renderer, self->raw, &s_rect, &d_rect);
	SDL_SetRenderTarget(renderer, NULL);

	return dest;
}

void Texture_print(struct Texture* self)
{
	assert(self);
	printf("[Texture] {raw: %p}, {w: %i}, {h: %i}\n", 
			self->raw, 
			self->width, 
			self->height);
}

void Texture_dtor(struct Texture* self)
{
	assert(self);
	SDL_DestroyTexture(self->raw);
	self->raw = NULL;
}
