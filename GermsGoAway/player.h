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
	sf::Clock animateTime;
	sf::Clock dt;
	std::vector<sf::Texture> textures;
	sf::Sprite sprite;
	sf::Image CharacterSpriteSheet;
	TextureManager* textureManager;


public:
	int getWidth(), getHeight();
	float getX(), getY();
	float getVelocityX();
	float jumpHeight;
	void update(std::vector<Platform> levelPlatforms, float dt);
	sf::Sprite getSprite();
	void jump();
	void changeSpriteTexture();
	// for animations
	float maxKeyframeTime;
	float timeSinceLastKeyframe;
	float walkFrame;
	bool checkIfPlayerFell();

	Player(TextureManager* textureManagerInitialized) {
		pos_x = 100.f;
		pos_y = 300.f;
		width = 18;
		height = 22;
		jumpHeight = 3.f;
		vel_x = 0;
		vel_y = 0;
		maxKeyframeTime = 1;
		timeSinceLastKeyframe = 0;
		walkFrame = 1;

		this->textureManager = textureManagerInitialized;
		// Preloading all player textures
		this->textures.push_back(textureManager->getTexture("Player_Idle"));
		this->textures.push_back(textureManager->getTexture("Player_Walk_1"));
		this->textures.push_back(textureManager->getTexture("Player_Walk_2"));
		this->textures.push_back(textureManager->getTexture("Player_Walk_3"));
		this->textures.push_back(textureManager->getTexture("Player_Jump_1"));
		this->textures.push_back(textureManager->getTexture("Player_Jump_2"));

		// Default texture set
		sprite.setTexture(textures.at(0));
		sprite.setOrigin({ 0, 0 });

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

float Player::getVelocityX() {
	return vel_x;
}


void Player::jump() {

}

bool Player::checkIfPlayerFell() {
	if (pos_y > 850) {
		return true;
	}
	return false;
}

void Player::changeSpriteTexture() {
	timeSinceLastKeyframe = animateTime.getElapsedTime().asSeconds();

	// Flips sprite based on if they're moving left/right
	if (vel_x > 0) {
		sprite.setOrigin({ 0, 0 });
		sprite.setScale({ 1, 1 });
	}
	else if (vel_x < 0) {
		sprite.setOrigin({ sprite.getLocalBounds().width, 0 });
		sprite.setScale({ -1, 1 });
	}

	// Animations for when character is on the ground
	if (vel_y == 0) {
		if (vel_x == 0) {
			sprite.setTexture(textures.at(0));
		}
		else if (vel_x > 0 || vel_x < 0) {
			if (timeSinceLastKeyframe > (maxKeyframeTime - (std::abs(vel_x) * .4))) {
				++walkFrame;
				if (walkFrame > 3) {
					walkFrame = 1;
				}
				sprite.setTexture(textures.at(walkFrame));
				animateTime.restart();
			}
		}
	}
	else if (vel_y > 0) {
		sprite.setTexture(textures.at(5));
		animateTime.restart();
	}
	else {
		sprite.setTexture(textures.at(4));
		animateTime.restart();
	}


}

void Player::update(std::vector<Platform> levelPlatforms, float dt) {
	std::cout << pos_y << std::endl;
	if (checkIfPlayerFell()) {
		vel_x = 0;
		vel_y = 0;
		pos_y = 500;
		pos_x = 100;
	}

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

			if (vel_x > -2) {
				vel_x -= gravity * 0.001802f;
			}
			pos_x += vel_x;
			sprite.move(vel_x, 0.f);
		}
	}
	else {
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

			if (vel_x < 2) {
				vel_x += gravity * 0.001802f;
			}

			pos_x += vel_x;

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
			pos_y -= jumpHeight;
			vel_y = -jumpHeight;
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
		if (platform.isCollidable()) {
			leftXCollission = (leftX > platform.getX()) && (leftX < (platform.getX() + platform.getWidth()));
			rightXCollision = (rightX > platform.getX()) && (rightX < (platform.getX() + platform.getWidth()));
			topYCollision = (topY > platform.getY()) && (topY < (platform.getY() + platform.getHeight()));
			bottomYCollision = (bottomY > platform.getY() && (bottomY < platform.getY() + platform.getHeight()));



			// Checks bottom collisions
			if (vel_y > 0) {
				float leftXCollission_bottom = (leftX + 1 > platform.getX()) && (leftX + 1 < (platform.getX() + platform.getWidth()));
				float rightXCollision_bottom = (rightX - 1 > platform.getX()) && (rightX - 1 < (platform.getX() + platform.getWidth()));
				if (bottomYCollision && (rightXCollision_bottom || leftXCollission_bottom)) {
					playerTouchedBottom = true;
					float adjustment = platform.getY() - height;
					pos_y = adjustment;
					bottomY = pos_y + height;
					sprite.setPosition(pos_x, adjustment);
					fall = false;
					vel_y = 0;
					std::cout << "bottom" << std::endl;
				}
			}



			// Checks top collisions
			if (vel_y < 0) {
				float leftXCollission_bottom = (leftX + 1 > platform.getX()) && (leftX + 1 < (platform.getX() + platform.getWidth()));
				float rightXCollision_bottom = (rightX - 1 > platform.getX()) && (rightX - 1 < (platform.getX() + platform.getWidth()));
				if (topYCollision && (rightXCollision_bottom || leftXCollission_bottom)) {
					float adjustment = platform.getY() + platform.getHeight();
					pos_y = adjustment;
					topY = pos_y;
					sprite.setPosition(pos_x, adjustment);
					vel_y = 0;
					std::cout << "top" << std::endl;
				}
			}

			// Checks left collisions
			if (vel_x < 0) {
				if (leftXCollission) {
					bool checkTopYPlatInBetween = platform.getY() > topY && platform.getY() + 1 < bottomY;
					bool checkBottomYPlatInBetween = platform.getY() + platform.getHeight() > topY && platform.getY() + platform.getHeight() < bottomY;
					if (checkTopYPlatInBetween || checkBottomYPlatInBetween) {
						moveLeft = false;
						pos_x = platform.getX() + platform.getWidth();
						leftX = pos_x;
						sprite.setPosition(pos_x, pos_y);
						vel_x = 0;
						std::cout << "left" << std::endl;
					}
				}
			}



			// Checks right collisions
			if (vel_x > 0) {
				if (rightXCollision) {
					bool checkTopYPlatInBetween = platform.getY() > topY && platform.getY() + 1 < bottomY;
					bool checkBottomYPlatInBetween = platform.getY() + platform.getHeight() > topY && platform.getY() + platform.getHeight() < bottomY;
					if (checkTopYPlatInBetween || checkBottomYPlatInBetween) {
						moveRight = false;
						pos_x = platform.getX() - width;
						rightX = (pos_x + width);
						sprite.setPosition(pos_x, pos_y);
						vel_x = 0;
						std::cout << "right" << std::endl;
					}
				}
			}


			if (!playerTouchedBottom) {
				fall = true;
			}
		}

	}

	changeSpriteTexture();


}

sf::Sprite Player::getSprite() {
	return sprite;
}

