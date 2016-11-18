#ifndef ENTITY_H
#define ENTITY_H

#include "Game.h"
#include "Texture.h"

typedef struct Entity* Entity;
typedef void(*Entity_Behavior)(Entity, Game*);
struct Entity
{
	struct Texture;
	SDL_Rect d_rect;
	Entity_Behavior behavior;
};

struct Entity Entity_init(struct Texture texture, int x, int y, Entity_Behavior behavior);
void Entity_render(Entity entity, Game* game);
void Entity_delete(Entity* entity);

#endif
