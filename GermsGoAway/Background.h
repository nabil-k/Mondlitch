#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
class Background {
	sf::Sprite skySprite;
	sf::Sprite treeSprite;
	public:
		sf::Sprite getMainSprite();
		sf::Sprite getLayerOneSprite();
		void update(float vel_x);

		Background(TextureManager* textureManager) {
			this->skySprite = sf::Sprite(textureManager->getTexture("Sky"), sf::IntRect(sf::Vector2i (0, 0), sf::Vector2i(5120, 720)));
			skySprite.setPosition(-300.f, 0.f);
			skySprite.setTexture(textureManager->getTexture("Sky"));
			
			this->treeSprite.setPosition(100.f, 310.f);
			this->treeSprite.setScale(3.f, 3.f);
			this->treeSprite.setTexture(textureManager->getTexture("Tree"));
		}

};

sf::Sprite Background::getMainSprite() {
	return skySprite;
}

sf::Sprite Background::getLayerOneSprite() {
	return treeSprite;
}

void Background::update(float vel_x) {
	treeSprite.move(vel_x * .1, 0.f);
}