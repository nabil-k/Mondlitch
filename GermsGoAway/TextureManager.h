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

		sf::Texture GrassTexture = sf::Texture();
		GrassTexture.loadFromImage(LevelSpriteSheet, sf::IntRect(177, 0, 16, 16));
		textures.insert({ "Grass", GrassTexture });

		// Character Texture Assets
		CharacterSpriteSheet.loadFromFile("./assets/characters.png");

		sf::Texture characterTextureIdle = sf::Texture();
		characterTextureIdle.loadFromImage(CharacterSpriteSheet, sf::IntRect(6, 72, 18, 23));
		textures.insert({"Player_Idle", characterTextureIdle});

		sf::Texture characterTextureWalk_1 = sf::Texture();
		characterTextureWalk_1.loadFromImage(CharacterSpriteSheet, sf::IntRect(38, 72, 18, 23));
		textures.insert({ "Player_Walk_1", characterTextureWalk_1 });

		sf::Texture characterTextureWalk_2 = sf::Texture();
		characterTextureWalk_2.loadFromImage(CharacterSpriteSheet, sf::IntRect(70, 72, 18, 23));
		textures.insert({ "Player_Walk_2", characterTextureWalk_2 });

		sf::Texture characterTextureWalk_3 = sf::Texture();
		characterTextureWalk_3.loadFromImage(CharacterSpriteSheet, sf::IntRect(102, 72, 19, 23));
		textures.insert({ "Player_Walk_3", characterTextureWalk_3 });

		sf::Texture characterTextureJump_1 = sf::Texture();
		characterTextureJump_1.loadFromImage(CharacterSpriteSheet, sf::IntRect(135, 72, 18, 23));
		textures.insert({ "Player_Jump_1", characterTextureJump_1 });

		sf::Texture characterTextureJump_2 = sf::Texture();
		characterTextureJump_2.loadFromImage(CharacterSpriteSheet, sf::IntRect(166, 72, 18, 23));
		textures.insert({ "Player_Jump_2", characterTextureJump_2 });

	}

};

sf::Texture& TextureManager::getTexture(std::string textureName) {
	if (textures.find(textureName) != textures.end()) {
		return textures.at(textureName);
	}
	else {
		std::cout << "Texture not found" << std::endl;
		std::cout << "Inputted Texture Name: " << textureName << std::endl;
	}
}
