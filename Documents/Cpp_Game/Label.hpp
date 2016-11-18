#ifndef LABEL_INCLUDED
#define LABEL_INCLUDED

#include "Entity.hpp"
#include <string>

class Label : public Entity
{
protected:
	SDL_Renderer* renderer;
	std::string text;
	TTF_Font* font;
public:
	Label(SDL_Renderer* renderer, Reg_Point r_point, int x, int y, TTF_Font* font, const char* text);
	void set_text(const char* text);
	const char* get_text(){ return text.c_str(); }
	~Label();
};

#endif
