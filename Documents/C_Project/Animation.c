#include "Animation.h"
#include <assert.h>

struct Animation* Animation_ctor(struct Animation* self, unsigned delay, struct Point* data, size_t num_frames)
{
	assert(self);
	assert(data);
	assert(num_frames);

	self->selected_frame = 0;
	self->delay = delay;
	self->time = 0;

	Vec_ctor(&self->frames, sizeof(struct Point), num_frames);
	Vec_set(&self->frames, data, num_frames);
	return self;
}

void Animation_dtor(struct Animation* self)
{
	assert(self);
	Vec_dtor(&self->frames);
}
