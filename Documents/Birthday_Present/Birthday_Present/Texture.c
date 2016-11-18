#include "Texture.h"
#include "Error.h"
#include <assert.h>
#include <SDL2/SDL_image.h>

struct Texture* Texture_from_font(SDL_Renderer* renderer, char* text, TTF_Font* font, enum Font_Render_Speed speed, SDL_Color color)
{
	assert(renderer);
	assert(text);
	assert(font);

	struct Texture* self = malloc(sizeof(struct Texture));	
	assert(self);
	
	SDL_Surface* surface;
	switch(speed)
	{
	case FONT_RENDER_SPEED_FAST:
		surface = TTF_RenderText_Solid(font, text, color);
		break;
	case FONT_RENDER_SPEED_SLOW:
		surface = TTF_RenderText_Blended(font, text, color);
		break;
	}

	if(!surface)
		error(TTF_GetError());
	self->raw = SDL_CreateTextureFromSurface(renderer, surface);
	TTF_SizeText(
		font,
		text,
		&self->width,
		&self->height
	);
	SDL_FreeSurface(surface);
	return self;
}

struct Texture* Texture_from_image(SDL_Renderer* renderer, char* file)
{
	assert(renderer);
	assert(file);

	struct Texture* self = malloc(sizeof(struct Texture));	
	assert(self);

	self->raw = IMG_LoadTexture(renderer, file);
	if(!self->raw)
		error(IMG_GetError());
	SDL_QueryTexture(
		self->raw, 
		NULL, 
		NULL, 
		&self->width,
		&self->height
	);
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
		error(SDL_GetError());

	SDL_SetTextureBlendMode(dest->raw, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, dest->raw);
	SDL_RenderClear(renderer);
	SDL_Rect s_rect = {0, 0, self->width, self->height};
	SDL_Rect d_rect = {0, 0, self->width, self->height};
	SDL_RenderCopy(renderer, self->raw, &s_rect, &d_rect);
	SDL_SetRenderTarget(renderer, NULL);

	return dest;
}

void Texture_dtor(struct Texture* self)
{
	assert(self);
	SDL_DestroyTexture(self->raw);
	free(self);
}
