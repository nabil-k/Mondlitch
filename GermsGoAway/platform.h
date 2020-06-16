#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Platform {

	int width, height;
	float x, y;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Image LevelSpriteSheet;
	TextureManager* textureManager;
	bool collidable;
	

	public:
		int getWidth(), getHeight();
		float getX(), getY();
		void update();
		sf::Sprite getSprite();
		//, int img_coords[4]

		Platform(float x, float y, int width, int height, TextureManager* textureManagerInitialized, sf::String type) {
		
			this->x = x;
			this->y = y;
			this->width = width;
			this-> height = height;
			this->textureManager = textureManagerInitialized;
			sprite.setTexture(textureManager->getTexture(type));
			sprite.setPosition(sf::Vector2f(x, y));
		
		}

};

int Platform::getWidth() {
	return width;
}

int Platform::getHeight() {
	return height;
}

float Platform::getX() {
	return x;
}

float Platform::getY() {
	return y;
}

void Platform::update() {
	
}

sf::Sprite Platform::getSprite() {
	return sprite;
}