#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "player.h"
#include "platform.h"


int main()
{
	sf::Image spriteSheet;
	spriteSheet.loadFromFile("./assets/characters.png");

	// Clock starts
	sf::Clock clock; 
	
	// Window Properties
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Germs Go Away");
	window.setFramerateLimit(60);

	//Player
	Player player = Player(spriteSheet);

	while (window.isOpen())
	{

		// Game Exit
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Updates
		player.update();

		// Rendering
		window.clear();
		window.draw(player.getSprite());
		window.display();
	}

	return 0;
}