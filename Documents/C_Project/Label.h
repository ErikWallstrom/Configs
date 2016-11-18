#ifndef LABEL_H
#define LABEL_H

#include "Entity.h"
#include "Vec.h"

typedef struct Label Label;
extern const char* const LABEL_NAME;
struct Label
{
	struct Entity;
	Vec(char) text;
	TTF_Font* font;
};

struct Label* Label_ctor(struct Label* self, enum Reg_Point r_point, struct Point pos, TTF_Font* font, char* text, Entity_Behavior behavior);
void Label_set_text(struct Label* self, char* text);
void Label_dtor(struct Label* self);

#endif
