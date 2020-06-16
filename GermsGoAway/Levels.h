#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
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

	public:
		std::vector<Platform> getLevelOne();

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
					}
					y += 16;
				}
			}
		}


};

std::vector<Platform> Levels::getLevelOne() {
	return levelOne;
}