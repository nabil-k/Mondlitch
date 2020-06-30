#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Platform {

	int width, height;
	float x, y;
	sf::Texture texture;
	sf::String type;

	public:
		float maxKeyframeTime = 0.25;
		float frame = 0;
		float timeSinceLastKeyframe = 0;
		sf::Clock animateTime;
		sf::Sprite sprite;
		int getWidth(), getHeight();
		float getX(), getY();
		bool isCollidable();
		void animate();
		void update();
		TextureManager* textureManager;
		bool animationCycleBack = false;
		std::string getType();
		sf::Sprite getSprite();

		Platform(float x, float y, int width, int height, TextureManager* textureManager, sf::String type) {
			this->type = type;
			this->x = x;
			this->y = y;
			this->width = width;
			this-> height = height;
			if (type != "Turn") {
				this->textureManager = textureManager;
				sprite.setTexture(textureManager->getTexture(type));
			}
			
			sprite.setPosition(sf::Vector2f(x, y));
		
		}


};

std::string Platform::getType() {
	return type;
}

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

bool Platform::isCollidable() {
	if (type == "Grass") {
		return true;
	}
	else if (type == "Dirt") {
		return true;
	}
	else if (type == "Wall") {
		return true;
	}
	else if (type == "Turn") {
		return true;
	}
	else {
		return false;
	}
}

void Platform::animate() {
	if (type == "Goal_1") {
		timeSinceLastKeyframe = animateTime.getElapsedTime().asSeconds();
		if (timeSinceLastKeyframe > maxKeyframeTime) {
			if (frame <= 2 && !animationCycleBack) {
				frame++;
			}
			if (frame > 2 && !animationCycleBack) {
				frame = 1;
				animationCycleBack = true;
			}
			else if (animationCycleBack) {
				frame--;
			}
			if (frame == 0) {
				animationCycleBack = false;
			}
			sprite.setTexture(textureManager->getGoalTexture(frame));
			animateTime.restart();
		}
	}

}

void Platform::update() {
	animate();
}

sf::Sprite Platform::getSprite() {
	return sprite;
}