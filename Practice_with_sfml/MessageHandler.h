#pragma once
//#include "MessageIdentifiers.inl"
#include "Message.h"
	/*
	#include <SFML/Graphics.hpp>
	#include "MessageIdentifiers.inl"
	#include "Identifiers.h"
	*/
//#include "Identifiers.h"
#include <queue>
#include "World.h"

class MessageHandler
{
public:
	MessageHandler(World*);
	void sendMessage(Message msg);
	void publishMessage(Message msg);
	void handleMessages();

private:
	std::queue<Message> directMessageQueue;
	std::queue<Message> publishedMessageQueue;
	World* world;

	void handleDirectMessages();
	void handlePublishedMessages();
};

