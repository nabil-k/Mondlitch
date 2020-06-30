#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cmath>
#include "Platform.h"
#include "WallPlatform.h"
#include "RockPlatform.h"
#include "GrassPlatform.h"
#include "FlowerPlatform.h"
#include "DirtPlatform.h"
#include "CratePlatform.h"
#include "Enemy.h"
#include "TextureManager.h"

class Levels {
	
	std::ifstream levelOneFile;
	std::ifstream levelTwoFile;
	std::string row;
	// Level One Objs
	std::vector<Platform> levelOneStructures;
	std::vector<Enemy> levelOneEnemies;
	std::vector< std::vector < std::vector<Platform> > > levelOneCollisionSections;
	// Level Two Objs
	std::vector<Platform> levelTwoStructures;
	std::vector<Enemy> levelTwoEnemies;
	std::vector< std::vector < std::vector<Platform> > > levelTwoCollisionSections;

	float collisionSectionRows = 0;
	float collisionSectionColumns = 0;

	public:
		std::vector<Platform>& getLevelOneStructures();
		std::vector<Enemy>& getLevelOneEnemies();
		std::vector<Platform> getPlatformNearPlayerLevelOne(float playerX, float playerY);

		std::vector<Platform>& getLevelTwoStructures();
		std::vector<Enemy>& getLevelTwoEnemies();
		std::vector<Platform> getPlatformNearPlayerLevelTwo(float playerX, float playerY);

		TextureManager* textureManager;

		void createLevel(std::ifstream& file, std::vector<Platform>& levelStructures, std::vector<Enemy>& levelEnemies, std::vector< std::vector < std::vector<Platform> > >& levelCollisionSections);

		Levels(TextureManager* textureManager) {
			this->textureManager = textureManager;
			// Creates level one from the text file
			levelOneFile.open("./levels/level_1.txt");
			if (!levelOneFile) {
				std::cout << "Unable to read level one file" << std::endl;
			}
			else {

				createLevel(levelOneFile, levelOneStructures, levelOneEnemies, levelOneCollisionSections);
			}

			// Creates level two from the text file
			levelTwoFile.open("./levels/level_2.txt");
			if (!levelTwoFile) {
				std::cout << "Unable to read level one file" << std::endl;
			}
			else {

				createLevel(levelTwoFile, levelTwoStructures, levelTwoEnemies, levelTwoCollisionSections);
			}
		}


};

void Levels::createLevel(std::ifstream& file, std::vector<Platform>& levelStructures, std::vector<Enemy>& levelEnemies, std::vector< std::vector < std::vector<Platform> > >& levelCollisionSections) {
	float y = 0;
	while (std::getline(file, row)) {
		for (float i = 0; i < row.length(); ++i) {

			// Adding platforms
			float x = i * 16.f;
			char platform = row.at(i);

			if (platform == 'G') {
				GrassPlatform p = GrassPlatform(x, y, 16, 16, textureManager, "Grass");
				levelStructures.push_back(p);

			}
			else if (platform == 'U') {
				DirtPlatform p = DirtPlatform(x, y, 16, 16, textureManager, "Dirt");
				levelStructures.push_back(p);

			}
			else if (platform == 'W') {
				WallPlatform p = WallPlatform(x, y, 16, 16, textureManager, "Wall");
				levelStructures.push_back(p);

			}
			else if (platform == 'R') {
				RockPlatform p = RockPlatform(x, y, 16, 16, textureManager, "Rock");
				levelStructures.push_back(p);

			}
			else if (platform == 'F') {
				FlowerPlatform p = FlowerPlatform(x, y, 16, 16, textureManager, "Flower");
				levelStructures.push_back(p);

			}
			else if (platform == 'C') {
				CratePlatform p = CratePlatform(x, y, 16, 16, textureManager, "Crate");
				levelStructures.push_back(p);

			}
			else if (platform == 'H') {
				Platform p = Platform(x, y, 16, 16, textureManager, "Hole");
				levelStructures.push_back(p);

			}
			else if (platform == 'E') {
				Enemy e = Enemy(x, y, textureManager);
				std::cout << "Enemy Created: " << x << "," << y << std::endl;
				levelEnemies.push_back(e);
			}
			else if (platform == 'T') {
				Platform p = Platform(x, y, 16, 16, textureManager, "Turn");
				levelStructures.push_back(p);

			}
			else if (platform == '0') {
				Platform p = Platform(x, y, 16, 16, textureManager, "Goal_1");
				levelStructures.push_back(p);

			}

			// By the end of the loop collisionSectionRows and collisionSectionColumns will be set to the values of the last platform
			collisionSectionColumns = std::ceil(x / 320.f);
		}
		collisionSectionRows = std::ceil(y / 180.f);

		y += 16;
	}

	// Adding platforms to their collision sections
	for (int r = 0; r < collisionSectionRows; r++) {
		std::vector< std::vector<Platform> > row;
		levelCollisionSections.push_back(row);
		for (int c = 0; c < collisionSectionColumns; c++) {
			std::vector<Platform> column;
			levelCollisionSections[r].push_back(column);
		}
	}

	for (int i = 0; i < levelStructures.size(); i++) {
		Platform p = levelStructures[i];

		int sectionRowIndex = std::ceil(p.getY() / 180) - 1;
		if (sectionRowIndex == -1) {
			sectionRowIndex = 0;
		}

		int sectionColumnIndex = std::ceil(p.getX() / 320) - 1;
		if (sectionColumnIndex == -1) {
			sectionColumnIndex = 0;
		}

		levelCollisionSections[sectionRowIndex][sectionColumnIndex].push_back(levelStructures[i]);
	}

	collisionSectionRows = 0;
	collisionSectionColumns = 0;
}

std::vector<Platform>& Levels::getLevelOneStructures() {
	return levelOneStructures;
}

std::vector<Enemy>& Levels::getLevelOneEnemies() {
	return levelOneEnemies;
}

std::vector<Platform> Levels::getPlatformNearPlayerLevelOne(float playerX, float playerY) {
	int PlayerColumnIndex = std::ceil(playerX / 320.f) - 1;
	int PlayerRowIndex = std::ceil(playerY / 180.f) - 1;

	if (PlayerColumnIndex == -1) {
		PlayerColumnIndex = 0;

	}

	if (PlayerRowIndex == -1) {
		PlayerRowIndex = 0;

	}
	std::cout << playerX << std::endl;
	std::cout << playerY << std::endl;
	std::cout << PlayerColumnIndex << std::endl;
	std::cout << PlayerRowIndex << std::endl;
	return levelOneCollisionSections[PlayerRowIndex][PlayerColumnIndex];
}


std::vector<Platform>& Levels::getLevelTwoStructures() {
	return levelTwoStructures;
}

std::vector<Enemy>& Levels::getLevelTwoEnemies() {
	return levelTwoEnemies;
}

std::vector<Platform> Levels::getPlatformNearPlayerLevelTwo(float playerX, float playerY) {
	int PlayerColumnIndex = std::ceil(playerX / 320.f) - 1;
	int PlayerRowIndex = std::ceil(playerY / 180.f) - 1;

	if (PlayerColumnIndex == -1) {
		PlayerColumnIndex = 0;

	}

	if (PlayerRowIndex == -1) {
		PlayerRowIndex = 0;

	}

	return levelTwoCollisionSections[PlayerRowIndex][PlayerColumnIndex];
}