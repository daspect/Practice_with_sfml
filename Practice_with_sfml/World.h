#pragma once
#include "Identifiers.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>


class World
{
public:
	World();
	Entity*	getEntity(ObjectIdentifier::ID);
	void	setup();
	void	update(sf::Time);
	void	addEntity(Entity*);

	TextureHolder textures;
	std::vector <Entity*> entities;

private:
	void	sortEntities();
	void	loadTextures();
	void	createEntities();
};
