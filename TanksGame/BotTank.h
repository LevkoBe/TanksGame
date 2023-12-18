#pragma once
#include "Tank.h"
#include <string>

class BotTank: public Tank
{
	int maxSpeed;
public:
	BotTank(int level, int size): Tank(90 * level, size, determineImageName(level)), maxSpeed(level * 10) {};

	int getMaxSpeed() const;

	void move() {

		// search for userTank;
		// find a route
		// move there
		// when vertically/horizontally alligned, shoot()
	}

	std::string determineImageName(int level) const {
		return "./images/prototank00" + std::to_string(level + 1) + ".png";
	}

	void shoot() {
		// search for userTank;
		// if sees userTank, shoot
	}
};

