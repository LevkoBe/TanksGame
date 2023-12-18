#include "GameManager.h"
#include "GameState.h"

GameManager::GameManager(int windowSize, int gridSize, int difficulty) : windowSize(windowSize), window(sf::VideoMode(windowSize, windowSize), "Tank Game"), game(windowSize, gridSize, difficulty), renderer(windowSize) {};

void GameManager::run() {
	initWindow();
	while (window.isOpen()) {
		auto commands = move(commander.processEvents(window));
		auto gamestate = game.update(move(commands));
		renderer.render(window, gamestate);
	}
}

void GameManager::initWindow() {
	const float FPS = 120.0f;
	window.setFramerateLimit(FPS);
}
