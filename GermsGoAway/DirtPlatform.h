#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.h"

class DirtPlatform : public Platform {
	bool collidable = true;
	using Platform::Platform;
};