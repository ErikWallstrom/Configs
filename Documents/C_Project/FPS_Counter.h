#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include "Label.h"

typedef struct FPS_Counter FPS_Counter;
extern const char* const FPS_COUNTER_NAME;
struct FPS_Counter
{
	struct Label;
	Uint32 time;
	Uint32 frames;
};

struct FPS_Counter* FPS_Counter_ctor(struct FPS_Counter* self, enum Reg_Point r_point, struct Point pos, TTF_Font* font);
void FPS_Counter_update(struct Entity* e);
void FPS_Counter_dtor(struct FPS_Counter* self);

#endif
