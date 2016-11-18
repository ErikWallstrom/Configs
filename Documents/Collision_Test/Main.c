#include "../ECS/Game.h"
#include "collisions.h"
#include <math.h>

struct Object
{
	int x, y;
	int w, h;
	int move_x, move_y;
};

struct Object rects[2] = {
	{0, 0, 20, 60, 0, 0},
	{50, 60, 40, 40, 0, 0}
};

void handle_collisions()
{
	if(rect_collided_left(
				rects[1].x, 
				rects[1].y, 
				rects[1].w, 
				rects[1].h, 
				rects[1].move_x, 
				rects[1].move_y,
				rects->x, 
				rects->y, 
				rects->w, 
				rects->h, 
				rects->move_x, 
				rects->move_y))
	{
		puts("COLLIDED LEFT 2");
	}
	if(rect_collided_right(
				rects[1].x, 
				rects[1].y, 
				rects[1].w, 
				rects[1].h, 
				rects[1].move_x, 
				rects[1].move_y,
				rects->x, 
				rects->y, 
				rects->w, 
				rects->h, 
				rects->move_x, 
				rects->move_y))
	{
		puts("COLLIDED RIGHT 2");
	}

	if(rect_collided_bottom(
				rects[1].x, 
				rects[1].y, 
				rects[1].w, 
				rects[1].h, 
				rects[1].move_x, 
				rects[1].move_y,
				rects->x, 
				rects->y, 
				rects->w, 
				rects->h, 
				rects->move_x, 
				rects->move_y))
	{
		puts("COLLIDED BOTTOM 2");
	}

	if(rect_collided_top(
				rects[1].x, 
				rects[1].y, 
				rects[1].w, 
				rects[1].h, 
				rects[1].move_x, 
				rects[1].move_y,
				rects->x, 
				rects->y, 
				rects->w, 
				rects->h, 
				rects->move_x, 
				rects->move_y))
	{
		puts("COLLIDED TOP 2");
	}
	if(rect_collided_left(
				rects->x, 
				rects->y, 
				rects->w, 
				rects->h, 
				rects->move_x, 
				rects->move_y,
				rects[1].x, 
				rects[1].y, 
				rects[1].w, 
				rects[1].h, 
				rects[1].move_x, 
				rects[1].move_y))
	{
		puts("COLLIDED LEFT 1");
	}

	if(rect_collided_right(
				rects->x, 
				rects->y, 
				rects->w, 
				rects->h, 
				rects->move_x, 
				rects->move_y,
				rects[1].x, 
				rects[1].y, 
				rects[1].w, 
				rects[1].h, 
				rects[1].move_x, 
				rects[1].move_y))
	{
		puts("COLLIDED RIGHT 1");
	}

	if(rect_collided_top(
				rects->x, 
				rects->y, 
				rects->w, 
				rects->h, 
				rects->move_x, 
				rects->move_y,
				rects[1].x, 
				rects[1].y, 
				rects[1].w, 
				rects[1].h, 
				rects[1].move_x, 
				rects[1].move_y))
	{
		puts("COLLIDED TOP 1");
	}

	if(rect_collided_bottom(
				rects->x, 
				rects->y, 
				rects->w, 
				rects->h, 
				rects->move_x, 
				rects->move_y,
				rects[1].x, 
				rects[1].y, 
				rects[1].w, 
				rects[1].h, 
				rects[1].move_x, 
				rects[1].move_y))
	{
		puts("COLLIDED BOTTOM 1");
	}
}

#define SPEED 1
void update(struct Scene* scene, struct Game* game)
{
	SDL_Renderer* renderer = game->window.renderer;
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, (SDL_Rect*)&rects[0]);
	SDL_RenderDrawRect(renderer, (SDL_Rect*)&rects[1]);

	const Uint8* key_state = game->window.key_state;
	if(key_state[SDL_SCANCODE_W])
		rects[0].move_y = -SPEED;
	if(key_state[SDL_SCANCODE_S])
		rects[0].move_y = SPEED;
	if(key_state[SDL_SCANCODE_A])
		rects[0].move_x = -SPEED;
	if(key_state[SDL_SCANCODE_D])
		rects[0].move_x = SPEED;

	if(key_state[SDL_SCANCODE_UP])
		rects[1].move_y = -SPEED;
	if(key_state[SDL_SCANCODE_DOWN])
		rects[1].move_y = SPEED;
	if(key_state[SDL_SCANCODE_LEFT])
		rects[1].move_x = -SPEED;
	if(key_state[SDL_SCANCODE_RIGHT])
		rects[1].move_x = SPEED;

	handle_collisions();

	rects[0].x += rects[0].move_x;
	rects[1].x += rects[1].move_x;
	rects[0].y += rects[0].move_y;
	rects[1].y += rects[1].move_y;

	rects[0].move_x = 0;
	rects[0].move_y = 0;
	rects[1].move_x = 0;
	rects[1].move_y = 0;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

int main(void)
{
	struct Game game;
	Game_ctor(&game, 800, 600);
	Game_add(&game, &(struct Scene){
			.change = SCENE_CHANGE_NONE,
			.update = update});

	SDL_RenderSetScale(game.window.renderer, 5.f, 5.f);

	Game_start(&game);
	Game_dtor(&game);
}
