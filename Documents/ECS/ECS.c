#include "ECS.h"
#include <math.h>
#include <assert.h>

struct ECS* ECS_ctor(struct ECS* self)
{
	assert(self);

	Vec_ctor(&self->masks, sizeof(int), 0);
	Vec_ctor(&self->textures, sizeof(struct Texture_Component), 0);
	Vec_ctor(&self->movements, sizeof(struct Movement_Component), 0);
	Vec_ctor(&self->positions, sizeof(struct Position_Component), 0);
	Vec_ctor(&self->collisions, sizeof(struct Collision_Component), 0);
	Vec_ctor(&self->key_controls, sizeof(struct Key_Control_Component), 0);
	return self;
}

void ECS_dtor(struct ECS* self)
{
	assert(self);
	Vec_dtor(&self->masks);
	Vec_dtor(&self->textures);
	Vec_dtor(&self->movements);
	Vec_dtor(&self->positions);
	Vec_dtor(&self->collisions);
	Vec_dtor(&self->key_controls);
}

Entity Entity_new(struct ECS* self)
{
	assert(self);
	Vec_make_space(&self->masks, self->masks.size, 1);
	Vec_make_space(&self->movements, self->movements.size, 1);
	Vec_make_space(&self->textures, self->textures.size, 1);
	Vec_make_space(&self->collisions, self->collisions.size, 1);
	Vec_make_space(&self->positions, self->positions.size, 1);
	Vec_make_space(&self->key_controls, self->key_controls.size, 1);

	Entity e = self->masks.size - 1;
	self->masks.buffer[e] = 0;
	self->movements.buffer[e] = (struct Movement_Component){0};
	self->textures.buffer[e] = (struct Texture_Component){0};
	self->collisions.buffer[e] = (struct Collision_Component){0};
	self->positions.buffer[e] = (struct Position_Component){0};
	self->key_controls.buffer[e] = (struct Key_Control_Component){0};
	
	return e;
}

#define RENDER_MASK (COMPONENT_TEXTURE | COMPONENT_POSITION)
void handle_rendering(struct ECS* self, SDL_Renderer* renderer)
{
	assert(self);
	assert(renderer);
	for(size_t i = 0; i < self->masks.size; i++)
	{
		if((self->masks.buffer[i] & RENDER_MASK) == RENDER_MASK)
		{
			SDL_Rect d_rect = {
				self->positions.buffer[i].x,
				self->positions.buffer[i].y,
				self->textures.buffer[i].width,
				self->textures.buffer[i].height
			};

			get_point(self->positions.buffer[i].r_point, &d_rect);
			SDL_RenderCopy(
					renderer, 
					self->textures.buffer[i].texture, 
					&(SDL_Rect){
						0,
						0,
						self->textures.buffer[i].width,
						self->textures.buffer[i].height
					},
					&d_rect);
			if((self->masks.buffer[i] & COMPONENT_COLLISION) == COMPONENT_COLLISION)
			{
				SDL_Rect rect = {
					self->positions.buffer[i].x,
					self->positions.buffer[i].y,
					self->collisions.buffer[i].hit_box.width,
					self->collisions.buffer[i].hit_box.height,
				};
				get_point(self->positions.buffer[i].r_point, &rect);
				SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
				SDL_RenderDrawRect(renderer, &rect);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
		}
	}
}

#define MOVEMENT_MASK (COMPONENT_MOVEMENT | COMPONENT_POSITION)
void handle_movements(struct ECS* self)
{
	assert(self);
	for(size_t i = 0; i < self->masks.size; i++)
	{
		if((self->masks.buffer[i] & MOVEMENT_MASK) == MOVEMENT_MASK)
		{
			self->positions.buffer[i].x += self->movements.buffer[i].x_movement;
			self->positions.buffer[i].y += self->movements.buffer[i].y_movement;

			self->movements.buffer[i].x_movement = 0.f;
			self->movements.buffer[i].y_movement = 0.f;
		}
	}
}

#define COLLISION_MASK (COMPONENT_POSITION | COMPONENT_COLLISION | COMPONENT_MOVEMENT)
void check_collisions(struct ECS* self)
{
	assert(self);
	for(size_t i = 0; i < self->masks.size; i++)
	{
		if((self->masks.buffer[i] & COLLISION_MASK) == COLLISION_MASK)
		{
			SDL_Rect rect_1 = {
				self->positions.buffer[i].x + self->movements.buffer[i].x_movement,
				self->positions.buffer[i].y + self->movements.buffer[i].y_movement,
				self->collisions.buffer[i].hit_box.width,
				self->collisions.buffer[i].hit_box.height,
			};
			get_point(self->positions.buffer[i].r_point, &rect_1);
			SDL_Point old_pos = {
				rect_1.x - self->movements.buffer[i].x_movement,
				rect_1.y - self->movements.buffer[i].y_movement
			};
		
			for(size_t j = 0; j < self->masks.size; j++)
			{
				if(j == i)
					continue;

				if((self->masks.buffer[j] & (COLLISION_MASK & ~COMPONENT_MOVEMENT)) == 
					(COLLISION_MASK & ~COMPONENT_MOVEMENT))
				{
					SDL_Rect rect_2 = {
						self->positions.buffer[j].x,
						self->positions.buffer[j].y,
						self->collisions.buffer[j].hit_box.width,
						self->collisions.buffer[j].hit_box.height,
					};
					get_point(self->positions.buffer[j].r_point, &rect_2);
					
					if(SDL_HasIntersection(&rect_1, &rect_2))
					{
						struct Collision_Info info;
						info.entity = j;
							
						if(old_pos.x + rect_1.w <= rect_2.x && 
							rect_1.x + rect_1.w > rect_2.x)
						{
							info.type = COLLISION_RIGHT;
						}
						else if(old_pos.x >= rect_2.x + rect_2.w &&
							rect_1.x < rect_2.x + rect_2.w)
						{
							info.type = COLLISION_LEFT;
						}
						else if(old_pos.y >= rect_2.y + rect_2.h &&
							rect_1.y < rect_2.y + rect_2.h)
						{
							info.type = COLLISION_TOP;
						}
						else if(old_pos.y + rect_1.h <= rect_2.y &&
							rect_1.y + rect_1.h > rect_2.y)
						{
							info.type = COLLISION_BOTTOM;
						}
						else
						{
							SDL_Rect result;
							SDL_IntersectRect(&rect_1, &rect_2, &result);
							if(result.w > result.h)
							{
								if(result.y > rect_2.y + rect_2.h / 2)
								{
									info.type = COLLISION_TOP;
								}
								else
								{
									info.type = COLLISION_BOTTOM;
								}
							}
							else
							{
								if(result.x > rect_2.x + rect_2.w / 2)
								{
									info.type = COLLISION_LEFT;
								}
								else
								{
									info.type = COLLISION_RIGHT;
								}
							}
						}
						
						Vec_push_back(&self->collisions.buffer[i].collisions, info);
					}
				}
			}
		}
	}
}

void handle_collisions(struct ECS* self)
{
	assert(self);
	for(size_t i = 0; i < self->masks.size; i++)
	{
		if((self->masks.buffer[i] & COLLISION_MASK) == COLLISION_MASK)
		{
			for(size_t j = 0; j < self->collisions.buffer[i].collisions.size; j++)
			{
				struct Collision_Info* info = &self->collisions.buffer[i].collisions.buffer[j];
				SDL_Rect pos = {
					self->positions.buffer[i].x,
					self->positions.buffer[i].y,
					self->textures.buffer[i].width,
					self->textures.buffer[i].height
				};
				SDL_Rect test_pos = {
					self->positions.buffer[info->entity].x,
					self->positions.buffer[info->entity].y,
					self->textures.buffer[info->entity].width,
					self->textures.buffer[info->entity].height
				};
				get_point(self->positions.buffer[i].r_point, &pos);
				get_point(self->positions.buffer[info->entity].r_point, &test_pos);

				switch(info->type)
				{
				case COLLISION_TOP:
					pos.y = test_pos.y + self->textures.buffer[info->entity].height;
					self->movements.buffer[i].y_movement = 0;
					break;
				case COLLISION_BOTTOM:
					pos.y = test_pos.y - self->textures.buffer[i].height;
					self->movements.buffer[i].y_movement = 0;
					break;
				case COLLISION_LEFT:
					pos.x = test_pos.x + self->textures.buffer[info->entity].width;
					self->movements.buffer[i].x_movement = 0;
					break;
				case COLLISION_RIGHT:
					pos.x = test_pos.x - self->textures.buffer[i].width;
					self->movements.buffer[i].x_movement = 0;
					break;
				default:;
				}

				set_point(self->positions.buffer[i].r_point, &pos);
				self->positions.buffer[i].x = pos.x;
				self->positions.buffer[i].y = pos.y;
			}
		}
	}

	for(size_t i = 0; i < self->masks.size; i++)
	{
		if((self->masks.buffer[i] & (COLLISION_MASK & ~COMPONENT_MOVEMENT)) == 
			(COLLISION_MASK & ~COMPONENT_MOVEMENT))
		{
			for(size_t j = 0; j < self->collisions.buffer[i].collisions.size; j++)
			{
				Vec_pop_back(&self->collisions.buffer[i].collisions);
			}
		}
	}
}

#define KEY_CONTROL_MASK (COMPONENT_MOVEMENT | COMPONENT_KEY_CONTROL)
void handle_key_controls(struct ECS* self, const Uint8* key_state)
{
	assert(self);
	assert(key_state);
	for(size_t i = 0; i < self->masks.size; i++)
	{
		if((self->masks.buffer[i] & KEY_CONTROL_MASK) == KEY_CONTROL_MASK)
		{
			if(key_state[self->key_controls.buffer[i].move_up])
			{
				self->movements.buffer[i].y_movement -= self->movements.buffer[i].speed;
			}
			if(key_state[self->key_controls.buffer[i].move_down])
			{
				self->movements.buffer[i].y_movement += self->movements.buffer[i].speed;
			}
			if(key_state[self->key_controls.buffer[i].move_left])
			{
				self->movements.buffer[i].x_movement -= self->movements.buffer[i].speed;
			}
			if(key_state[self->key_controls.buffer[i].move_right])
			{
				self->movements.buffer[i].x_movement += self->movements.buffer[i].speed;
			}
		}
	}
}
