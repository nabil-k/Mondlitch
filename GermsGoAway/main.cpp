#include <iostream>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "TextureManager.h"

int main()
{
	TextureManager* textureManager = new TextureManager();

	// Window Properties
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Germs Go Away");
	window.setFramerateLimit(60);

	// Preparing Player
	Player player = Player(textureManager);

	// Preparing Level

	std::vector<Platform> levelPlatforms;
	
	int grassPlatformSpriteCoords[3][4] = {
		{161,0,16,16},
		{(161 + 16),0,16,16},
		{(161 + 32),0,16,16}
	};


	for (int i = 0; i < 10; i++){
		Platform platform = Platform(i * 16.f, 704.f, 16, 16, textureManager);
		levelPlatforms.push_back(platform);
	};

	// Clock starts
	sf::Clock clock;

	while (window.isOpen())
	{
		
		window.clear();

		// Game Exit
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		int i = 0;

		// Level update & render
		for (auto &platform: levelPlatforms) {
			
			platform.update();
			window.draw(platform.getSprite());
		}
		
		// Player update & render
		player.update();
		window.draw(player.getSprite());

		window.display();
	}

	return 0;
}
