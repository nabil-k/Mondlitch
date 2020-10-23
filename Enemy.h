#pragma once
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Platform.h"

class Enemy {
	int width, height;
	float pos_x, pos_y;
	float vel_x, vel_y;
	bool top_collision, bottom_collision, left_collision, right_collision;
	float gravity = 32;
	bool fall = true;
	TextureManager* textureManager;
	sf::Sprite sprite;
	// for animations
	sf::Clock animateTime;
	float maxKeyframeTime;
	float timeSinceLastKeyframe;
	float walkFrame;


	public:
		int getWidth(), getHeight();
		float getX(), getY();
		float getVelocityX();
		bool canMoveLeft, canMoveRight;
		void moveLeft();
		void moveRight();
		sf::Sprite getSprite();
		void changeSpriteTexture();
		void update(std::vector<Platform> levelPlatforms);

		Enemy(float x, float y, TextureManager* textureManager) {

			pos_x = x;
			pos_y = y;
			width = 15;
			height = 20;
			vel_x = 0;
			vel_y = 0;
			maxKeyframeTime = 0.5;
			canMoveLeft = false;
			canMoveRight = true;
			this->textureManager = textureManager;

			sprite.setTexture(textureManager->getEnemyTexture(0));
			sprite.setOrigin({ 0, 0 });
			sprite.setPosition(sf::Vector2f(pos_x, pos_y));
		}


};

int Enemy::getWidth() {
	return width;
}

int Enemy::getHeight() {
	return height;
}

float Enemy::getX() {
	return pos_x;
}

float Enemy::getY() {
	return pos_y;
}

float Enemy::getVelocityX() {
	return vel_x;
}

void Enemy::moveLeft() {
	if (vel_x > -1) {
		vel_x += -gravity * 0.001802f;
	}

	pos_x += vel_x;
}


void Enemy::moveRight() {
	if (vel_x < 1) {
		vel_x += gravity * 0.001802f;
	}

	pos_x += vel_x;
}

void Enemy::changeSpriteTexture() {
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

	// When enemy is on the ground
	if (vel_y == 0) {
		if (vel_x == 0) {
			sprite.setTexture(textureManager->getEnemyTexture(0));
		}
		else if (vel_x > 0 || vel_x < 0) {
			if (timeSinceLastKeyframe > (maxKeyframeTime - (std::abs(vel_x) * .3))) {
				++walkFrame;
				if (walkFrame > 3) {
					walkFrame = 1;
				}
				sprite.setTexture(textureManager->getEnemyTexture(walkFrame));
				animateTime.restart();
			}
		}
	}
}


void Enemy::update(std::vector<Platform> levelPlatforms) {

	// Controls how player falls
	if (fall) {
		if (vel_y < 10) {
			vel_y += gravity * 0.001802f * 2;
		}
		pos_y += vel_y;
		sprite.move(0.f, vel_y);

	}

	if (canMoveLeft) {
		moveLeft();
	}

	if (canMoveRight) {
		moveRight();
	}

	// Player's hitbox
	float leftX = pos_x;
	float rightX = (pos_x + width);
	float topY = pos_y;
	float bottomY = pos_y + height;

	// Tracks if player can move in a certain direction
	bool playerTouchedBottom = false;
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
					float adjustment = platform.getY() - height;
					playerTouchedBottom = true;
					pos_y = adjustment;
					bottomY = pos_y + height;
					vel_y = 0;
					sprite.setPosition(pos_x, adjustment);
		
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
					vel_y = 0;
					sprite.setPosition(pos_x, adjustment);
			

				}
			}
			// Checks left collisions
			if (vel_x < 0) {
				if (leftXCollission) {
					bool checkTopYPlatInBetween = platform.getY() > topY && platform.getY() + 1 < bottomY;
					bool checkBottomYPlatInBetween = platform.getY() + platform.getHeight() > topY && platform.getY() + platform.getHeight() < bottomY;
					if (checkTopYPlatInBetween || checkBottomYPlatInBetween) {
						pos_x = platform.getX() + platform.getWidth();
						leftX = pos_x;
						sprite.setPosition(pos_x, pos_y);
						vel_x = 0;
						canMoveLeft = false;
						canMoveRight = true;
				
					}
				}
			}
			// Checks right collisions
			if (vel_x > 0) {
				if (rightXCollision) {
					bool checkTopYPlatInBetween = platform.getY() > topY && platform.getY() + 1 < bottomY;
					bool checkBottomYPlatInBetween = platform.getY() + platform.getHeight() > topY && platform.getY() + platform.getHeight() < bottomY;
					if (checkTopYPlatInBetween || checkBottomYPlatInBetween) {
						pos_x = platform.getX() - width;
						rightX = (pos_x + width);
						sprite.setPosition(pos_x, pos_y);
						vel_x = 0;
						canMoveLeft = true;
						canMoveRight = false;
						
					}
				}
			}

			if (!playerTouchedBottom) {
				fall = true;
			}
		}
		changeSpriteTexture();
	}
}

sf::Sprite Enemy::getSprite(){
	return sprite;
}