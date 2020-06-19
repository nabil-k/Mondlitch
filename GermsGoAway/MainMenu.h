#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class MainMenu {
	sf::Sprite background;
	sf::Sprite title;

	public:
		sf::Sprite getBackground();
		sf::Sprite getTitle();
		void update();
		bool doesGameStart();
		bool gameStart = false;

		MainMenu(TextureManager* textureManagerInitialized) {
			background.setTexture(textureManagerInitialized->getTexture("MainMenu_Background"));
			title.setTexture(textureManagerInitialized->getTexture("MainMenu_Title"));
			title.setPosition(330.f, 200.f);
		}
};

void MainMenu::update() {
}

bool MainMenu::doesGameStart() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
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