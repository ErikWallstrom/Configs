#include "Window.h"
#include "Error.h"
#include <assert.h>

struct Window* Window_ctor(char* title, int width, int height, enum Window_Flags flags)
{
	assert(title);
	assert(width > 0);
	assert(height > 0);

	struct Window* self = malloc(sizeof(struct Window));
	assert(self);

	self->raw = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, 
		height,
		(flags == WINDOW_CONTEXT) ? 
			SDL_WINDOW_OPENGL : 
			SDL_WINDOW_SHOWN
	);
	if(!self->raw)
		error(SDL_GetError());

	if(flags == WINDOW_CONTEXT)
	{
		self->context = SDL_GL_CreateContext(self->raw);
		if(!self->context)
			error(SDL_GetError());
	}
	else
	{
		self->renderer = SDL_CreateRenderer(
			self->raw,
			-1,
			SDL_RENDERER_ACCELERATED | 
			SDL_RENDERER_PRESENTVSYNC |
			SDL_RENDERER_TARGETTEXTURE
		);
		if(!self->renderer)
			error(SDL_GetError());
	}
		
	self->flags = flags;
	self->width = width;
	self->height = height;
	self->key_state = SDL_GetKeyboardState(NULL);
	self->mouse_state = SDL_GetMouseState(
		&self->mouse_x,
		&self->mouse_y
	);

	size_t title_len = strlen(title);
	self->title = Vec_ctor(1, title_len + 1);
	Vec_set(&self->title, title, title_len);
	self->events = Vec_ctor(sizeof(SDL_Event), 0);
	return self;
}

int Window_update(struct Window* self)
{
	assert(self);
	SDL_Event event;
	Vec_set(&self->events, NULL, 0);
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			return 0;
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_TEXTEDITING:
		case SDL_TEXTINPUT:
			Vec_push_back(&self->events, event);
		default:
			continue;
		}
	}

	self->mouse_state = SDL_GetMouseState(
		&self->mouse_x,
		&self->mouse_y
	);

	SDL_GetWindowSize(self->raw, &self->width, &self->height);
	if(self->flags == WINDOW_CONTEXT)
		SDL_GL_SwapWindow(self->raw);
	else
	{
		SDL_RenderPresent(self->renderer);
		SDL_RenderClear(self->renderer);
	}
	return 1;
}

void Window_dtor(struct Window* self)
{
	assert(self);
	if(self->flags == WINDOW_CONTEXT)
		SDL_GL_DeleteContext(self->context);
	else
		SDL_DestroyRenderer(self->renderer);

	Vec_dtor(&self->title);
	Vec_dtor(&self->events);
	SDL_DestroyWindow(self->raw);
	free(self);
}

