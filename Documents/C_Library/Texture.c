#include "Texture.h"
#include "Base.h"
#include <assert.h>
#include <SDL2/SDL_image.h>

struct Texture Texture_from_image(SDL_Renderer* renderer, char* file)
{
	assert(renderer && file);
	struct Texture self = {
		IMG_LoadTexture(renderer, file),
		{0}
	};
	if(!self.texture)
		debug(IMG_GetError());
	SDL_QueryTexture(
		self.texture, 
		NULL, 
		NULL, 
		&self.s_rect.w,
		&self.s_rect.h);
	return self;
}

struct Texture Texture_from_font(SDL_Renderer* renderer, TTF_Font* font, char* text)
{
	assert(renderer && font && text);
	SDL_Surface* surface = TTF_RenderText_Blended(
		font, 
		text,
		(SDL_Color){
			255,
			255, 
			255,
			255
		});
	if(!surface)
		debug(TTF_GetError());
	struct Texture self = {
		SDL_CreateTextureFromSurface(
			renderer,
			surface),
		{0}
	};
	TTF_SizeText(
		font, 
		text, 
		&self.s_rect.w,
		&self.s_rect.h);
	SDL_FreeSurface(surface);
	return self;
}

void Texture_delete(Texture* self)
{
	assert(self && *self);
	SDL_DestroyTexture((*self)->texture);
	free(*self);
	*self = NULL;
}
