#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"

typedef struct Button Button;
extern const char* const BUTTON_NAME;
struct Button
{
	struct Label;
	int pressed;
	int mouse_down;
};

struct Button* Button_ctor(struct Button* self, enum Reg_Point r_point, struct Point pos, TTF_Font* font, char* text);
void Button_update(struct Entity* e);
void Button_dtor(struct Button* self);

#endif
