#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include <SDL2/SDL_ttf.h>

enum Texture_Speed
{
	TEXTURE_SPEED_FAST,
	TEXTURE_SPEED_SLOW,
};

struct Texture_Component
{
	SDL_Texture* texture;
	int width, height;
};

struct Texture_Component* Texture_Component_from_font(struct Texture_Component* self, SDL_Renderer* renderer, char* text, TTF_Font* font, enum Texture_Speed speed);
struct Texture_Component* Texture_Component_from_image(struct Texture_Component* self, SDL_Renderer* renderer, char* file);
struct Texture_Component* Texture_Component_copy(struct Texture_Component* self, struct Texture_Component* dest, SDL_Renderer* renderer);

#endif
