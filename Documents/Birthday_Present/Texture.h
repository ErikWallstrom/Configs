#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL_ttf.h>

enum Font_Render_Speed
{
	FONT_RENDER_SPEED_FAST,
	FONT_RENDER_SPEED_SLOW
};

struct Texture
{
	SDL_Texture* raw;
	int width, height;
};

struct Texture* Texture_from_font(SDL_Renderer* renderer, char* text, TTF_Font* font, enum Font_Render_Speed speed, SDL_Color color);
struct Texture* Texture_from_image(SDL_Renderer* renderer, char* file);
struct Texture* Texture_copy(struct Texture* self, struct Texture* dest, SDL_Renderer* renderer);
void Texture_dtor(struct Texture* self);

#endif
