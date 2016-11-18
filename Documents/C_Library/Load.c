#include "Load.h"
#include "Button.h"
#include "Sprite.h"
#include <assert.h>

static Scene main_scene;
static Scene game_scene;

void main_scene_behavior(Scene self, Game* game)
{
	for_each(self->content, i)
	{
		Button btn = self->content[i];
		if(btn->presses)
		{
			if(!strcmp(btn->label, "Play"))
			{
				push(game->scenes, game_scene);
				btn->presses = 0;
			}
			else if(!strcmp(btn->label, "Quit"))
				game->done = 1;
		}
	}
}

void main_scene_clean_up(Scene scene)
{
	for_each(scene->content, i)
	{
		Button btn = scene->content[i];
		Button_delete(&btn);
	}
}

Scene load_main_scene(Game* game)
{
	assert(game);
	main_scene = new(
		Scene_init(
			main_scene_behavior,
			main_scene_clean_up));
	TTF_Font* font = TTF_OpenFont("Roboto-Regular.ttf", 24);
	if(!font)
		debug(TTF_GetError());

	Button buttons[] = {
		new(Button_init(
			Entity_init(
				Texture_from_font(
					game->renderer, 
					font, 
					"Play"),
				game->width / 2, 0,
				Button_behavior),
			"Play")),
		new(Button_init(
			Entity_init(
				Texture_from_font(
					game->renderer, 
					font, 
					"Quit"),
				game->width / 2, 0,
				Button_behavior),
			"Quit"))
	};

	for(size_t i = 0; i < sizeof(buttons) / sizeof(*buttons); i++)
	{
		buttons[i]->d_rect.y = i * 50 + 200;
		push(main_scene->content, buttons[i]);
	}
	
	TTF_CloseFont(font);
	return main_scene;
}

void game_scene_behavior(Scene self, Game* game)
{
	int offset_x = 0, offset_y = 0;
	int speed = 6;
	
	if(game->key_state[SDL_SCANCODE_W])
		offset_y -= speed;
	if(game->key_state[SDL_SCANCODE_S])
		offset_y += speed;
	if(game->key_state[SDL_SCANCODE_A])
		offset_x -= speed;
	if(game->key_state[SDL_SCANCODE_D])
		offset_x += speed;
	if(game->key_state[SDL_SCANCODE_ESCAPE])
		pop(game->scenes);

	for_each(self->content, i)
	{
		Entity e = self->content[i];
		e->d_rect.x += offset_x;
		e->d_rect.y += offset_y;
	}
}

void game_scene_clean_up(Scene scene)
{
	for_each(scene->content, i)
	{
		Button btn = scene->content[i];
		Button_delete(&btn);
	}
}

Scene load_game_scene(Game* game)
{
	assert(game);
	game_scene = new(
		Scene_init(
			game_scene_behavior,
			game_scene_clean_up));
	TTF_Font* font = TTF_OpenFont("Roboto-Regular.ttf", 24);
	if(!font)
		debug(TTF_GetError());

	Button btn = new(Button_init(
		Entity_init(
			Texture_from_font(
				game->renderer,
				font,
				"You are now in-game!"),
			game->width / 2,
			game->height / 2,
			NULL),
		"You are now in-game!"));

	Sprite sprite = new(((struct Sprite){
		Entity_init(
			Texture_from_image(
				game->renderer,
				"Player.png"),
			120, 120,
			Sprite_behavior),
		dynamic(((struct Animation[]){
			{
				.delay = 100,
				.selected_frame = 0,
				.frames = dynamic(((SDL_Rect[]){
					{120, 0, 40, 50},
					{80, 0, 40, 50},
					{40, 0, 40, 50},
					{0, 0, 40, 50}
				}))
			}
		})), 0
	}));
	sprite->d_rect.w = 40;
	sprite->d_rect.h = 50;
	
	push(game_scene->content, btn);
	push(game_scene->content, sprite);
	TTF_CloseFont(font);
	return game_scene;
}

