#include "../ECS/Game.h"
#include <assert.h>
#include <math.h>

#define Vector_2D Line
struct Vector_2D
{
	float origin_x, origin_y;
	float x, y;
};

struct Box
{
	float x, y;
	float width, height;
	float move_x, move_y;
};

enum Collision_Side
{
	COLLISION_NONE,
	COLLISION_LEFT,
	COLLISION_RIGHT,
	COLLISION_TOP,
	COLLISION_BOTTOM
};

SDL_Renderer* renderer;

int lines_intersect(struct Line line_1, struct Line line_2)
{
	float p0_x = line_1.origin_x, p0_y = line_1.origin_y, p1_x = line_1.x, p1_y = line_1.y;
	float p2_x = line_2.origin_x, p2_y = line_2.origin_y, p3_x = line_2.x, p3_y = line_2.y;
	float s1_x, s1_y, s2_x, s2_y;

    s1_x = p1_x - p0_x;
    s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;
    s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        return 1;
    }

    return 0; // No collision
}

int test_collision(struct Box box_1, struct Box box_2, enum Collision_Side side)
{
	struct Line top_1 = { box_1.x, box_1.y, box_1.x + box_1.width, box_1.y };
	struct Line bottom_1 = { box_1.x, box_1.y + box_1.height, box_1.x + box_1.width, box_1.y + box_1.height };
	struct Line left_1 = { box_1.x, box_1.y, box_1.x, box_1.y + box_1.height };
	struct Line right_1 = { box_1.x + box_1.width, box_1.y, box_1.x + box_1.width, box_1.y + box_1.height };

	struct Line top_2 = { box_2.x, box_2.y, box_2.x + box_2.width, box_2.y };
	struct Line bottom_2 = { box_2.x, box_2.y + box_2.height, box_2.x + box_2.width, box_2.y + box_2.height };
	struct Line left_2 = { box_2.x, box_2.y, box_2.x, box_2.y + box_2.height };
	struct Line right_2 = { box_2.x + box_2.width, box_2.y, box_2.x + box_2.width, box_2.y + box_2.height };

	switch(side)
	{
	case COLLISION_TOP:
		if(top_1.origin_x + box_1.move_x < bottom_2.x && top_1.origin_x + box_1.move_x > bottom_2.origin_x)
		{
			float delta_x = bottom_2.x - top_1.origin_x;
			float width = top_1.x - top_1.origin_x;
			float vector_x;
			if(delta_x > width)
			{
				vector_x = top_1.x - 1;
			}
			else
			{
				vector_x = top_1.origin_x + delta_x - 1;
			}

			struct Vector_2D move_vector = { 
				vector_x,
				top_1.origin_y,
				vector_x,
				top_1.origin_y + box_1.move_y
			};

			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawLine(renderer, move_vector.x, move_vector.y, move_vector.origin_x, move_vector.origin_y);
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_RenderDrawLine(renderer, bottom_2.x, bottom_2.y, bottom_2.origin_x, bottom_2.origin_y);

			if(lines_intersect(move_vector, bottom_2))
			{
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderDrawLine(renderer, move_vector.x, move_vector.y, move_vector.origin_x, move_vector.origin_y);
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderDrawLine(renderer, bottom_2.x, bottom_2.y, bottom_2.origin_x, bottom_2.origin_y);
				return 1;
			}
		}
		else if(top_1.x + box_1.move_x < bottom_2.x && top_1.x + box_1.move_x > bottom_2.origin_x)
		{
			float delta_x = top_1.x - bottom_2.x;
			float width = top_1.x - top_1.origin_x;
			float vector_x;
			if(delta_x > width)
			{
				vector_x = top_1.origin_x;
			}
			else
			{
				vector_x = top_1.origin_x - delta_x;
			}

			struct Vector_2D move_vector = { 
				vector_x,
				top_1.origin_y,
				vector_x,
				top_1.origin_y + box_1.move_y
			};

			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawLine(renderer, move_vector.x, move_vector.y, move_vector.origin_x, move_vector.origin_y);
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_RenderDrawLine(renderer, bottom_2.x, bottom_2.y, bottom_2.origin_x, bottom_2.origin_y);

			if(lines_intersect(move_vector, bottom_2))
			{
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderDrawLine(renderer, move_vector.x, move_vector.y, move_vector.origin_x, move_vector.origin_y);
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderDrawLine(renderer, bottom_2.x, bottom_2.y, bottom_2.origin_x, bottom_2.origin_y);
				return 1;
			}
		}
		break;
	case COLLISION_BOTTOM:
		if(bottom_1.origin_x + box_1.move_x < top_2.x && bottom_1.origin_x + box_1.move_x > top_2.origin_x)
		{
			float delta_x = top_2.x - bottom_1.origin_x;
			float width = bottom_1.x - bottom_1.origin_x;
			float vector_x;
			if(delta_x > width)
			{
				vector_x = bottom_1.x;
			}
			else
			{
				vector_x = bottom_1.origin_x + delta_x;
			}

			struct Vector_2D move_vector = { 
				vector_x,
				bottom_1.origin_y,
				vector_x,
				bottom_1.origin_y + box_1.move_y
			};
			if(lines_intersect(move_vector, top_2))
			{
				return 1;
			}
		}
		else if(bottom_1.x + box_1.move_x < top_2.x && bottom_1.x + box_1.move_x > top_2.origin_x)
		{
			float delta_x = bottom_1.x - top_2.x;
			float width = bottom_1.x - bottom_1.origin_x;
			float vector_x;
			if(delta_x > width)
			{
				vector_x = bottom_1.origin_x;
			}
			else
			{
				vector_x = bottom_1.origin_x - delta_x;
			}

			struct Vector_2D move_vector = { 
				vector_x,
				bottom_1.origin_y,
				vector_x,
				bottom_1.origin_y + box_1.move_y
			};
			if(lines_intersect(move_vector, top_2))
			{
				return 1;
			}
		}
		break;
	case COLLISION_LEFT:
		if(left_1.origin_y + box_1.move_y < right_2.y && left_1.origin_y + box_1.move_y > right_2.origin_y)
		{
			float delta_y = right_2.y - left_1.origin_y;
			float height = left_1.y - left_1.origin_y;
			float vector_y;
			if(delta_y > height)
			{
				vector_y = left_1.y;
			}
			else
			{
				vector_y = left_1.origin_y + delta_y;
			}

			struct Vector_2D move_vector = { 
				left_1.origin_x,
				vector_y,
				left_1.x + box_1.move_x,
				vector_y 
			};
			if(lines_intersect(move_vector, right_2))
			{
				return 1;
			}
		}
		else if(bottom_1.x + box_1.move_x < top_2.x && bottom_1.x + box_1.move_x > top_2.origin_x)
		{
			float delta_x = bottom_1.x - top_2.x;
			float width = bottom_1.x - bottom_1.origin_x;
			float vector_x;
			if(delta_x > width)
			{
				vector_x = bottom_1.origin_x;
			}
			else
			{
				vector_x = bottom_1.origin_x - delta_x;
			}

			struct Vector_2D move_vector = { 
				vector_x,
				bottom_1.origin_y,
				vector_x,
				bottom_1.origin_y + box_1.move_y
			};
			if(lines_intersect(move_vector, top_2))
			{
				return 1;
			}
		}
		break;
	case COLLISION_RIGHT:
		break;
	case COLLISION_NONE:
		break;
	}

	return 0;
}


struct Box box_1 = {
	.x = 0.3f, 
	.y = 0.5f, 
	.width = 50.12f, 
	.height = 99.0f,
	.move_x = 0.0f,
	.move_y = 0.0f
};

struct Box box_2 = {
	.x = 400.3f, 
	.y = 200.5f, 
	.width = 100.12f, 
	.height = 20.0f,
	.move_x = 0.0f,
	.move_y = 0.0f
};

#define SPEED 5
void update(struct Scene* scene, struct Game* game)
{
	const Uint8* key_down = game->window.key_state;
	if(key_down[SDL_SCANCODE_W])
	{
		box_1.move_y -= SPEED;
	}
	if(key_down[SDL_SCANCODE_S])
	{
		box_1.move_y += SPEED;
	}
	if(key_down[SDL_SCANCODE_A])
	{
		box_1.move_x -= SPEED;
	}
	if(key_down[SDL_SCANCODE_D])
	{
		box_1.move_x += SPEED;
	}

	if(key_down[SDL_SCANCODE_UP])
	{
		box_2.move_y -= SPEED;
	}
	if(key_down[SDL_SCANCODE_DOWN])
	{
		box_2.move_y += SPEED;
	}
	if(key_down[SDL_SCANCODE_LEFT])
	{
		box_2.move_x -= SPEED;
	}
	if(key_down[SDL_SCANCODE_RIGHT])
	{
		box_2.move_x += SPEED;
	}
	
	SDL_RenderClear(renderer);

	if(test_collision(box_1, box_2, COLLISION_TOP))
	{
		box_1.y = box_2.y + box_2.height + 1;
		box_1.move_y = 0;
	}

	if(test_collision(box_1, box_2, COLLISION_BOTTOM))
	{
		box_1.y = box_2.y - box_1.height - 1;
		box_1.move_y = 0;
	}

	if(test_collision(box_2, box_1, COLLISION_TOP))
	{
		box_2.y = box_1.y + box_1.height + 1;
		box_2.move_y = 0;
	}

	if(test_collision(box_2, box_1, COLLISION_BOTTOM))
	{
		box_2.y = box_1.y - box_2.height - 1;
		box_2.move_y = 0;
	}

	if(test_collision(box_1, box_2, COLLISION_LEFT))
	{
		box_1.x = box_2.x + box_2.width + 1;
		box_1.move_x = 0;
	}

	box_1.x += box_1.move_x;
	box_1.y += box_1.move_y;
	box_1.move_x = 0;
	box_1.move_y = 0;

	box_2.x += box_2.move_x;
	box_2.y += box_2.move_y;
	box_2.move_x = 0;
	box_2.move_y = 0;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &(SDL_Rect){box_1.x, box_1.y, box_1.width, box_1.height});
	SDL_RenderDrawRect(renderer, &(SDL_Rect){box_2.x, box_2.y, box_2.width, box_2.height});
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

int main(void)
{
	struct Game game;
	Game_ctor(&game, 800, 600);

	struct Scene scene = {
		.change = SCENE_CHANGE_NONE,
		.update = update,
	};

	Vec_push_back(&game.scenes, &scene);
	renderer = game.window.renderer;

	Game_start(&game);
	Game_dtor(&game);
}

