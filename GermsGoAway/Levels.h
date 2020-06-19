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
#include "TextureManager.h"

class Levels {
	
	std::ifstream levelOneFile;
	std::string row;
	std::vector<Platform> levelOne;
	std::vector< std::vector < std::vector<Platform> > > levelOneCollisionSections;
	float collisionSectionRows = 0;
	float collisionSectionColumns = 0;

	public:
		std::vector<Platform> getLevelOne();
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
							levelOne.push_back(p);
							
						}
						else if (platform == 'U') {
							DirtPlatform p = DirtPlatform(x, y, 16, 16, textureManager, "Dirt");
							levelOne.push_back(p);
							
						}
						else if (platform == 'W') {
							WallPlatform p = WallPlatform(x, y, 16, 16, textureManager, "Wall");
							levelOne.push_back(p);
							
						}
						else if (platform == 'R') {
							RockPlatform p = RockPlatform(x, y, 16, 16, textureManager, "Rock");
							levelOne.push_back(p);
							
						}
						else if (platform == 'F') {
							FlowerPlatform p = FlowerPlatform(x, y, 16, 16, textureManager, "Flower");
							levelOne.push_back(p);
							
						}
						else if (platform == 'C') {
							CratePlatform p = CratePlatform(x, y, 16, 16, textureManager, "Crate");
							levelOne.push_back(p);
							
						}
						else if (platform == 'H') {
							Platform p = Platform(x, y, 16, 16, textureManager, "Hole");
							levelOne.push_back(p);

						}
					// By the end of the loop collisionSectionRows and collisionSectionColumns will be set to the values of the last platform
						collisionSectionColumns = std::ceil(x / 640.f);
					}
					collisionSectionRows = std::ceil(y / 360.f);

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

				for (int i = 0; i < levelOne.size(); i++) {
					Platform p = levelOne[i];
					
					int sectionRowIndex = std::ceil(p.getY() / 360) - 1;
					if (sectionRowIndex == -1) {
						sectionRowIndex = 0;
					}

					int sectionColumnIndex = std::ceil(p.getX() / 640) - 1;
					if (sectionColumnIndex == -1) {
						sectionColumnIndex = 0;
					}
					
					levelOneCollisionSections[sectionRowIndex][sectionColumnIndex].push_back(levelOne[i]);
				}
				
			}
		}


};

//std::vector<Platform> Levels::addPlatformToCollisionSectionLevelOne(Platform platform) {
	//return 
//}

std::vector<Platform> Levels::getLevelOne() {
	return levelOne;
}

std::vector<Platform> Levels::getPlatformNearPlayerLevelOne(float playerX, float playerY) {
	int PlayerColumnIndex = std::ceil(playerX / 640.f) - 1;
	int PlayerRowIndex = std::ceil(playerY / 360.f) - 1;
	std::cout << "Getting nearby platforms" << std::endl;
	return levelOneCollisionSections[PlayerRowIndex][PlayerColumnIndex];
}