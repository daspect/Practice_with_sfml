#pragma once

void World::loadTextures()
{
	//BACKGROUNDS
	textures.load(Textures::Landscape, "stardew2.png");

	//PLAYER
	textures.load(Textures::PlayerDown, "sprite_front.png");
	textures.load(Textures::PlayerUp, "sprite_back.png");
	textures.load(Textures::PlayerLeft, "sprite_left.png");
	textures.load(Textures::PlayerRight, "sprite_right.png");

	//SCENERY
	textures.load(Textures::Tree, "palm.png");
}

void World::createEntities()
{
	//BACKGROUND
	Entity* background(new Entity(ObjectIdentifier::Background, EntityType::Background, textures));
	background->setDefaultTexture(Textures::Landscape);
	entities.push_back(background);

	//PLAYER
	Entity* player(new Entity(ObjectIdentifier::Player, EntityType::Movable, textures));
	player->setDefaultTexture(Textures::PlayerDown);
	player->setDirectionTextures(Textures::PlayerDown, Textures::PlayerUp, Textures::PlayerRight, Textures::PlayerLeft);
	player->setFootprint(20, 20, 0, 0);
	entities.push_back(player);

	//TREE
	Entity* tree(new Entity(EntityType::Immovable, textures));
	tree->setDefaultTexture(Textures::Tree);
	tree->setPosition(700.f, 700.f);
	tree->setFootprint(30, 30, 0, -50);
	entities.push_back(tree);
}