#ifndef REG_POINT_H
#define REG_POINT_H

#include <SDL2/SDL.h>

enum Reg_Point
{
	REG_POINT_CENTER,
	REG_POINT_TOP_LEFT,
	REG_POINT_TOP_RIGHT,
	REG_POINT_BOTTOM_LEFT,
	REG_POINT_BOTTOM_RIGHT,
};

void get_point(enum Reg_Point r_point, SDL_Rect* dest);
void set_point(enum Reg_Point r_point, SDL_Rect* dest);

#endif
