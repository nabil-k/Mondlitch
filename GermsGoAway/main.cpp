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

	for (int i = 0; i < 40; i++){
		Platform platform = Platform(i * 16.f, 704.f, 16, 16, textureManager);
		levelPlatforms.push_back(platform);
	};

	Platform smallWall_1 = Platform(500.f, 500.f, 16, 16, textureManager);
	Platform smallWall_2 = Platform(0.f, 688.f, 16, 16, textureManager);
	Platform smallWall_3 = Platform(160.f, 688.f, 16, 16, textureManager);
	levelPlatforms.push_back(smallWall_1);
	levelPlatforms.push_back(smallWall_2);
	levelPlatforms.push_back(smallWall_3);

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

		int i = 0;

		if (mouse.isButtonPressed(sf::Mouse::Left)) {
			std::cout << "Mouse Y : " << mouse.getPosition(window).y << std::endl;
		}

		// Level update & render
		for (auto &platform: levelPlatforms) {
			
			platform.update();
			window.draw(platform.getSprite());
		}
		
		// Player update & render
		player.update(levelPlatforms, clock.getElapsedTime().asSeconds());
		window.draw(player.getSprite());

		window.display();
	}

	return 0;
}
