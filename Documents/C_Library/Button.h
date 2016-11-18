#ifndef BUTTON_H
#define BUTTON_H

#include "Entity.h"
#include "String.h"

typedef struct Button* Button;
struct Button
{
	struct Entity;
	int presses;
	int mouse_down;
	String label;
};

struct Button Button_init(struct Entity entity, char* label);
void Button_behavior(Entity entity, Game* game);
void Button_delete(Button* button);

#endif
