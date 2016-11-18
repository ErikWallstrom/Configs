#ifndef TEXTURE_INCLUDED
#define TEXTURE_INCLUDED

#include <SDL2/SDL_ttf.h>

class Texture
{
private:
	SDL_Texture* raw;
	int width, height;
public:
	Texture(SDL_Renderer* renderer, const char* file);
	Texture(SDL_Renderer* renderer, const char* text, TTF_Font* font);
	~Texture();
	SDL_Texture* get_raw(){ return raw; }
	int get_width(){ return width; }
	int get_height(){ return height; }
};

#endif
