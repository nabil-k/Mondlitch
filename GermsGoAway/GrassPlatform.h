#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.h"

class GrassPlatform : public Platform {
	sf::String type = "Grass";
	bool collidable = true;
	using Platform::Platform;
};