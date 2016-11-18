#include "Entity.hpp"
#include <cassert>

Entity::Entity(Texture* texture, Reg_Point r_point, int x, int y, int width, int height)
{
	this->texture = texture;
	this->r_point = r_point;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->s_rect.x = 0;
	this->s_rect.y = 0;
	if(texture)
	{
		this->s_rect.w = texture->get_width();
		this->s_rect.h = texture->get_height();
	}
}

Entity::~Entity()
{
	
}

void Entity::update(Game* game)
{
}

void Entity::render(SDL_Renderer* renderer)
{
	assert(renderer);
	if(texture)
	{
		SDL_Rect d_rect = {
			get_real_x(),
			get_real_y(),
			width,
			height
		};

		SDL_RenderCopy(
				renderer,
				texture->get_raw(),
				&s_rect,
				&d_rect);
	}
}

int Entity::get_real_x()
{
	switch(r_point)
	{
	case POINT_CENTER:
		return x - width / 2;
	case POINT_TOP_LEFT:
	case POINT_BOTTOM_LEFT:
		return x;
	case POINT_TOP_RIGHT:
	case POINT_BOTTOM_RIGHT:
		return x + width;
	}

	throw "Invalid Reg_Point passed to Entity::get_real_x";
}

int Entity::get_real_y()
{
	switch(r_point)
	{
	case POINT_CENTER:
		return y - height / 2;
	case POINT_TOP_LEFT:
	case POINT_BOTTOM_LEFT:
		return y;
	case POINT_TOP_RIGHT:
	case POINT_BOTTOM_RIGHT:
		return y + height;
	}

	throw "Invalid Reg_Point passed to Entity::get_real_y";
}
