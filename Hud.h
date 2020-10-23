#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"


class Hud {
	public:
		int lives = 3;
		std::vector< sf::Sprite > hearts;
		void update(int playerLives);
		std::vector< sf::Sprite >& getHearts();
		Hud(TextureManager* textureManager) {
			float screenWidth = 1280;
			for (int i = 1; i <= lives; i++) {
				
				sf::Sprite heart(textureManager->getTexture("HealthPoint"));
				float heartX = screenWidth - (38 * i);
				heart.setPosition(heartX,0.f);
				hearts.push_back(heart);
			}
		}
};

void Hud::update(int playerLives) {

}

std::vector< sf::Sprite >& Hud::getHearts() {
	return hearts;
}
