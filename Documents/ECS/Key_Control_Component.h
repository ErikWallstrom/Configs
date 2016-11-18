#ifndef KEY_CONTROL_COMPONENT_H
#define KEY_CONTROL_COMPONENT_H

#include <SDL2/SDL.h>

struct Key_Control_Component
{
	SDL_Scancode move_up;
	SDL_Scancode move_down;
	SDL_Scancode move_left;
	SDL_Scancode move_right;
};

#endif
