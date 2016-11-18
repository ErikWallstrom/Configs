#ifndef ENTITY_H
#define ENTITY_H

#include "Texture.h"
#include "Point.h"

enum Reg_Point
{
	REG_POINT_CENTER,
	REG_POINT_TOP_LEFT,
	REG_POINT_TOP_RIGHT,
	REG_POINT_BOTTOM_LEFT,
	REG_POINT_BOTTOM_RIGHT
};

typedef struct Entity Entity;
typedef void(*Entity_Behavior)(struct Entity*);
extern const char* const ENTITY_NAME;
struct Entity
{
	SDL_Rect s_rect;
	Entity_Behavior behavior;
	struct Texture* texture; 
	const char* name;
	struct Point pos;
	int width, height;
	int flip_x, flip_y;
	enum Reg_Point r_point;
};

struct Entity* Entity_ctor(struct Entity* self, struct Texture* texture, enum Reg_Point r_point, struct Point pos, int width, int height, Entity_Behavior behavior);
void Entity_render(struct Entity* self, SDL_Renderer* renderer);
void Entity_get_real_pos(struct Entity* self, struct Point* dest);
void Entity_print(struct Entity* self);
void Entity_dtor(struct Entity* self);

#endif
