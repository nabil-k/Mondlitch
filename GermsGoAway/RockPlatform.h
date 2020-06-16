#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.h"

class RockPlatform : public Platform {
	sf::String type = "Rock";
	bool collidable = false;
	using Platform::Platform;
};