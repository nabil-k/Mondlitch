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
	std::string row;
	std::vector<Platform> levelOneStructures;
	std::vector<Enemy> levelOneEnemies;
	std::vector< std::vector < std::vector<Platform> > > levelOneCollisionSections;
	float collisionSectionRows = 0;
	float collisionSectionColumns = 0;

	public:
		std::vector<Platform>& getLevelOneStructures();
		std::vector<Enemy>& getLevelOneEnemies();
		std::vector<Platform> getPlatformNearPlayerLevelOne(float playerX, float playerY);

		Levels(TextureManager* textureManager) {

			// Creates level one from the text file
			levelOneFile.open("./levels/level_1.txt");
			if (!levelOneFile) {
				std::cout << "Unable to read level one file" << std::endl;
			}
			else {
				float y = 0;
				while (std::getline(levelOneFile, row)) {
					for (float i = 0; i < row.length(); ++i) {

						// Adding platforms
						float x = i * 16.f;
						char platform = row.at(i);

						if (platform == 'G') {
							GrassPlatform p = GrassPlatform(x, y, 16, 16, textureManager, "Grass");
							levelOneStructures.push_back(p);
							
						}
						else if (platform == 'U') {
							DirtPlatform p = DirtPlatform(x, y, 16, 16, textureManager, "Dirt");
							levelOneStructures.push_back(p);
							
						}
						else if (platform == 'W') {
							WallPlatform p = WallPlatform(x, y, 16, 16, textureManager, "Wall");
							levelOneStructures.push_back(p);
							
						}
						else if (platform == 'R') {
							RockPlatform p = RockPlatform(x, y, 16, 16, textureManager, "Rock");
							levelOneStructures.push_back(p);
							
						}
						else if (platform == 'F') {
							FlowerPlatform p = FlowerPlatform(x, y, 16, 16, textureManager, "Flower");
							levelOneStructures.push_back(p);
							
						}
						else if (platform == 'C') {
							CratePlatform p = CratePlatform(x, y, 16, 16, textureManager, "Crate");
							levelOneStructures.push_back(p);
							
						}
						else if (platform == 'H') {
							Platform p = Platform(x, y, 16, 16, textureManager, "Hole");
							levelOneStructures.push_back(p);

						}
						else if (platform == 'E') {
							Enemy e = Enemy(x, y, textureManager);
							std::cout << "Enemy Created: " << x << "," << y << std::endl;
							levelOneEnemies.push_back(e);
						}
						else if (platform == 'T') {
							Platform p = Platform(x, y, 16, 16, textureManager, "Turn");
							levelOneStructures.push_back(p);
						
						}
						else if (platform == '0') {
							Platform p = Platform(x, y, 16, 16, textureManager, "Goal_1");
							levelOneStructures.push_back(p);

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
					levelOneCollisionSections.push_back(row);
					for (int c = 0; c < collisionSectionColumns; c++) {
						std::vector<Platform> column;
						levelOneCollisionSections[r].push_back(column);
					}
				}

				for (int i = 0; i < levelOneStructures.size(); i++) {
					Platform p = levelOneStructures[i];
					
					int sectionRowIndex = std::ceil(p.getY() / 180) - 1;
					if (sectionRowIndex == -1) {
						sectionRowIndex = 0;
					}

					int sectionColumnIndex = std::ceil(p.getX() / 320) - 1;
					if (sectionColumnIndex == -1) {
						sectionColumnIndex = 0;
					}
					
					levelOneCollisionSections[sectionRowIndex][sectionColumnIndex].push_back(levelOneStructures[i]);
				}
				
			}
		}


};


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

	return levelOneCollisionSections[PlayerRowIndex][PlayerColumnIndex];
}