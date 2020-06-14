#pragma once
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Platform.h"

class Player {
	int width, height;
	float pos_x, pos_y;
	float vel_x, vel_y;
	bool top_collision, bottom_collision, left_collision, right_collision;
	float gravity = 32;
	bool fall = true;
	bool moveRight = true;
	bool moveLeft = true;
	bool moveUp = true;


	sf::Clock dt;

	std::vector<Platform> levelPlatforms;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Image CharacterSpriteSheet;
	TextureManager* textureManager;
	

	public:
		int getWidth(), getHeight();
		float getX(), getY();
		void update(std::vector<Platform> levelPlatforms, float dt);
		sf::Sprite getSprite();
		void jump();
	
	Player(TextureManager* textureManagerInitialized){
		pos_x = 600.f;
		pos_y = 0.f;
		width = 15;
		height = 22;
		vel_x = 0;
		vel_y = 0;
		this->textureManager = textureManagerInitialized;
		sprite.setTexture(textureManager->getTexture("IdlePlayer"));
		sprite.setPosition(sf::Vector2f(pos_x, pos_y));

	}

};

int Player::getWidth() {
	return width;
}

int Player::getHeight() {
	return height;
}

float Player::getX() {
	return pos_x;
}

float Player::getY() {
	return pos_y;
}


void Player::jump(){

}

void Player::update(std::vector<Platform> levelPlatforms, float dt) {
	
	bool jumpPressed = false;
	bool moveLeftPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

		jumpPressed = true;

			
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		pos_y += 5;
		vel_y = 5;
		sprite.move(0, 5.f);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		std::cout << "A" << std::endl;
		pos_x -= 3;
		vel_x = 3;
		sprite.move(-3.f, 0);
		moveLeftPressed = true;

	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		std::cout << "D IS PRESSED============================" << std::endl;
		pos_x += 3;
		vel_x = 3;
		sprite.move(3.f, 0);

	}

	if (jumpPressed) {
		if (!fall) {
			pos_y -= 3;
			vel_y = -3;
			sprite.move(0, -3.f);
		}

	}


	if (fall) {
		std::cout << vel_y << std::endl;
		if (dt > 0.015f) {
			dt = 0.015f;
		}
		if (vel_y < 10) {
			vel_y += gravity * 0.001802f * 2;

		}

		pos_y += vel_y;
		sprite.move(0.f, vel_y);

	}


	
	
	this->levelPlatforms = levelPlatforms;

	float leftX = pos_x;
	float rightX = (pos_x + width);

	float topY = pos_y;
	float bottomY = pos_y + height;

	bool leftXCollission, rightXCollision, topYCollision, bottomYCollision;
	bool playerTouchedBottom = false;
	float adjustment;

	for (auto &platform : levelPlatforms) {
		leftXCollission = (leftX >= platform.getX()) && (leftX <= (platform.getX() + platform.getWidth()));
		rightXCollision = (rightX >= platform.getX()) && (rightX <= (platform.getX() + platform.getWidth()));
		topYCollision = (topY >= platform.getY()) && (topY <= (platform.getY() + platform.getHeight()));
		bottomYCollision = (bottomY >= platform.getY() && (bottomY <= platform.getY() + platform.getHeight()));


		
		// Checks bottom collisions
		if (vel_y > 0) {
			if (bottomYCollision && (rightXCollision || leftXCollission)) {
				playerTouchedBottom = true;
				float adjustment = platform.getY() - height;
				pos_y = adjustment;
				bottomY = pos_y;
				sprite.setPosition(pos_x, adjustment);
				fall = false;
				std::cout << "ADJUSTED_1 at " << dt << std::endl;
				std::cout << "bottomY" << bottomY << std::endl;
				vel_y = 0;
			}
		}

		

		// Checks top collisions
		if (topYCollision && (rightXCollision || leftXCollission)) {
			//std::cout << "TOP COLLISION" << std::endl;
			vel_y = 0;
		}

		// Checks left collisions
	
		
		if (leftXCollission) {
			bool checkTopYPlatInBetween = platform.getY() >= topY && platform.getY() + 1 < bottomY;
			bool checkBottomYPlatInBetween = platform.getY() + platform.getHeight() >= topY && platform.getY() + platform.getHeight() < bottomY;
			if (checkTopYPlatInBetween || checkBottomYPlatInBetween) {
				std::cout << "ADJUSTED_2 at " << dt << std::endl;
				std::cout << "bottomY" << bottomY << std::endl;
				pos_x = platform.getX() + platform.getWidth();
				sprite.setPosition(pos_x, pos_y);
				vel_x = 0;
			}
		}
		

		// Checks right collisions
		if (rightXCollision) {
			//std::cout << "RIGHT COLLISION" << std::endl;
			vel_x = 0;
		}
	
		if (!playerTouchedBottom) {
			fall = true;
		}

	}




	

}

sf::Sprite Player::getSprite() {
	return sprite;
}