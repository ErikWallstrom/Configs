#ifndef SPRITE_H
#define SPRITE_H

#include "Animation.h"
#include "Entity.h"

#define Sprite_add(self, anim) Vec_push_back(&(self)->animations, anim)

extern const char* const SPRITE_NAME;
typedef struct Sprite Sprite;
struct Sprite
{
	struct Entity;
	Vec(struct Animation) animations;
	size_t selected_anim;
};

struct Sprite* Sprite_ctor(struct Sprite* self, struct Texture* texture, enum Reg_Point r_point, struct Point pos, int width, int height);
void Sprite_update(struct Entity* e);
void Sprite_dtor(struct Sprite* self);

#endif
