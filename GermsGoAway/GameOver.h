#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class GameOver {
	sf::Sprite title;

public:
	sf::Sprite getTitle();
	void update();
	bool doesGameStart();
	bool gameStart = false;

	GameOver(TextureManager* textureManagerInitialized) {

		title.setTexture(textureManagerInitialized->getTexture("GameOver_Title"));
		
	}
};

void GameOver::update() {
}

bool GameOver::doesGameStart() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		std::cout << "START GAME" << std::endl;
		return true;
	}
	return false;
}

sf::Sprite GameOver::getTitle() {
	return title;
}