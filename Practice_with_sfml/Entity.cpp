#include "Entity.h"

//Define comparison < operator between 2 entities
bool Entity::operator<(const Entity &e2) const
{
	//Background should alawys be at the top of the entity stack, rendered first so that everything else goes on top.
	if (entityType == EntityType::Background)
		return (true);
	if (e2.entityType == EntityType::Background)
		return (false);

	float e1y = footprintYbound;
	float e2y = e2.footprintYbound;

	return (e1y < e2y);
}

//Constructors
Entity::Entity(ObjectIdentifier::ID identifier, EntityType::ID type, TextureHolder& textures)
	: texturesRef(textures)
{
	entityType = type;
	entityIdentifier = identifier;
	if (entityType == EntityType::Background)
		footprintYbound = -1;
}

Entity::Entity(EntityType::ID type, TextureHolder& textures)
	: texturesRef(textures)
{
	entityType = type;
	if (entityType == EntityType::Background)
		footprintYbound = -1;
}

sf::Vector2f Entity::getCentroid()
{
	sf::Vector2f centroid(this->getPosition());
	centroid.x += this->getTexture()->getSize().x / 2;
	centroid.y += this->getTexture()->getSize().y / 2;
	return centroid;
}

void Entity::setFootprint(int height, int width, int offsetX, int offsetY)
{
	this->footprintHeight = height;
	this->footprintWidth = width;
	this->footprintOffsetX = offsetX;
	this->footprintOffsetY = offsetY;
}

sf::FloatRect Entity::getFootprint()
{
	//Find the origin of the sprite
	sf::Vector2f pos = this->getPosition();
	sf::Vector2f point(pos.x, pos.y);

	//find the center and bottom point of the sprite
	sf::Vector2u size = this->getTexture()->getSize();
	point.x += (float) (size.x / 2);
	point.y += (float) (size.y);

	//move point so that the footprint centroid is in the middle of the sprite 
	//and the footprint bottom edge is coincident with the bottom edge of the texture
	point.x -= footprintWidth / 2;
	point.y -= footprintHeight / 2;

	//apply the offsets
	point.x += footprintOffsetX;
	point.y += footprintOffsetY;

	//create and return the footprint
	return sf::FloatRect(point, sf::Vector2f(footprintWidth, footprintHeight));
}

void Entity::updateFootprintYBound()
{
	if (entityType == EntityType::Background)
		return;
	sf::Vector2f pos = this->getPosition();
	sf::Vector2u size = this->getTexture()->getSize();
	footprintYbound = pos.y + size.y + footprintOffsetY;
	return;
}


void Entity::update(std::vector<Entity*> entities, sf::Time dt)
{
	processMessages();

	if (entityType == EntityType::Movable)
	{
		move(nextMove * dt.asSeconds());

		for (std::size_t i = 0; i < entities.size(); ++i)
		{
			if (entities[i]->checkCollision(getFootprint()))
			{
				move(-nextMove * dt.asSeconds());
				break;
			}
		}
		nextMove.x = 0;
		nextMove.y = 0;
	}
}

void Entity::addMessage(Message msg)
{
	switch (entityType)
	{
	case EntityType::Movable:
		if (msg.messageType == MessageType::Movement)
			messageQueue.push(msg);
	}
}

void Entity::processMessages()
{
	while (!messageQueue.empty())
	{
		
		if (messageQueue.front().messageType == MessageType::Movement)
		{
			processMovementMessage(messageQueue.front().movementDir);
			
		}
		messageQueue.pop();
	}
}

bool Entity::checkCollision(sf::FloatRect rect)
{
	
	switch (entityType)
	{
	case EntityType::Player:
		break;
	case EntityType::Movable:
		break;
	case EntityType::Immovable:
		if (getFootprint().intersects(rect))
			return true;
		break;
	case EntityType::Background:
		if (!getGlobalBounds().intersects(rect))
			return true;
		break;
	}
	return false;
}

void Entity::processMovementMessage(MovementDirection::ID dir)
{
	switch (dir)
	{
	case(MovementDirection::Left):
		nextMove += sf::Vector2f(-movementSpeed, 0.f);
		if (hasDirectionalTextures)
			setTexture(texturesRef.get(leftTexture));
		break;
	case(MovementDirection::Right):
		nextMove += sf::Vector2f(movementSpeed, 0.f);
		if (hasDirectionalTextures)
			setTexture(texturesRef.get(rightTexture));
		break;
	case(MovementDirection::Up):
		nextMove += sf::Vector2f(0.f, -movementSpeed);
		if (hasDirectionalTextures)
			setTexture(texturesRef.get(upTexture));
		break;
	case(MovementDirection::Down):
		nextMove += sf::Vector2f(0.f, movementSpeed);
		if (hasDirectionalTextures)
			setTexture(texturesRef.get(downTexture));
		break;
	}
}

void Entity::setDefaultTexture(Textures::ID textureID)
{
	defaultTexture = textureID;
	setTexture(texturesRef.get(textureID));
}

void Entity::setDirectionTextures(Textures::ID down, Textures::ID up, Textures::ID right, Textures::ID left)
{
	downTexture = down;
	upTexture = up;
	rightTexture = right;
	leftTexture = left;
	hasDirectionalTextures = true;
}

void Entity::addSubscription(MessageType::ID sub)
{
	subscriptions.push_back(sub);
}

bool Entity::isSubscribed(MessageType::ID id)
{
	if (std::find(subscriptions.begin(), subscriptions.end(), id) != subscriptions.end())
		return true;
	else
		return false;
}
