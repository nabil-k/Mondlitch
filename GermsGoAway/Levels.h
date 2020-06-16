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
							std::cout << x << " " << y << std::endl;
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