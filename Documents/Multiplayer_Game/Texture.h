#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL_ttf.h>

typedef struct Texture Texture;
struct Texture
{
	SDL_Texture* raw;
	int width, height;
};

typedef enum Texture_Speed Texture_Speed;
enum Texture_Speed
{
	TEXTURE_SPEED_FAST,
	TEXTURE_SPEED_SLOW,
};

struct Texture* Texture_from_image(struct Texture* self, SDL_Renderer* renderer, char* file);
struct Texture* Texture_from_font(struct Texture* self, SDL_Renderer* renderer, char* text, TTF_Font* font, enum Texture_Speed speed);
struct Texture* Texture_copy(struct Texture* self, struct Texture* dest, SDL_Renderer* renderer);
void Texture_print(struct Texture* self);
void Texture_dtor(struct Texture* self);

#endif
