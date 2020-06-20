#include <iostream>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Player.h"
#include "Platform.h"
#include "TextureManager.h"
#include "Levels.h";
#include "Background.h"



int main()
{
	bool gameStarted = false;

	TextureManager* textureManager = new TextureManager();

	// Window Properties
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Germs Go Away");
	window.setFramerateLimit(60);
	// View Properties
	sf::View view(sf::FloatRect(0.f, 600.f, 480.f, 270.f));
	window.setView(view);

	// Preparing Main Menu
	MainMenu mainMenu = MainMenu(textureManager);

	// Preparing Player
	Player player = Player(textureManager);

	// Preparing Level
	Levels levels = Levels(textureManager);
	std::vector<Platform> levelOneStructures = levels.getLevelOneStructures();
	std::vector<Enemy> levelOneEnemies = levels.getLevelOneEnemies();

	// Preparing Background
	Background background = Background(textureManager);


	// Clock starts
	sf::Clock clock;
	sf::Mouse mouse;

	while (window.isOpen())
	{
		
		window.clear(sf::Color(0, 0, 0));
		

		// Game Exit
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (!gameStarted) {
			view.setSize(1280.f, 720.f);
			view.setCenter(640.f, 360.f);
			mainMenu.update();
			window.draw(mainMenu.getBackground());
			window.draw(mainMenu.getTitle());
			gameStarted = mainMenu.doesGameStart();

			window.setView(view);
		}

		if (gameStarted) {
			// Level update & render
			background.update(player.getVelocityX());
			window.draw(background.getMainSprite());
			window.draw(background.getLayerOneSprite());

			for (auto &platform : levelOneStructures) {
				platform.update();
				window.draw(platform.getSprite());
			}

			

			for (auto &enemy : levelOneEnemies) {
				enemy.update(levels.getPlatformNearPlayerLevelOne(enemy.getX(), enemy.getY()));
				window.draw(enemy.getSprite());
			}

			// Player update & render
			player.update(levels.getPlatformNearPlayerLevelOne(player.getX(), player.getY()), clock.getElapsedTime().asSeconds());
			window.draw(player.getSprite());

			view.setSize(480.f, 270.f);
			if (player.getX() >= 240.f) {
				view.setCenter(player.getX(), player.getY() - 16.f);
			}
			else {
				view.setCenter(240.f, player.getY() - 16.f);
			}

			
			
			window.setView(view);
		}


		window.display();
	}

	return 0;
}
