#include "Game.h"
#include "Sprite.h"
#include "Button.h"
#include "FPS_Counter.h"

#include <stdlib.h>

#define gc(T) T __attribute__((__cleanup__(T##_dtor)))
#define new(T, ...) T##_ctor(malloc(sizeof(T)), __VA_ARGS__)
#define range(i, v) size_t i = v - 1; i < v; i--

struct Game* game;
struct Texture texture;

Point walk[4] = {
	{0, 0},
	{40, 0},
	{80, 0},
	{120, 0}
};
Point stand[1] = {
	{0, 0}
};
Animation stand_anim;
Animation walk_anim;

void keyboard_behavior(Entity* e)
{
	static int_fast32_t speed = 8;
	if(game->key_state[SDL_SCANCODE_W])
		e->pos.y -= speed;
	if(game->key_state[SDL_SCANCODE_S])
		e->pos.y += speed;
	if(game->key_state[SDL_SCANCODE_A])
		e->pos.x -= speed;
	if(game->key_state[SDL_SCANCODE_D])
		e->pos.x += speed;
}

void animation_behavior(Entity* e)
{
	Sprite* self = (Sprite*)e;
	static int_fast32_t speed = 8;
	int moving = 0;
	if(game->key_state[SDL_SCANCODE_W])
	{
		e->pos.y -= speed;
		self->selected_anim = 1;
		moving = 1;
	}
	if(game->key_state[SDL_SCANCODE_S])
	{
		e->pos.y += speed;
		self->selected_anim = 1;
		moving = 1;
	}
	if(game->key_state[SDL_SCANCODE_A])
	{
		e->pos.x -= speed;
		self->selected_anim = 1;
		self->flip_x = 1;
		moving = 1;
	}
	if(game->key_state[SDL_SCANCODE_D])
	{
		e->pos.x += speed;
		self->selected_anim = 1;
		self->flip_x = 0;
		moving = 1;
	}

	if(!moving)
		self->selected_anim = 0;
	Sprite_update(e);
}

void update(Scene* self, Entity* entity)
{
	if(entity->name == BUTTON_NAME)
	{
		Button* button = (Button*)entity;
		if(button->mouse_down)
		{
			Sprite* sprite = new(Sprite,
					&texture, 
					REG_POINT_CENTER, 
					(Point){
						rand() % 800, 
						rand() % 600
					}, 
					texture.width / 6, 
					texture.height);

			sprite->behavior = animation_behavior;
			Sprite_add(sprite, stand_anim);
			Sprite_add(sprite, walk_anim);

			Scene_add(self, (struct Entity*)sprite);
			button->presses = 0;
		}
	}
	else if(entity->name == LABEL_NAME)
	{
		static char buffer[sizeof(int) * 8 + 2 + 9] = "Objects: ";
		SDL_itoa(self->content.size, buffer + 9, 10);

		Label_set_text((Label*)entity, buffer);
		SDL_SetTextureColorMod(entity->texture->raw, 80, 80, 255);
	}
}

void test(Scene* self)
{
	(void)self;
	if(game->key_state[SDL_SCANCODE_Q])
		game->done = 1;
	if(game->key_state[SDL_SCANCODE_SPACE])
	{
		SDL_SetTextureColorMod(
				texture.raw, 
				rand() % 255, 
				rand() % 255, 
				rand() % 255);
	}
}

void clean_up(Scene* self)
{
	for(size_t i = self->content.size - 1; i > 2; i--)
	{
		Sprite* sprite = (Sprite*)self->content.buffer[i];
		Sprite_dtor(sprite);
		free(sprite);
	}
}

int main(void)
{
	gc(Game) l_game;
	Game_ctor(&l_game, 800, 600);
	game = &l_game;

	gc(Scene) main_menu;
	Scene_ctor(&main_menu, update, test, clean_up);
	Game_add(game, &main_menu);

	Texture_from_image(&texture, game->renderer, "./Player.png");
	TTF_Font* font = TTF_OpenFont("Roboto-Regular.ttf", 18);

	gc(FPS_Counter) counter;
	FPS_Counter_ctor(
			&counter, 
			REG_POINT_TOP_LEFT, 
			(Point){game->width - 75, 25}, 
			font);

	gc(Button) button;
	Button_ctor(
			&button, 
			REG_POINT_CENTER,
			(Point){50, 50},
			font, 
			"Click me!");

	gc(Label) label;
	Label_ctor(
			&label, 
			REG_POINT_CENTER, 
			(Point){game->width / 2, 
			game->height / 2}, 
			font, 
			"Objects", 
			NULL);

	Animation_ctor(&walk_anim, 100, walk, 4);
	Animation_ctor(&stand_anim, 100, stand, 1);

	Scene_add(&main_menu, (Entity*)&counter);
	Scene_add(&main_menu, (Entity*)&button);
	Scene_add(&main_menu, (Entity*)&label);

	while(!game->done)
	{
		Game_update(game);
	}

	TTF_CloseFont(font);
	Texture_dtor(&texture);
	Animation_dtor(&walk_anim);
	Animation_dtor(&stand_anim);
}

