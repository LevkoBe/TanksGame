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
	GameManager(int windowSize) : windowSize(windowSize), window(sf::VideoMode(windowSize, windowSize), "Tank Game") {};
	void run() {
		initWindow();
		while (window.isOpen()) {
			auto commands = move(commander.processEvents(window));
			game.update(move(commands));
			renderer.render(window);
		}
	}

	void initWindow() {
		// Initialize window properties
	}
};

