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
	bool prev_moveRight = false;
	bool prev_moveLeft = false;


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

	// Might be used to implement crounching later
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
	}

	// Left movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (moveLeft) {
			if (prev_moveRight) {
				vel_x = 0;
				prev_moveRight = false;
			}
			prev_moveLeft = true;

			if (vel_x > -3) {
				vel_x -= gravity * 0.001802f;
			}
			pos_x += vel_x;

			//pos_x -= 3;
			//vel_x = -3.f;
			sprite.move(vel_x, 0.f);
			std::cout << "Moving Left= " << pos_x << std::endl;
		}
	}
	else{
		if (prev_moveLeft) {
			vel_x = 0;
		}
	}

	// Right movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {	
		if (moveRight) {
			if (prev_moveLeft) {
				vel_x = 0;
				prev_moveLeft = false;
			}
			prev_moveRight = true;

			if (vel_x < 3) {
				vel_x += gravity * 0.001802f;
			}

			pos_x += vel_x;

			//pos_x += 3;
			//vel_x = 3.f;
			sprite.move(vel_x, 0);
		}
	}
	else {
		if (prev_moveRight) {
			vel_x = 0;
		}
	}

	// Controls how a player jumps
	if (jumpPressed) {
		if (!fall) {
			pos_y -= 5;
			vel_y = -5.f;
			sprite.move(0, vel_y);
		}

	}

	// Controls how player falls
	if (fall) {
		if (vel_y < 10) {
			vel_y += gravity * 0.001802f * 2;
		}
		pos_y += vel_y;
		sprite.move(0.f, vel_y);
	}


	
	// Level
	this->levelPlatforms = levelPlatforms;

	// Player's hitbox
	float leftX = pos_x;
	float rightX = (pos_x + width);
	float topY = pos_y;
	float bottomY = pos_y + height;

	// Tracks if player can move in a certain direction
	bool playerTouchedBottom = false;
	moveLeft = true;
	moveRight = true;
	float adjustment;

	// Player Collision Detection
	bool leftXCollission, rightXCollision, topYCollision, bottomYCollision;

	for (auto &platform : levelPlatforms) {
		leftXCollission = (leftX >= platform.getX()) && (leftX <= (platform.getX() + platform.getWidth()));
		rightXCollision = (rightX >= platform.getX()) && (rightX <= (platform.getX() + platform.getWidth()));
		topYCollision = (topY >= platform.getY()) && (topY <= (platform.getY() + platform.getHeight()));
		bottomYCollision = (bottomY >= platform.getY() && (bottomY <= platform.getY() + platform.getHeight()));


		
		// Checks bottom collisions
		if (vel_y > 0) {
			float leftXCollission_bottom = (leftX + 1 >= platform.getX()) && (leftX + 1 <= (platform.getX() + platform.getWidth()));
			float rightXCollision_bottom = (rightX - 1 >= platform.getX()) && (rightX - 1 <= (platform.getX() + platform.getWidth()));
			if (bottomYCollision && (rightXCollision_bottom || leftXCollission_bottom)) {
				playerTouchedBottom = true;
				float adjustment = platform.getY() - height;
				pos_y = adjustment;
				bottomY = pos_y;
				sprite.setPosition(pos_x, adjustment);
				fall = false;
				std::cout << "BOTTOM COLLISION" << std::endl;
				vel_y = 0;
			}
		}

		

		// Checks top collisions
		if (vel_y < 0) {
			float leftXCollission_bottom = (leftX + 1 >= platform.getX()) && (leftX + 1 <= (platform.getX() + platform.getWidth()));
			float rightXCollision_bottom = (rightX - 1 >= platform.getX()) && (rightX - 1 <= (platform.getX() + platform.getWidth()));
			if (topYCollision && (rightXCollision_bottom || leftXCollission_bottom)) {
				float adjustment = platform.getY() + platform.getHeight();
				pos_y = adjustment;
				bottomY = pos_y;
				sprite.setPosition(pos_x, adjustment);
				std::cout << "TOP COLLISION" << std::endl;
				vel_y = 0;
			}
		}

		// Checks left collisions
		if (leftXCollission) {
			bool checkTopYPlatInBetween = platform.getY() >= topY && platform.getY() + 1 < bottomY;
			bool checkBottomYPlatInBetween = platform.getY() + platform.getHeight() >= topY && platform.getY() + platform.getHeight() < bottomY;
			if (checkTopYPlatInBetween || checkBottomYPlatInBetween) {
				moveLeft = false;
				pos_x = platform.getX() + platform.getWidth();
				sprite.setPosition(pos_x, pos_y);
				std::cout << "LEFT COLLISION" << std::endl;
				std::cout << fall << std::endl;
				vel_x = 0;
			}
		}
		

		// Checks right collisions
		if (rightXCollision) {
			bool checkTopYPlatInBetween = platform.getY() >= topY && platform.getY() + 1 < bottomY;
			bool checkBottomYPlatInBetween = platform.getY() + platform.getHeight() >= topY && platform.getY() + platform.getHeight() < bottomY;
			if (checkTopYPlatInBetween || checkBottomYPlatInBetween) {
				moveRight = false;
				pos_x = platform.getX() - width;
				sprite.setPosition(pos_x, pos_y);
				std::cout << "RIGHT COLLISION" << std::endl;
			}
		}
	
		if (!playerTouchedBottom) {
			fall = true;
		}

	}
	std::cout << "=====================" << std::endl;

}

sf::Sprite Player::getSprite() {
	return sprite;
}