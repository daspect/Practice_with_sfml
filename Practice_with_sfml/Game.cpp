#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : frameSize(1000), window(sf::VideoMode(frameSize, frameSize), "Moons Rest"), messenger(&world)
{
	window.setFramerateLimit(60);
	view.reset(sf::FloatRect(0, 0, frameSize, frameSize));
	world.setup();
}

void Game::run()
{
	while (window.isOpen())
	{
		processInput();
		messenger.handleMessages();
		world.update(TimePerFrame);

		sf::Time elapsedTime = mClock.restart();
		//std::cout << int(1.f / elapsedTime.asSeconds()) << std::endl;
		//std::cout << "" << std::endl;

		render();
	}
	return;
}

void Game::render()
{
	window.clear();
	window.setView(view);
	for (std::size_t i = 0; i < world.entities.size(); ++i)
	{
		window.draw(*world.entities[i]);
	}
	window.display();
}

void Game::processInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			break;
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Message msg(MessageType::Movement, ObjectIdentifier::Player);
		msg.setMovementDir(MovementDirection::Left);
		messenger.sendMessage(msg);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Message msg(MessageType::Movement, ObjectIdentifier::Player);
		msg.setMovementDir(MovementDirection::Right);
		messenger.sendMessage(msg);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Message msg(MessageType::Movement, ObjectIdentifier::Player);
		msg.setMovementDir(MovementDirection::Up);
		messenger.sendMessage(msg);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Message msg(MessageType::Movement, ObjectIdentifier::Player);
		msg.setMovementDir(MovementDirection::Down);
		messenger.sendMessage(msg);
	}



	view.setCenter(world.getEntity(ObjectIdentifier::Player)->getCentroid());

	if (view.getCenter().x < frameSize / 2)
		view.setCenter(frameSize / 2, view.getCenter().y);
	if (view.getCenter().y < frameSize / 2)
		view.setCenter(view.getCenter().x, frameSize / 2);
	if (view.getCenter().x > world.getEntity(ObjectIdentifier::Background)->getTexture()->getSize().x - (frameSize / 2))
		view.setCenter(world.getEntity(ObjectIdentifier::Background)->getTexture()->getSize().x - (frameSize / 2), view.getCenter().y);
	if (view.getCenter().y > world.getEntity(ObjectIdentifier::Background)->getTexture()->getSize().y - (frameSize / 2))
		view.setCenter(view.getCenter().x, world.getEntity(ObjectIdentifier::Background)->getTexture()->getSize().y - (frameSize / 2));
		
}