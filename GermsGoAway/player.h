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
		pos_x = 200.f;
		pos_y = 0.f;
		width = 14;
		height = 21;
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
	
	this->levelPlatforms = levelPlatforms;

	float leftX = pos_x;
	float rightX = (pos_x + width);

	float leftAndRightTopY = pos_y + 3;
	float leftAndRightBottomY = pos_y + height - 3;

	float topY = pos_y;
	float bottomY = pos_y + height + (vel_y*(1.f/2.f));
	bool fall = true;
	bool moveRight = true;
	bool moveLeft = true;
	bool moveUp = true;
	bool leftXCollission, rightXCollision, topYCollision, bottomYCollision;

	for (auto &platform : levelPlatforms) {
		leftXCollission = (
			(leftX >= platform.getX()) && (leftX <= (platform.getX() + platform.getWidth())) &&
			((leftAndRightTopY <= (platform.getY() + platform.getHeight())) && (leftAndRightBottomY >= (platform.getY())))
		);
		rightXCollision = (
					(rightX >= platform.getX()) && (rightX <= (platform.getX() + platform.getWidth())) &&
					(leftAndRightTopY <= (platform.getY() + platform.getHeight()) && leftAndRightBottomY >= (platform.getY()))
		);

		topYCollision = (
			(topY >= platform.getY()) && (topY <= (platform.getY() + platform.getHeight())) &&
			(
				(rightX >= platform.getX()) && (rightX <= (platform.getX() + platform.getWidth())) ||
				(leftX >= platform.getX()) && (leftX <= (platform.getX() + platform.getWidth()))
			)
		);
		bottomYCollision = (
			(bottomY >= platform.getY()) && (bottomY <= (platform.getY() + platform.getHeight())) &&
			(
				(rightX - 5.f >= platform.getX()) && (rightX - 5.f <= (platform.getX() + platform.getWidth())) ||
				(leftX + 5.f >= platform.getX()) && (leftX + 5.f <= (platform.getX() + platform.getWidth()))
			)
		);
		
		if (leftXCollission) {
			moveLeft = false;
		}
		if (rightXCollision) {
			moveRight = false;
		}

		if (bottomYCollision) {
			fall = false;
		}
		if (topYCollision) {
			moveUp = false;
		}
	}

	if (fall) {
		std::cout << "Falling" << std::endl;
	}

	if (!moveLeft) {
		std::cout << "Left is hit" << std::endl;
		
	}
	if (!moveRight) {
		std::cout << "Right is hit" << std::endl;
		
	}
	if (!moveUp) {
		std::cout << "Top is hit" << std::endl;
	}

	if (fall) {
		//std::cout << vel_y << std::endl;
		if (dt > 0.015f) {
			dt = 0.015f;
		}
		if (vel_y < 5) {
			vel_y += gravity * dt;
		}
		
		pos_y += vel_y;
		sprite.move(0.f, vel_y);
		
	}else {
		vel_y = 0;
	}

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (moveUp) {
			sprite.move(0.f, -5.f);
			pos_y -= 5;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		sprite.move(0.f, 5.f);
		pos_y += 5;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (moveLeft) {
			sprite.move(-3.f, 0.f);
			pos_x -= 3;
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		if (moveRight) {
			sprite.move(3.f, 0.f);
			pos_x += 3;
		}

	}
	

	
}

sf::Sprite Player::getSprite() {
	return sprite;
}