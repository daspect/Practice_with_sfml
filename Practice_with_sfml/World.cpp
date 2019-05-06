#include "World.h"


//Add inline definitions for loadTextures() and createEntities()
#include "TextureAndEntityCreation.inl"



World::World()
{
}

void World::setup()
{
	loadTextures();
	createEntities();
	sortEntities();
}


void World::update(sf::Time dt)
{
	for (std::size_t i = 0; i < entities.size(); ++i)
	{
		entities[i]->update(entities, dt);
	}
	sortEntities();
}

void World::sortEntities()
{
	for (std::size_t i = 0; i < entities.size(); ++i)
	{
		entities[i]->updateFootprintYBound();
	}
	std::sort(entities.begin(), entities.end(), Entity::PointerCompare());
}

Entity*	World::getEntity(ObjectIdentifier::ID id)
{
	for (std::size_t i = 0; i < entities.size(); ++i)
	{
		if(entities[i]->entityIdentifier == id)
			return entities[i];
	}
	return NULL;
}

void World::addEntity(Entity* ent)
{
	entities.push_back(ent);
}

