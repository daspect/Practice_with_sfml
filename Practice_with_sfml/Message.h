#pragma once
#include <SFML/Graphics.hpp>
#include "MessageIdentifiers.inl"
#include "Identifiers.h"


class Message
{
public:
	Message(MessageType::ID);
	Message(MessageType::ID, ObjectIdentifier::ID to);
	Message(MessageType::ID, ObjectIdentifier::ID to, ObjectIdentifier::ID from);
	MessageType::ID messageType;
	ObjectIdentifier::ID to;
	ObjectIdentifier::ID from;



	MovementDirection::ID movementDir;
	void setMovementDir(MovementDirection::ID dir);
};

