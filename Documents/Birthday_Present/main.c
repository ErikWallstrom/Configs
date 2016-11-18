#include "Texture.h"
#include "Game.h"

#define true 1
#define false 0

struct Item
{
	struct Texture* texture;
	int good;
};
Vec(struct Item) items;

struct Object
{
	struct Item item;
	int lane;
	int y;
};
Vec(struct Object) objects;

struct Line 
{
	int y;
	int tree;
	int tree_offset;
};
Vec(struct Line) lines;
struct Texture* tree;

struct Player
{
	struct Texture* texture;
	int lane;
};
struct Player player;

void update(struct Scene* self, struct Game* game, void* data)
{
	SDL_Renderer* renderer = game->window->renderer;
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderFillRect( 
		renderer, 
		&(SDL_Rect){
			game->window->width / 6,
			0,
			game->window->width - game->window->width / 3,
			game->window->height
		}
	);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(
		renderer,
		&(SDL_Rect){
			game->window->width / 6,
			0,
			10,
			game->window->height
		}
	);
	SDL_RenderFillRect(
		renderer,
		&(SDL_Rect){
			game->window->width - game->window->width / 6 - 10,
			0,
			10,
			game->window->height
		}
	);

	static long last_time = 0;
	long current_time = SDL_GetTicks();
	if(current_time / 1000 > last_time)
	{
		last_time = current_time / 1000;
		struct Line line;
		if((rand() % 10) <= 3)
		{
			line.tree_offset = rand() % 150 + 60;
			line.tree = 1;
		}
		else
			line.tree = 0;
		line.y = -100;
		Vec_push_back(&lines, line);
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for(size_t j = Vector(&lines).size; j > 0; j--)
	{
		int i = j - 1;
		SDL_RenderFillRect(
			renderer,
			&(SDL_Rect){
				game->window->width / 6 + ((game->window->width - game->window->width / 3) / 3),
				lines[i].y,
				10,
				100
			}
		);
		SDL_RenderFillRect(
			renderer,
			&(SDL_Rect){
				game->window->width / 6 + ((game->window->width - game->window->width / 3) / 3) * 2,
				lines[i].y,
				10,
				100
			}
		);
		if(lines[i].tree)
		{
			SDL_RenderCopy(
				renderer,
				tree->raw,
				NULL,
				&(SDL_Rect){
					35,
					lines[i].y - lines[i].tree_offset,
					tree->width,
					tree->height
				}
			);
			SDL_RenderCopy(
				renderer,
				tree->raw,
				NULL,
				&(SDL_Rect){
					game->window->width - tree->width - 35,
					lines[i].y - (lines[i].tree_offset * 3),
					tree->width,
					tree->height
				}
			);
		}


		lines[i].y += 5;
		if(lines[i].y > game->window->height + 300)
			Vec_collapse(&lines, i, 1);
	}

	for(size_t i = 0; i < Vector(&game->window->events).size; i++)
	{
		if(game->window->events[i].type == SDL_KEYDOWN)
		{
			switch(game->window->events[i].key.keysym.sym)
			{
			case SDLK_LEFT:
				if(player.lane > 1)
					player.lane--;
				break;
			case SDLK_RIGHT:
				if(player.lane < 5)
					player.lane++;
				break;
			default:;
			}
		}
	}

	SDL_RenderCopy(
		renderer,
		player.texture->raw,
		NULL,
		&(SDL_Rect){
			player.lane * (game->window->width / 6) - 60,
			game->window->height - game->window->height / 10 - 200,
			120,
			200
		}
	);

	static long last_time_1 = 0;
	long current_time_1 = SDL_GetTicks();
	long t = current_time_1 / (rand() % 200 + 1000);
	if(t > last_time_1)
	{
		int sel_item = rand() % Vector(&items).size;
		Vec_push_back(&objects, (struct Object){
			.item = items[sel_item],
			.lane = rand() % 3 + 2,
			.y = -100
		});

		last_time_1 = t;
	}

	for(size_t j = Vector(&objects).size; j > 0; j--)
	{
		int i = j - 1;
		objects[i].y += 4;
		SDL_RenderCopy(
			renderer,
			objects[i].item.texture->raw,
			NULL,
			&(SDL_Rect){
				objects[i].lane * (game->window->width / 6) - 90,
				objects[i].y,
				180,
				180
			}
		);

		if(SDL_HasIntersection(
				&(SDL_Rect){
					player.lane * (game->window->width / 6) - 60,
					game->window->height - game->window->height / 10 - 200,
					120,
					200
				}, 
				&(SDL_Rect){
					objects[i].lane * (game->window->width / 6) - 90,
					objects[i].y,
					180,
					180
				}
			)
		)
		{
			Vec_collapse(&objects, i, 1);
		}
	}

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
}

int main(void) 
{
	struct Game* game = Game_ctor(700, 900);
	Game_add(
		game, 
		&(struct Scene){
			.change = SCENE_CHANGE_NONE,
			.update = update
		}
	);

	tree = Texture_from_image(game->window->renderer, "tree.png");
	player.texture = Texture_from_image(game->window->renderer, "car.png");
	player.lane = 3;

	objects = Vec_ctor(sizeof(struct Object), 0);
	items = Vec_ctor(sizeof(struct Item), 0);
	lines = Vec_ctor(sizeof(struct Line), 0);
	Vec_push_back(
		&items, 
		(struct Item){
			Texture_from_image(game->window->renderer, "oliver.png"),
			false,
		}
	);
	Vec_push_back(
		&items, 
		(struct Item){
			Texture_from_image(game->window->renderer, "te.png"),
			false,
		}
	);
	Vec_push_back(
		&items, 
		(struct Item){
			Texture_from_image(game->window->renderer, "chili.png"),
			false,
		}
	);
	Vec_push_back(
		&items, 
		(struct Item){
			Texture_from_image(game->window->renderer, "potatis.png"),
			true,
		}
	);
	Vec_push_back(
		&items, 
		(struct Item){
			Texture_from_image(game->window->renderer, "sill.png"),
			true,
		}
	);
	Vec_push_back(
		&items, 
		(struct Item){
			Texture_from_image(game->window->renderer, "ost.png"),
			true,
		}
	);

	SDL_SetWindowFullscreen(game->window->raw, SDL_WINDOW_FULLSCREEN_DESKTOP);
	Game_start(game, NULL);
	Game_dtor(game);
}
