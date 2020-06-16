#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.h"

class FlowerPlatform : public Platform {
	sf::String type = "Flower";
	bool collidable = false;
	using Platform::Platform;
};