#pragma once
#include <iostream>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class TextureManager {
	
	std::map<std::string, sf::Texture> textures;
	sf::Image LevelSpriteSheet;
	sf::Image CharacterSpriteSheet;


	public:
		sf::Texture& getTexture(std::string textureName);

	TextureManager() {
		// Level Texture Assets
		LevelSpriteSheet.loadFromFile("./assets/sheet.png");

		sf::Texture dirtTexture = sf::Texture();
		dirtTexture.loadFromImage(LevelSpriteSheet, sf::IntRect(177, 0, 16, 16));
		textures.insert({ "Dirt", dirtTexture });

		// Character Texture Assets
		CharacterSpriteSheet.loadFromFile("./assets/characters_hitboxes.png");

		sf::Texture characterTextureIdle = sf::Texture();
		characterTextureIdle.loadFromImage(CharacterSpriteSheet, sf::IntRect(9, 42, 15, 22));
		textures.insert({"IdlePlayer", characterTextureIdle});

	}

};

sf::Texture& TextureManager::getTexture(std::string textureName) {
	if (textures.find(textureName) != textures.end()) {
		return textures.at(textureName);
	}
	else {
		std::cout << "Texture not found" << std::endl;
	}
}
