#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL_ttf.h>

typedef struct Texture* Texture;
struct Texture
{
	SDL_Texture* texture;
	SDL_Rect s_rect;
};

struct Texture Texture_from_image(SDL_Renderer* renderer, char* file);
struct Texture Texture_from_font(SDL_Renderer* renderer, TTF_Font* font, char* text);
void Texture_delete(Texture* texture);

#endif
