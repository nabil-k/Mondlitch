#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.h"

class CratePlatform : public Platform {
	sf::String type = "Crate";
	bool collidable = false;
	using Platform::Platform;
};