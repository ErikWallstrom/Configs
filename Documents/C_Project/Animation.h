#ifndef ANIMATION_H
#define ANIMATION_H

#include "Vec.h"
#include "Point.h"

typedef struct Animation Animation;
struct Animation
{
	Vec(struct Point) frames;
	size_t selected_frame;
	unsigned delay, time;
};

struct Animation* Animation_ctor(struct Animation* self, unsigned delay, struct Point* data, size_t num_frames);
void Animation_dtor(struct Animation* self);

#endif
