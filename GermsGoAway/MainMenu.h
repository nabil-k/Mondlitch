#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureManager.h"

class MainMenu {
	sf::Sprite background;
	sf::Sprite title;
	sf::Music music;
	sf::Clock clock;

	public:
		sf::Sprite getBackground();
		sf::Sprite getTitle();
		float titleCenterX = 330.f;
		float titleCenterY = 200.f;
		float timeSinceLastFrame = 0;
		void animateTitle();
		void allowMenuMusic();
		void update();
		bool doesGameStart(bool leftClickReleased);
		bool gameStart = false;
		bool playMusic = true;

		MainMenu(TextureManager* textureManagerInitialized) {
			background.setTexture(textureManagerInitialized->getTexture("MainMenu_Background"));
			title.setTexture(textureManagerInitialized->getTexture("MainMenu_Title"));
			title.setPosition(titleCenterX, titleCenterY);

			if (!music.openFromFile("./audio/Castle Theme-Super Mario World.wav")) {
				std::cout << "couldn't load main menu music" << std::endl;
			}

			music.setLoop(true);
			music.setVolume(10);

		}
};


void MainMenu::animateTitle() {
	float windowWidth = 1280;
	float windowHeight = 720;
	float pos_x_adjustment = (windowWidth - title.getGlobalBounds().width) / 2;
	float pos_y_adjustment = (windowHeight - title.getGlobalBounds().height) / 2;
	timeSinceLastFrame = clock.getElapsedTime().asSeconds();
	if (timeSinceLastFrame < 3) {
		title.scale(1.001, 1.001);
		title.setPosition(pos_x_adjustment, pos_y_adjustment);
	}
	else if (timeSinceLastFrame < 6) {
		title.scale(0.999, 0.999);
		title.setPosition(pos_x_adjustment, pos_y_adjustment);
	}
	else {
		clock.restart();
		title.setPosition(pos_x_adjustment, pos_y_adjustment);
	}

	
}

void MainMenu::allowMenuMusic() {
	playMusic = true;
}

void MainMenu::update() {
	animateTitle();
	if (playMusic) {
		std::cout << "play again" << std::endl;
		music.play();
		playMusic = false;
	}
}

bool MainMenu::doesGameStart(bool leftClickReleased) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (leftClickReleased) {
			music.stop();
		}
		return true;
	}
	return false;
}

sf::Sprite MainMenu::getBackground() {
	return background;
}

sf::Sprite MainMenu::getTitle() {
	return title;
}