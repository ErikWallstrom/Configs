#ifndef SPRITE_H
#define SPRITE_H

#include "Entity.h"

typedef struct Animation* Animation;
struct Animation
{
	unsigned delay, time;
	Array frames;
	size_t selected_frame;
};

typedef struct Sprite* Sprite;
struct Sprite
{
	struct Entity;
	Array animations;
	size_t selected_animation;
};

void Sprite_behavior(Entity entity, Game* game);

#endif
