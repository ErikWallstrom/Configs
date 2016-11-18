#include "Collision_Component.h"
#include <assert.h>

struct Collision_Component* Collision_Component_ctor(
		struct Collision_Component* self, 
		struct Hit_Box hit_box)
{
	assert(self);
	self->hit_box = hit_box;
	Vec_ctor(&self->collisions, sizeof(struct Collision_Info), 0);

	return self;
}
