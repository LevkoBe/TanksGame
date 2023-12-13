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
	int windowSize = 800;
	sf::RenderWindow window;

public:
	GameManager(int windowSize, int gridSize);
	
	void run();

	void initWindow();
};

