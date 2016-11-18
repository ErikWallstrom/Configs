#ifndef BUTTON_INCLUDED
#define BUTTON_INCLUDED

#include "Label.hpp"

class Button : public Label
{
protected:
	int presses;
	int mouse_down;
public:
	Button(SDL_Renderer* renderer, Reg_Point r_point, int x, int y, TTF_Font* font, const char* text);
	~Button();

	int get_presses() { return presses; }
	int get_mouse_down(){ return mouse_down; }
};

#endif
