#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Scene.hpp"

class Game
{
private:
	SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;
	const Uint8* key_state;
	Uint32 mouse_state;
	int width, height;
	int mouse_x, mouse_y;
	std::vector<Scene*> scenes;

public:
	Game(int width, int height);
	~Game();
	bool update();
	void add(Scene* scene);
	SDL_Window* get_window(){ return window; }
	SDL_Renderer* get_renderer(){ return renderer; }
	bool key_down(SDL_Scancode key){ return key_state[key]; }
	bool mouse_down(Uint32 button){ return mouse_state & SDL_BUTTON(button); }
	int get_mouse_x(){ return mouse_x; }
	int get_mouse_y(){ return mouse_y; }
	int get_width(){ return width; }
	int get_height(){ return height; }
};

#endif
