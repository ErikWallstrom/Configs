#include "Reg_Point.h"
#include <assert.h>

void get_point(enum Reg_Point r_point, SDL_Rect* dest)
{
	assert(dest);
	switch(r_point)
	{
	case REG_POINT_CENTER:
		dest->x = dest->x - dest->w / 2;
		dest->y = dest->y - dest->h / 2;
		break;
	case REG_POINT_TOP_LEFT:
		break;
	case REG_POINT_TOP_RIGHT:
		dest->x = dest->x - dest->w;
		break;
	case REG_POINT_BOTTOM_LEFT:
		dest->y = dest->y - dest->h;
		break;
	case REG_POINT_BOTTOM_RIGHT:
		dest->x = dest->x - dest->w;
		dest->y = dest->y - dest->h;
		break;
	}
}

void set_point(enum Reg_Point r_point, SDL_Rect* dest)
{
	assert(dest);
	switch(r_point)
	{
	case REG_POINT_CENTER:
		dest->x = dest->x + dest->w / 2;
		dest->y = dest->y + dest->h / 2;
		break;
	case REG_POINT_TOP_LEFT:
		break;
	case REG_POINT_TOP_RIGHT:
		dest->x = dest->x + dest->w;
		break;
	case REG_POINT_BOTTOM_LEFT:
		dest->y = dest->y + dest->h;
		break;
	case REG_POINT_BOTTOM_RIGHT:
		dest->x = dest->x + dest->w;
		dest->y = dest->y + dest->h;
		break;
	}
}
