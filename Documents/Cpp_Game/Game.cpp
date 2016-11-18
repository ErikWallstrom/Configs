#include "Game.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <cstdlib>
#include <ctime>

Game::Game(int width, int height)
{
	assert(width > 0);
	assert(height > 0);

	std::srand(std::time(nullptr));
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) ||
			!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) ||
			TTF_Init())
		throw SDL_GetError();

	window = SDL_CreateWindow(
			"Game Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			0);
	if(!window)
		throw SDL_GetError();
	renderer = SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC |
			SDL_RENDERER_TARGETTEXTURE);
	if(!renderer)
		throw SDL_GetError();

	key_state = SDL_GetKeyboardState(nullptr);
	mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

	this->width = width;
	this->height = height;
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Game::update()
{
	while(SDL_PollEvent(&event))
		if(event.type == SDL_QUIT)
			return false;
	mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

	SDL_RenderClear(renderer);
	if(scenes.size())
		scenes[0]->update(this);
	SDL_RenderPresent(renderer);
	return true;
}

void Game::add(Scene* scene)
{
	assert(scene);
	scenes.push_back(scene);
}
