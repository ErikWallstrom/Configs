#include "Game.hpp"
#include "Label.hpp"
#include <iostream>
#include <cstdlib>

int main()
{
	try {
		Game game(800, 600);
		Texture texture(
				game.get_renderer(), 
				"Player.png");
		Scene scene;
		game.add(&scene);
		Entity entity(
				&texture, 
				Entity::POINT_CENTER, 
				50, 
				50, 
				120, 
				80);
		TTF_Font* font = TTF_OpenFont("Roboto-Regular.ttf", 24);
		Label label(
				game.get_renderer(),
				Entity::POINT_TOP_LEFT,
				300,
				200,
				font,
				"Suka blyad nahoi");
		scene.add(&entity);
		scene.add(&label);
		while(game.update());
	}
	catch(const char* msg)
	{
		SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_ERROR,
				"Error",
				msg,
				NULL);
		abort();
	}
}
