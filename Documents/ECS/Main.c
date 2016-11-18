#include "Game.h"
#include "ECS.h"
#include "Error.h"

#define blyad(sasdc) x

struct ECS ecs;

void update(struct Scene* self, struct Game* game)
{
	handle_key_controls(&ecs, game->window.key_state);
	check_collisions(&ecs);
	handle_collisions(&ecs);
	handle_movements(&ecs);
	handle_rendering(&ecs, game->window.renderer);
}

int main(void)
{
	struct Game game;
	Game_ctor(&game, 800, 600);

	ECS_ctor(&ecs);
	Entity e = Entity_new(&ecs);
	ecs.masks.buffer[e] = COMPONENT_POSITION | 
			COMPONENT_TEXTURE | 
			COMPONENT_MOVEMENT | 
			COMPONENT_COLLISION |
			COMPONENT_KEY_CONTROL;
	ecs.positions.buffer[e] = (struct Position_Component){
		.r_point = REG_POINT_BOTTOM_RIGHT, 
		.x = game.window.width, 
		.y = game.window.height
	};
	Texture_Component_from_image(
			&ecs.textures.buffer[e], 
			game.window.renderer, 
			"Ground.png");
	ecs.movements.buffer[e] = (struct Movement_Component){
		.x_movement = 0, 
		.y_movement = 0,
		.speed = 1
	};
	ecs.key_controls.buffer[e] = (struct Key_Control_Component){
		.move_up = SDL_SCANCODE_W,
		.move_down = SDL_SCANCODE_S,
		.move_left = SDL_SCANCODE_A,
		.move_right = SDL_SCANCODE_D
	};
	Collision_Component_ctor(
			&ecs.collisions.buffer[e], 
			(struct Hit_Box){
				ecs.textures.buffer[e].width,
				ecs.textures.buffer[e].height,
			});

	e = Entity_new(&ecs);
	ecs.masks.buffer[e] = COMPONENT_POSITION | 
			COMPONENT_TEXTURE | 
			COMPONENT_MOVEMENT | 
			COMPONENT_COLLISION | 
			COMPONENT_KEY_CONTROL;
	ecs.positions.buffer[e] = (struct Position_Component){
		.r_point = REG_POINT_TOP_LEFT, 
		.x = 0, 
		.y = 0
	};
	Texture_Component_from_image(&ecs.textures.buffer[e], game.window.renderer, "Ground.png");
	ecs.movements.buffer[e] = (struct Movement_Component){
		.x_movement = 0, 
		.y_movement = 0,
		.speed = 5
	};
	ecs.key_controls.buffer[e] = (struct Key_Control_Component){
		.move_up = SDL_SCANCODE_UP,
		.move_down = SDL_SCANCODE_DOWN,
		.move_left = SDL_SCANCODE_LEFT,
		.move_right = SDL_SCANCODE_RIGHT
	};
	Collision_Component_ctor(
			&ecs.collisions.buffer[e], 
			(struct Hit_Box){
				ecs.textures.buffer[e].width,
				ecs.textures.buffer[e].height,
			});

	e = Entity_new(&ecs);
	ecs.masks.buffer[e] = COMPONENT_POSITION | 
			COMPONENT_TEXTURE | 
			COMPONENT_MOVEMENT | 
			COMPONENT_COLLISION | 
			COMPONENT_KEY_CONTROL;
	ecs.positions.buffer[e] = (struct Position_Component){
		.r_point = REG_POINT_TOP_RIGHT, 
		.x = game.window.width, 
		.y = 0
	};
	Texture_Component_from_image(
			&ecs.textures.buffer[e], 
			game.window.renderer, "Ground.png");
	ecs.movements.buffer[e] = (struct Movement_Component){
		.x_movement = 0, 
		.y_movement = 0,
		.speed = 5
	};
	ecs.key_controls.buffer[e] = (struct Key_Control_Component){
		.move_up = SDL_SCANCODE_K,
		.move_down = SDL_SCANCODE_J,
		.move_left = SDL_SCANCODE_H,
		.move_right = SDL_SCANCODE_L
	};
	Collision_Component_ctor(
			&ecs.collisions.buffer[e], 
			(struct Hit_Box){
				ecs.textures.buffer[e].width,
				ecs.textures.buffer[e].height,
			});


	Vec_push(&game.scenes, &(struct Scene){ update, SCENE_CHANGE_NONE });
	Game_start(&game);

	ECS_dtor(&ecs);
	Game_dtor(&game);
}
