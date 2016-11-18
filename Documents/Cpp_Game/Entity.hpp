#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED

#include "Texture.hpp"
class Game;

class Entity
{
public:
	enum Reg_Point 
	{
		POINT_CENTER,
		POINT_TOP_LEFT,
		POINT_TOP_RIGHT,
		POINT_BOTTOM_LEFT,
		POINT_BOTTOM_RIGHT
	};
	Entity(Texture* texture, Reg_Point r_point, int x, int y, int width, int height);
	virtual void update(Game* game);
	virtual void render(SDL_Renderer* renderer);
	virtual ~Entity();

	Texture* get_texture(){ return texture; }
	int get_width(){ return width; }
	int get_height(){ return height; }
	int get_x(){ return x; }
	int get_y(){ return y; }
	int get_real_x();
	int get_real_y();

	void set_width(int width) { this->width = width; }
	void set_height(int height) { this->height = height; }
	void set_x(int x) { this->x = x; }
	void set_y(int y) { this->y = y; }

protected:
	Texture* texture;
	SDL_Rect s_rect;
	int x, y;
	int width, height;
	Reg_Point r_point;

};

#endif
