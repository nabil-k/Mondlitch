#pragma once
#include <SFML/Graphics.hpp>

class Platform {

	int width, height;
	float x, y;
	sf::Texture texture;
	sf::Sprite sprite;

	public:
		int getWidth(), getHeight();
		float getX(), getY();
		void update();
		sf::Sprite getSprite();

	Platform(float x, float y, int width, int height, sf::Image img, int img_coords[4]) {
		this->x = x;
		this->y = y;
		this->width = width;
		this-> height = height;
		texture.loadFromImage(img, sf::IntRect(img_coords[0], img_coords[1], img_coords[2], img_coords[3]));
		sprite.setTexture(texture);
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