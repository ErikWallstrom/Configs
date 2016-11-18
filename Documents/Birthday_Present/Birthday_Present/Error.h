#ifndef ERROR_H
#define ERROR_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#define error(msg) \
	do { \
		SDL_ShowSimpleMessageBox( \
			SDL_MESSAGEBOX_ERROR, \
			__func__, \
			msg, \
			NULL \
		); \
		abort(); \
	} while(0)

#endif
