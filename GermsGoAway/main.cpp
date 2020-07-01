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
#include "GameOver.h"
#include "Victory.h"



int main()
{
	bool gameStarted = false;
	bool restartGame = false;
	bool leftClickReleased = true;
	TextureManager* textureManager = new TextureManager();

	// Window Properties
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Mondlitch");
	window.setFramerateLimit(60);
	// View Properties
	sf::View view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f));
	float cameraX;
	float cameraY;
	float cameraX_Spawn;
	float cameraY_Spawn;
	float cameraSlope;
	bool cameraAdjusted = true;

	window.setView(view);

	// Preparing Main Menu
	MainMenu* mainMenu = new MainMenu(textureManager);

	// Preparing Game Over
	GameOver gameOver = GameOver(textureManager);

	// Preparing Victory
	Victory victory = Victory(textureManager);

	// Preparing Player
	Player player = Player(textureManager);

	// Preparing Level
	Levels levels = Levels(textureManager);
	
	std::vector<Platform> levelOneStructures = levels.getLevelOneStructures();
	std::vector<Enemy> levelOneEnemies = levels.getLevelOneEnemies();

	std::vector<Platform> levelTwoStructures = levels.getLevelTwoStructures();
	std::vector<Enemy> levelTwoEnemies = levels.getLevelTwoEnemies();

	// Preparing Background
	Background* background = new Background(textureManager);


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
			gameOver.allowMusic();
			victory.allowMusic();
			player.revive();
			mainMenu->update();
			window.draw(mainMenu->getBackground());
			window.draw(mainMenu->getTitle());
			if (mainMenu->doesGameStart(leftClickReleased) == 0) {
				leftClickReleased = true;
			}
			if (leftClickReleased) {
				gameStarted = mainMenu->doesGameStart(leftClickReleased);
				if (gameStarted) {
					view.setSize(480.f, 270.f);
					view.setCenter(240.f,player.getY() - 16.f);
				}
			}


			window.setView(view);
		}

		if (gameStarted && (player.getLives() > -1) && !player.finishedGame()) {

			// Level update & render
			background->update(player.getVelocityX());
			window.draw(background->getMainSprite());

			if (player.getLevelsCompleted() == 0) {

				cameraX_Spawn = 240.f;
				cameraY_Spawn = 650.f;

				for (auto &platform : levelOneStructures) {
					platform.update();
					window.draw(platform.getSprite());
				}

				for (auto &enemy : levelOneEnemies) {
					
					enemy.update(levels.getPlatformNearPlayerLevelOne(enemy.getX(), enemy.getY()));

					window.draw(enemy.getSprite());
				}

				// Player update & render
				player.update(levels.getPlatformNearPlayerLevelOne(player.getX(), player.getY()), levelOneEnemies, clock.getElapsedTime().asSeconds(), cameraAdjusted);

			}
			else if (player.getLevelsCompleted() == 1) {

				cameraX_Spawn = 240.f;
				cameraY_Spawn = 266.f;

				for (auto &platform : levelTwoStructures) {
					platform.update();
					window.draw(platform.getSprite());
				}

				for (auto &enemy : levelTwoEnemies) {
					enemy.update(levels.getPlatformNearPlayerLevelTwo(enemy.getX(), enemy.getY()));
					window.draw(enemy.getSprite());
				}

				// Player update & render
				player.update(levels.getPlatformNearPlayerLevelTwo(player.getX(), player.getY()), levelTwoEnemies, clock.getElapsedTime().asSeconds(), cameraAdjusted);

			}

			window.draw(player.getSprite());

			

			if (!player.hasDied() && cameraAdjusted && !player.finishedGame()) {

				cameraX = player.getX();
				cameraY = player.getY() - 16.f;

				cameraSlope = -1 * (cameraY_Spawn - cameraY) / (cameraX_Spawn - cameraX);
				if (player.getX() >= 240.f) {
		
					view.setCenter(cameraX, cameraY);
				}
				else {
						
						view.setCenter(cameraX_Spawn, cameraY);
				}
			}
			else {

				cameraAdjusted = false;
				float cameraXadjustment = 3.f * (cameraX * 0.0015);
				float cameraYadjustment = cameraXadjustment * cameraSlope;
				view.move(-cameraXadjustment, cameraYadjustment);
				
				if (view.getCenter().x <= cameraX_Spawn ) {
					cameraAdjusted = true;
				}
				
			}

			window.setView(view);
		}

		if ((player.getLives() == -1)) {
			background->stopMusic();
			background->allowMusic();
			view.setSize(1280.f, 720.f);
			view.setCenter(640.f, 360.f);
			gameOver.update();
			window.draw(gameOver.getTitle());
			if (gameOver.doesGameStart()) {
				restartGame = true;
				gameStarted = false;
				mainMenu->allowMenuMusic();
				leftClickReleased = false;
			}
			window.setView(view);
		}

		if (player.finishedGame()) {
			background->stopMusic();
			background->allowMusic();
			view.setSize(1280.f, 720.f);
			view.setCenter(640.f, 360.f);
			victory.update();
			window.draw(victory.getTitle());
			if (victory.doesGameStart()) {
				restartGame = true;
				gameStarted = false;
				mainMenu->allowMenuMusic();
				leftClickReleased = false;
			}
			window.setView(view);
		}


		window.display();
	}

	return 0;
}
