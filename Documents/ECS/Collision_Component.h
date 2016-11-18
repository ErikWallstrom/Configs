#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Reg_Point.h"
#include "Vec.h"

typedef size_t Entity;

enum Collision_Type
{
	COLLISION_UNDEFINED,
	COLLISION_TOP,
	COLLISION_BOTTOM,
	COLLISION_LEFT,
	COLLISION_RIGHT
};

struct Collision_Info
{
	Entity entity;
	enum Collision_Type type;
};

struct Hit_Box
{
	int width;
	int height;
};

struct Collision_Component
{
	struct Hit_Box hit_box;
	Vec(struct Collision_Info) collisions;
};

struct Collision_Component* Collision_Component_ctor(
		struct Collision_Component* self, 
		struct Hit_Box hit_box);

#endif
