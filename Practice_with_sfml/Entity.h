#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include "Message.h"
//#include "MessageHandler.h" //If I include this, everything breaks
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include "Identifiers.h"


class Entity : public sf::Sprite
{
public:
	//Constructors
	Entity(ObjectIdentifier::ID, EntityType::ID, TextureHolder& textures);
	Entity(EntityType::ID, TextureHolder& textures);
	
	void					setDefaultTexture(Textures::ID id);
	void					setDirectionTextures(Textures::ID down, Textures::ID up, Textures::ID right, Textures::ID left);
	ObjectIdentifier::ID	entityIdentifier = ObjectIdentifier::Default;

	sf::Vector2f	getCentroid();
	void			setFootprint(int height, int width, int offsetX, int offsetY);
	sf::FloatRect	getFootprint();
	void			updateFootprintYBound();
	void			update(std::vector<Entity*>, sf::Time);

	void	addMessage(Message);
	void	addSubscription(MessageType::ID);
	bool	isSubscribed(MessageType::ID);
	
	//Define comparision of Entity pointers to be passed to the std::sort() method as a comparator. Elsewhere in the class, the comparison of 2 Entites is defined 
	struct PointerCompare
	{
		bool operator()(const Entity* l, const Entity* r)
		{
			return *l < *r;
		}
	};
	

private:
	EntityType::ID entityType;

	std::queue<Message>				messageQueue;
	std::vector<MessageType::ID>	subscriptions;
	//MessageHandler*					messengerRef = NULL;

	
	int		footprintHeight = 0;
	int		footprintWidth = 0;
	int		footprintOffsetX = 0;
	int		footprintOffsetY = 0;
	float	footprintYbound = 0;

	float movementSpeed = 500.f;
	sf::Vector2f nextMove;
	
	TextureHolder&	texturesRef;
	Textures::ID	defaultTexture;
	Textures::ID	downTexture;
	Textures::ID	upTexture;
	Textures::ID	rightTexture;
	Textures::ID	leftTexture;
	bool			hasDirectionalTextures = false;

	//Definition of < comparison operator of 2 Entity objects. Used by std::sort() method.
	bool operator< (const Entity &e2) const;
	
	
	void	processMessages();
	bool	checkCollision(sf::FloatRect);
	void	processMovementMessage(MovementDirection::ID);
	
	
};

