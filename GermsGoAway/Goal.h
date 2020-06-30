#pragma once
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "TextureManager.h"

class Goal : public Platform {

	using Platform::Platform;
	bool collidable = false;

	
};