#include <iostream>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "TextureManager.h"
#include "Levels.h";


int main()
{
	TextureManager* textureManager = new TextureManager();

	// Window Properties
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Germs Go Away");
	window.setFramerateLimit(60);
	// View Properties
	sf::View view(sf::FloatRect(0.f, 600.f, 480.f, 270.f));
	window.setView(view);


	// Preparing Player
	Player player = Player(textureManager);

	// Preparing Level
	Levels levels = Levels(textureManager);
	std::vector<Platform> levelOne = levels.getLevelOne();


	// Clock starts
	sf::Clock clock;
	sf::Mouse mouse;

	while (window.isOpen())
	{
		
		window.clear(sf::Color(176, 131, 229));
		

		// Game Exit
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Level update & render
		for (auto &platform: levelOne) {
			
			platform.update();
			window.draw(platform.getSprite());
		}
		
		// Player update & render
		player.update(levelOne, clock.getElapsedTime().asSeconds());
		window.draw(player.getSprite());
		
		view.setCenter(player.getX(), player.getY() - 16.f);
		window.setView(view);

		window.display();
	}

	return 0;
}
