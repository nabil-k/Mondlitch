#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureManager.h"

class GameOver {
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


	GameOver(TextureManager* textureManagerInitialized) {

		title.setTexture(textureManagerInitialized->getTexture("GameOver_Title"));
		if (!gameOverBuffer.loadFromFile("./audio/game-over-sfx-and-voice.wav")) {
			std::cout << "Couldn't load hurt sfx" << std::endl;
		}

		sound.setBuffer(gameOverBuffer);
		
	}
};

void GameOver::allowMusic() {
	playGameOver = true;
}

void GameOver::update() {
	if (playGameOver) {
		sound.play();
	}
	playGameOver = false;
}

bool GameOver::doesGameStart() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		sound.stop();
		return true;
	}
	return false;
}

sf::Sprite GameOver::getTitle() {
	return title;
}