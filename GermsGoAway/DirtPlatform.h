#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.h"

class DirtPlatform : public Platform {
	sf::String type = "Dirt";
	bool collidable = true;
	using Platform::Platform;
};