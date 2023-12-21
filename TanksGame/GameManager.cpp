#include "GameManager.h"
#include "GameState.h"

GameManager::GameManager(int windowSize) : windowSize(windowSize), window(sf::VideoMode(windowSize, windowSize), "Tank Game"), renderer(windowSize) {}

void GameManager::run() {
    initWindow();

    while (window.isOpen()) {
        if (game) {
            if (game->isFinished())
            {
                auto command = commander.checkButtonsPressed(window);
                handleMenuInteractions(command);
            }
            else {
                auto commands = move(commander.processEvents(window));
                auto gamestate = game->update(move(commands));
                renderer.renderGame(window, gamestate);
            }
        }
        else {
            renderer.renderMenu(window);
            auto command = commander.checkButtonsPressed(window);
            handleMenuInteractions(command);
        }
    }
}

void GameManager::handleMenuInteractions(Command command) {
    switch (command)
    {
    case FirstButtonPressed:
        if (game) {
            game.reset();  // Reset the game to nullptr, returning to the menu
        }
        else {
            startNewGame();
        }
        break;
    case SecondLeftPressed:
        gridSize--;
        break;
    case SecondRightPressed:
        gridSize++;
        break;
    case ThirdLeftPressed:
        difficulty--;
        break;
    case ThirdRightPressed:
        difficulty++;
        break;
    case FourthButtonPressed:
        break;
    default:
        break;
    }
}


void GameManager::startNewGame() {
    game = std::make_unique<GameRun>(windowSize, gridSize, difficulty);
}

void GameManager::initWindow() {
    const float FPS = 600.0f; // for me it doesn't seem to change anything
    window.setFramerateLimit(FPS);
}
