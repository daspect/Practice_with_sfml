#include "MessageHandler.h"



MessageHandler::MessageHandler(World* w) : world(w)
{
}

void MessageHandler::sendMessage(Message msg)
{
	directMessageQueue.push(msg);
}

void MessageHandler::publishMessage(Message msg)
{
	publishedMessageQueue.push(msg);
}

void MessageHandler::handleMessages()
{
	handleDirectMessages();
	handlePublishedMessages();
}

void MessageHandler::handleDirectMessages()
{
	while (!directMessageQueue.empty())
	{
		Entity* ptr;
		ptr = world->getEntity(directMessageQueue.front().to);
		if (ptr)
		{
			ptr->addMessage(directMessageQueue.front());
		}		
		directMessageQueue.pop();
	}
}

void MessageHandler::handlePublishedMessages()
{

}
