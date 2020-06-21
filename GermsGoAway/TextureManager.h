#pragma once
#include <iostream>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class TextureManager {
	
	std::map<std::string, sf::Texture> textures;
	sf::Image LevelSpriteSheet;
	sf::Image CharacterSpriteSheet;
	sf::Image SkySpriteSheet;
	sf::Image MainMenuBackgroundSpriteSheet;
	sf::Image MainMenuTitleSpriteSheet;
	sf::Image GameOverTitleSpriteSheet;
	std::vector<sf::Texture> enemyTextures;



	public:
		sf::Texture& getTexture(std::string textureName);
		sf::Texture& getEnemyTexture(int index);


	TextureManager() {
		
		// Level Texture Assets
		LevelSpriteSheet.loadFromFile("./assets/sheet.png");

		sf::Texture GrassTexture = sf::Texture();
		GrassTexture.loadFromImage(LevelSpriteSheet, sf::IntRect(177, 0, 16, 16));
		textures.insert({ "Grass", GrassTexture });

		sf::Texture DirtTexture = sf::Texture();
		DirtTexture.loadFromImage(LevelSpriteSheet, sf::IntRect(112, 9, 16, 16));
		DirtTexture.setRepeated(true);
		textures.insert({ "Dirt", DirtTexture });

		sf::Texture WallTexture = sf::Texture();
		WallTexture.loadFromImage(LevelSpriteSheet, sf::IntRect(209, 8, 16, 16));
		textures.insert({ "Wall", WallTexture });

		sf::Texture RockTexture = sf::Texture();
		RockTexture.loadFromImage(LevelSpriteSheet, sf::IntRect(258, 80, 11, 16));
		textures.insert({ "Rock", RockTexture });

		sf::Texture FlowerTexture = sf::Texture();
		FlowerTexture.loadFromImage(LevelSpriteSheet, sf::IntRect(226, 80, 16, 16));
		textures.insert({ "Flower", FlowerTexture });

		sf::Texture CrateTexture = sf::Texture();
		CrateTexture.loadFromImage(LevelSpriteSheet, sf::IntRect(130, 64, 12, 16));
		textures.insert({ "Crate", CrateTexture });

		sf::Texture TreeTexture = sf::Texture();
		TreeTexture.loadFromImage(LevelSpriteSheet, sf::IntRect(36, 0, 73, 128));
		textures.insert({ "Tree", TreeTexture });


		sf::Texture HoleTexture = sf::Texture();
		HoleTexture.loadFromImage(LevelSpriteSheet, sf::IntRect(144, 112, 16, 16));
		textures.insert({ "Hole", HoleTexture });

		// Backdrop Assets
		SkySpriteSheet.loadFromFile("./assets/sky.png");
		sf::Texture SkyTexture = sf::Texture();
		SkyTexture.loadFromImage(SkySpriteSheet, sf::IntRect(0, 0, 1280, 720));
		SkyTexture.setRepeated(true);
		textures.insert({ "Sky", SkyTexture });

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

		sf::Texture EnemyTextureIdle = sf::Texture();
		EnemyTextureIdle.loadFromImage(CharacterSpriteSheet, sf::IntRect(9, 11, 18, 20));
		enemyTextures.push_back(EnemyTextureIdle);
		textures.insert({ "Enemy_Idle", EnemyTextureIdle });

		sf::Texture EnemyTextureWalk_1 = sf::Texture();
		EnemyTextureWalk_1.loadFromImage(CharacterSpriteSheet, sf::IntRect(40, 11, 18, 20));
		enemyTextures.push_back(EnemyTextureWalk_1);
		textures.insert({ "Enemy_Walk_1", EnemyTextureWalk_1 });

		sf::Texture EnemyTextureWalk_2 = sf::Texture();
		EnemyTextureWalk_2.loadFromImage(CharacterSpriteSheet, sf::IntRect(71, 11, 19, 20));
		enemyTextures.push_back(EnemyTextureWalk_2);
		textures.insert({ "Enemy_Walk_2", EnemyTextureWalk_2 });

		sf::Texture EnemyTextureWalk_3 = sf::Texture();
		EnemyTextureWalk_3.loadFromImage(CharacterSpriteSheet, sf::IntRect(104, 11, 19, 20));
		enemyTextures.push_back(EnemyTextureWalk_3);
		textures.insert({ "Enemy_Walk_3", EnemyTextureWalk_3 });

		// Main Menu Texture Assets
		MainMenuBackgroundSpriteSheet.loadFromFile("./assets/menu_background.png");
		MainMenuTitleSpriteSheet.loadFromFile("./assets/title.png");

		sf::Texture MainMenuBackgroundTexture = sf::Texture();
		MainMenuBackgroundTexture.loadFromImage(MainMenuBackgroundSpriteSheet, sf::IntRect(0, 0, 1280, 720));
		textures.insert({ "MainMenu_Background", MainMenuBackgroundTexture });

		sf::Texture MainMenuTitleTexture = sf::Texture();
		MainMenuTitleTexture.loadFromImage(MainMenuTitleSpriteSheet, sf::IntRect(0, 0, 620, 280));
		textures.insert({ "MainMenu_Title", MainMenuTitleTexture });

		// Main Menu Texture Assets
		GameOverTitleSpriteSheet.loadFromFile("./assets/gameover.png");

		sf::Texture GameOverTitleTexture = sf::Texture();
		GameOverTitleTexture.loadFromImage(GameOverTitleSpriteSheet, sf::IntRect(0, 0, 1280, 720));
		textures.insert({ "GameOver_Title", GameOverTitleTexture });

	}

};

sf::Texture& TextureManager::getEnemyTexture(int index) {
	return enemyTextures.at(index);
}

sf::Texture& TextureManager::getTexture(std::string textureName) {
	if (textures.find(textureName) != textures.end()) {
		return textures.at(textureName);
	}
	else {
		std::cout << "Texture not found" << std::endl;
		std::cout << "Inputted Texture Name: " << textureName << std::endl;
	}
}
