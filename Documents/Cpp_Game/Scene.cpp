#include "Scene.hpp"
#include "Game.hpp"
#include <cassert>

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::update(Game* game)
{
	for(auto e : content)
	{
		e->update(game);
		e->render(game->get_renderer());
	}
}

void Scene::add(Entity* entity)
{
	assert(entity);
	content.push_back(entity);
}
