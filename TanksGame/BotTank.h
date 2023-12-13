#pragma once
#include "Tank.h"

class BotTank: public Tank
{
public:
	BotTank(int level): Tank(90 * level) {};

	void move() {

		// search for userTank;
		// find a route
		// move there
		// when vertically/horizontally alligned, shoot()
	}

	void shoot() {
		// search for userTank;
		// if sees userTank, shoot
	}
};

