#include "Message.h"



Message::Message(MessageType::ID type) : messageType(type)
{
}

Message::Message(MessageType::ID type, ObjectIdentifier::ID to) : messageType(type), to(to)
{
}

Message::Message(MessageType::ID type, ObjectIdentifier::ID to, ObjectIdentifier::ID from) : messageType(type), to(to), from(from)
{
}

void Message::setMovementDir(MovementDirection::ID dir) {
	movementDir = dir;
}

