#ifndef ECS_H
#define ECS_H

#include "Key_Control_Component.h"
#include "Animation_Component.h"
#include "Collision_Component.h"
#include "Movement_Component.h"
#include "Position_Component.h"
#include "Texture_Component.h"
#include "Vec.h"
#include <SDL2/SDL.h>

typedef size_t Entity;

enum Component_Type
{
	COMPONENT_NONE,
	COMPONENT_TEXTURE = 1 << 0,
	COMPONENT_POSITION = 1 << 1,
	COMPONENT_MOVEMENT = 1 << 2,
	COMPONENT_COLLISION = 1 << 3,
	COMPONENT_KEY_CONTROL = 1 << 4,
};

struct ECS
{
	Vec(int) masks;
	Vec(struct Texture_Component) textures;
	Vec(struct Position_Component) positions;
	Vec(struct Movement_Component) movements;
	Vec(struct Collision_Component) collisions;
	Vec(struct Key_Control_Component) key_controls;
};

struct ECS* ECS_ctor(struct ECS* self);
void ECS_dtor(struct ECS* self);
Entity Entity_new(struct ECS* self);

void handle_rendering(struct ECS* self, SDL_Renderer* renderer);
void handle_movements(struct ECS* self);
void check_collisions(struct ECS* self);
void handle_collisions(struct ECS* self);
void handle_key_controls(struct ECS* self, const Uint8* key_state);

#endif
