#include "Load.h"
#include "String.h"
#include "Memory.h"

int main(void)
{
	gc(Game) game = Game_new(800, 600);
	gc(Scene) main_scene = load_main_scene(&game);
	gc(Scene) game_scene = load_game_scene(&game);

	push(game.scenes, main_scene);

	while(!game.done)
		Game_update(&game);
}
