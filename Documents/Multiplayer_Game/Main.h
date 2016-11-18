#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Vec.h"

#define Game_error(msg) \
	do { \
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", msg, NULL); \
		abort(); \
	} while(0)

enum Properties
{
	WINDOW_WIDTH = 800,
	WINDOW_HEIGHT = 600,
	PLAYER_WIDTH = 80,
	PLAYER_HEIGHT = 50,
};

struct Wall
{
	int x, y;
};

struct Player
{
	float x, y;
};

struct Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	Vec(struct Wall) walls;
	struct Player player;
	struct Player enemy;

	SDL_Texture* wall_tex;
	SDL_Texture* char_tex;
} game;

