#pragma once
#include "Tank.h"
#include <string>

class BotTank: public Tank
{
public:
	BotTank(int level, int size): Tank(90 * level, size, getImageName(level)) {};

	void move() {

		// search for userTank;
		// find a route
		// move there
		// when vertically/horizontally alligned, shoot()
	}

	std::string getImageName(int level) {
		return "./images/prototank00" + std::to_string(level + 1) + ".png";
	}

	void shoot() {
		// search for userTank;
		// if sees userTank, shoot
	}
};

