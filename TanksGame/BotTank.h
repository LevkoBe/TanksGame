#pragma once
#include "Tank.h"
#include <string>

class BotTank: public Tank
{
	int maxSpeed;
public:
	BotTank(int level, int size): Tank(level, size, determineImageName(level % 4)), maxSpeed(level * 10) {};

	int getMaxSpeed() const;

	std::string determineImageName(int level) const {
		return "./images/prototank00" + std::to_string(level + 1) + ".png";
	}
};

