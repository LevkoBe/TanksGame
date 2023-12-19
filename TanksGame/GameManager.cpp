#include "GameManager.h"
#include "GameState.h"

GameManager::GameManager(int windowSize) : windowSize(windowSize), window(sf::VideoMode(windowSize, windowSize), "Tank Game"), renderer(windowSize) {}

void GameManager::run() {
    initWindow();

    while (window.isOpen()) {
        if (game) {
            auto commands = move(commander.processEvents(window));
            auto gamestate = game->update(move(commands));
            renderer.renderGame(window, gamestate);
        }
        else {
            renderer.renderMenu(window, game && game->isFinished(), unit);
            handleMenuInteractions();
        }
    }
}

void GameManager::handleMenuInteractions() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= window.getSize().x / 2 - 3 * unit / 2 && mousePos.x <= window.getSize().x / 2 + 3 * unit / 2 &&
                mousePos.y >= window.getSize().y / 2 - unit / 2 && mousePos.y <= window.getSize().y / 2 + unit / 2) {
                startNewGame();
            }
            else if (game && game->isFinished() && mousePos.x >= window.getSize().x / 2 - 50 &&
                mousePos.x <= window.getSize().x / 2 + 50 && mousePos.y >= window.getSize().y / 2 + 50 &&
                mousePos.y <= window.getSize().y / 2 + 100) {
                game.reset();  // Reset the game to nullptr, returning to the menu
            }
        }
    }
}


void GameManager::startNewGame() {
    game = std::make_unique<GameRun>(windowSize, gridSize, difficulty);
}

void GameManager::initWindow() {
    const float FPS = 10.0f; // for me it doesn't seem to change anything
    window.setFramerateLimit(FPS);
}
