#include "Label.hpp"
#include <cassert>

Label::Label(SDL_Renderer* renderer, Reg_Point r_point, int x, int y, TTF_Font* font, const char* text)
	: Entity(nullptr, r_point, x, y, 0, 0)
{
	texture = new Texture(renderer, text, font);
	this->width = texture->get_width();
	this->height = texture->get_height();
	s_rect.w = texture->get_width();
	s_rect.h = texture->get_height();

	this->font = font;
	this->text.assign(text);
	this->renderer = renderer;
}

Label::~Label()
{
	delete texture;
}

void Label::set_text(const char* text)
{
	delete texture;
	texture = new Texture(renderer, text, font);
	width = texture->get_width();
	height = texture->get_height();
	s_rect.w = texture->get_width();
	s_rect.h = texture->get_height();
}
