#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.h"

class WallPlatform : public Platform {
	sf::String type = "Wall";
	bool collidable = true;
	using Platform::Platform;
};