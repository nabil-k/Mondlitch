#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureManager.h"

class Victory {
	sf::Sprite title;
	//for sfx
	sf::Sound sound;
	sf::SoundBuffer gameOverBuffer;

public:
	sf::Sprite getTitle();
	void update();
	bool doesGameStart();
	void allowMusic();
	bool gameStart = false;
	bool playGameOver = true;


	Victory(TextureManager* textureManagerInitialized) {

		title.setTexture(textureManagerInitialized->getTexture("Victory_Title"));
		if (!gameOverBuffer.loadFromFile("./audio/466133__humanoide9000__victory-fanfare.wav")) {
			std::cout << "Couldn't load hurt sfx" << std::endl;
		}

		sound.setBuffer(gameOverBuffer);

	}
};

void Victory::allowMusic() {
	playGameOver = true;
}

void Victory::update() {
	if (playGameOver) {
		sound.play();
	}
	playGameOver = false;
}

bool Victory::doesGameStart() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

		return true;
	}
	return false;
}

sf::Sprite Victory::getTitle() {
	return title;
}