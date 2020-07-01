#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureManager.h"

class Background {
	sf::Sprite skySprite;
	sf::Music music;
	bool playMusic = true;

	public:
		sf::Sprite getMainSprite();
		void update(float vel_x);
		void allowMusic();
		void stopMusic();

		Background(TextureManager* textureManager) {
			this->skySprite = sf::Sprite(textureManager->getTexture("Sky"), sf::IntRect(sf::Vector2i (0, 0), sf::Vector2i(5120, 720)));
			skySprite.setPosition(-300.f, 0.f);
			skySprite.setTexture(textureManager->getTexture("Sky"));

			if (!music.openFromFile("./audio/Ghost House - Super Mario World.wav")) {
				std::cout << "couldn't load main menu music" << std::endl;
			}

			music.setLoop(true);
			music.setVolume(10);

		}

};

void Background::allowMusic() {
	playMusic = true;
}

void Background::stopMusic() {
	music.stop();
}

sf::Sprite Background::getMainSprite() {
	return skySprite;
}


void Background::update(float vel_x) {
	if (playMusic) {
		std::cout << "play again" << std::endl;
		music.play();
		playMusic = false;
	}
	
}