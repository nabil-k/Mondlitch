#pragma once
#include <SFML/Graphics.hpp>

class Player {
	int width, height;
	float x, y;
	bool top_collision, bottom_collision, left_collision, right_collision;
	sf::Texture texture;
	sf::Sprite sprite;

	public:
		int getWidth(), getHeight();
		float getX(), getY();
		void update();
		sf::Sprite getSprite();
	
	Player(sf::Image img){
		x = 640.f;
		y = 360.f;
		texture.loadFromImage(img, sf::IntRect(9, 42, 14, 21));
		sprite.setTexture(texture);
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

void Player::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		sprite.move(sf::Vector2f(0.f, -10.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		sprite.move(sf::Vector2f(0.f,10.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sprite.move(sf::Vector2f(-10.f,0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sprite.move(sf::Vector2f(10.f, 0.f));
	}
}

sf::Sprite Player::getSprite() {
	return sprite;
}