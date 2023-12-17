#pragma once
#include "GameRun.h"
#include "Renderer.h"
#include "UserCommandHandler.h"
#include <SFML/Graphics.hpp>
#include "Tank.h"

class GameManager
{
	UserCommandHandler commander;
	GameRun game;
	Renderer renderer;
	Tank sampleTank;
	int windowSize;
	sf::RenderWindow window;

public:
	GameManager(int windowSize, int gridSize, int difficulty);
	
	void run();

	void initWindow();
};

