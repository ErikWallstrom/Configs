#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <SDL2/SDL.h>
#include "Vec.h"

struct Animation
{
	Vec(SDL_Point) frames;
	size_t selected_frame;
	unsigned delay, time;
};

struct Animation_Component
{
	Vec(struct Animation) animations;
	size_t selected_animation;
	int frame_width, frame_height;
};

#endif
