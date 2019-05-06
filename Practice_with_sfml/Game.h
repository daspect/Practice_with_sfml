#pragma once

#include "ResourceIdentifiers.hpp"
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include "ResourceHolder.hpp"
#include "Entity.h"
//#include "World.h"
#include "MessageHandler.h"


class Game
{
	public:
				Game();
		void	run();
		void	render();
		void	processInput();

		World world;
		MessageHandler messenger;
		
		
		
		

	private:
		static const sf::Time TimePerFrame;
		const int frameSize;
		sf::RenderWindow window;
		sf::Clock mClock;
		sf::View view;
		


};
