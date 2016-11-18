#include "Texture.hpp"
#include <SDL2/SDL_image.h>
#include <cassert>

Texture::Texture(SDL_Renderer* renderer, const char* file)
{
	assert(renderer);
	assert(file);

	raw = IMG_LoadTexture(renderer, file);
	if(!raw)
		throw IMG_GetError();

	SDL_QueryTexture(
			raw, 
			nullptr, 
			nullptr, 
			&width, 
			&height);
}

Texture::Texture(SDL_Renderer* renderer, const char* text, TTF_Font* font)
{
	assert(renderer);
	assert(text);
	assert(font);

	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface* surface = TTF_RenderText_Blended(
			font, 
			text, 
			color);
	if(!surface)
		throw TTF_GetError();
	raw = SDL_CreateTextureFromSurface(renderer, surface);
	TTF_SizeText(
			font,
			text,
			&width,
			&height);
}

Texture::~Texture()
{
	SDL_DestroyTexture(raw);
}
