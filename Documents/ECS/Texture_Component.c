#include "Texture_Component.h"
#include "Error.h"
#include <assert.h>
#include <SDL2/SDL_image.h>

struct Texture_Component* Texture_Component_from_font(struct Texture_Component* self, SDL_Renderer* renderer, char* text, TTF_Font* font, enum Texture_Speed speed)
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
	}

	if(!surface)
		error(TTF_GetError());
	self->texture = SDL_CreateTextureFromSurface(renderer, surface);
	TTF_SizeText(
			font,
			text,
			&self->width,
			&self->height);
	SDL_FreeSurface(surface);
	return self;
}

struct Texture_Component* Texture_Component_from_image(struct Texture_Component* self, SDL_Renderer* renderer, char* file)
{
	assert(self);
	assert(renderer);
	assert(file);

	self->texture = IMG_LoadTexture(renderer, file);
	if(!self->texture)
		error(IMG_GetError());
	SDL_QueryTexture(
			self->texture, 
			NULL, 
			NULL, 
			&self->width,
			&self->height);
	return self;
}

struct Texture_Component* Texture_Component_copy(struct Texture_Component* self, struct Texture_Component* dest, SDL_Renderer* renderer)
{
	assert(self);
	assert(dest);

	dest->width = self->width;
	dest->height = self->height;

	Uint32 format;
	SDL_QueryTexture(self->texture, &format, NULL, NULL, NULL);
	dest->texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, self->width, self->height);
	if(!dest->texture)
		error(SDL_GetError());

	SDL_SetTextureBlendMode(dest->texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, dest->texture);
	SDL_RenderClear(renderer);
	SDL_Rect s_rect = {0, 0, self->width, self->height};
	SDL_Rect d_rect = {0, 0, self->width, self->height};
	SDL_RenderCopy(renderer, self->texture, &s_rect, &d_rect);
	SDL_SetRenderTarget(renderer, NULL);

	return dest;
}

