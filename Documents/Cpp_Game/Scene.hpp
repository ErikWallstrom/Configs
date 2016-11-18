#ifndef SCENE_INCLUDED
#define SCENE_INCLUDED

#include <vector>
#include "Entity.hpp"

class Scene
{
private:
	std::vector<Entity*> content;
public:
	Scene();
	virtual ~Scene();
	void update(Game* game);
	void add(Entity* entity);
};

#endif
