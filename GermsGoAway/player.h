#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Platform.h"

class Player {
	int width, height;
	float x, y;
	bool top_collision, bottom_collision, left_collision, right_collision;
	std::vector<Platform> levelPlatforms;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Image CharacterSpriteSheet;
	TextureManager* textureManager;
	

	public:
		int getWidth(), getHeight();
		float getX(), getY();
		void update(std::vector<Platform> levelPlatforms);
		sf::Sprite getSprite();
	
	Player(TextureManager* textureManagerInitialized){
		x = 200.f;
		y = -1000.f;
		width = 14;
		height = 21;
		this->textureManager = textureManagerInitialized;
		sprite.setTexture(textureManager->getTexture("IdlePlayer"));
		sprite.setPosition(sf::Vector2f(x, y));

	}

};

int Player::getWidth() {
	return width;
}

int Player::getHeight() {
	return height;
}

float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}

void Player::update(std::vector<Platform> levelPlatforms) {
	
	this->levelPlatforms = levelPlatforms;

	float leftX = x;
	float rightX = (x + width);
	float topY = y;
	float bottomY = y + height;
	bool fall = true;

	for (auto &platform : levelPlatforms) {
		bool leftXCollission = (leftX >= platform.getX()) && (leftX <= (platform.getX() + platform.getWidth()));
		bool rightXCollision = (rightX >= platform.getX()) && (rightX <= (platform.getX() + platform.getWidth()));
		bool topYCollision = (topY >= platform.getY()) && (topY <= (platform.getY() + platform.getHeight()));
		bool bottomYCollision = (bottomY >= platform.getY()) && (bottomY <= (platform.getY() + platform.getHeight()));;

		if (bottomYCollision && (leftXCollission || rightXCollision)) {
			std::cout << "Collision" << std::endl;
			fall = false;
		}

	}

	if (fall) {
		sprite.move(sf::Vector2f(0.f, 5.f));
		y += 5;
	}
	
	std::cout << y << std::endl;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		sprite.move(sf::Vector2f(0.f, -5.f));
		y -= 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		sprite.move(sf::Vector2f(0.f,5.f));
		y += 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sprite.move(sf::Vector2f(-5.f,0.f));
		x -= 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sprite.move(sf::Vector2f(5.f, 0.f));
		x += 5;
	}
}

sf::Sprite Player::getSprite() {
	return sprite;
}