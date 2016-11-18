#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Array.h"

typedef struct
{
	int done;
	int width, height;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Uint32 mouse_state;
	int mouse_x, mouse_y;
	const Uint8* key_state;

	Array scenes;
} Game;

Game Game_new(int width, int height);
void Game_update(Game* game);
void Game_delete(Game* game);

#endif
