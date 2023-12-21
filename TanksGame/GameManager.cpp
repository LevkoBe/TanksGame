#include "GameManager.h"
#include "GameState.h"

GameManager::GameManager(int windowSize) : runningState(Menu), windowSize(windowSize),
window(sf::VideoMode(windowSize, windowSize), "Tank Game"), renderer(windowSize) {
    commander.setWindowSize(windowSize);
}

void GameManager::pause() {
    runningState = Paused;
}

void GameManager::run() {
    initWindow();

    while (window.isOpen()) {
        if (game) {
            if (runningState == Running)
            {
                auto commands = move(commander.processEvents(window));
                for (auto& command : commands) {
                    if (command == Pause) { pause(); }
                }
                if (runningState != Paused) {
                    auto gamestate = game->update(move(commands));
                    runningState = renderer.renderGame(window, gamestate);
                }
            }
            else {
                int buttonsNumber = 2;
                switch (runningState)
                {
                case Won:
                    renderer.renderPause(window, move(std::vector<std::string>{"You won!\nNext level", "Menu"}));
                    break;
                case Lost:
                    renderer.renderPause(window, move(std::vector<std::string>{"You lost...\nRestart", "Menu"}));
                    break;
                case Paused:
                    renderer.renderPause(window, move(std::vector<std::string>{"Continue", "Restart", "Menu"}));
                    buttonsNumber++;
                    break;
                default:
                    break;
                }
                auto command = commander.handlePause(window, buttonsNumber);
                handlePause(command);

            }
        }
        else {
            renderer.renderMenu(window, gridSize, difficulty);
            auto command = commander.handleMenuInteractions(window);
            handleMenuInteractions(command);
        }
    }
}

void GameManager::handlePause(Command command) {
    switch (command)
    {
    case FirstButtonPressed:
        switch (runningState)
        {
        case Won:
            difficulty++;
        case Lost:
            startNewGame(std::move(*game));
        case Paused:
            runningState = Running;
        default:
            break;
        }
        break;
    case SecondLeftPressed:
        startNewGame(std::move(*game));
        runningState = Running;
        break;
    case ThirdLeftPressed:
        break;
    case LastButtonPressed:
        game.reset(); // nullptr => menu
        break;
    case Menu:
        break;
    default:
        break;
    }
}

void GameManager::handleMenuInteractions(Command command) {
    switch (command)
    {
    case FirstButtonPressed:
        startNewGame();
        runningState = Running;
        break;
    case SecondLeftPressed:
        gridSize = gridSize <= 2 ? gridSize : --gridSize;
        break;
    case SecondRightPressed:
        gridSize++;
        break;
    case ThirdLeftPressed:
        difficulty = difficulty <= 1 ? difficulty : --difficulty;
        break;
    case ThirdRightPressed:
        difficulty++;
        break;
    case LastButtonPressed:
        window.close();
        break;
    default:
        break;
    }
}


void GameManager::startNewGame() {
    game = std::make_unique<GameRun>(windowSize, gridSize, difficulty);
}

void GameManager::startNewGame(GameRun previousGame) {
    game = std::make_unique<GameRun>(windowSize, gridSize, difficulty, std::move(previousGame));
}

void GameManager::initWindow() {
    const float FPS = 600.0f; // for me it doesn't seem to change anything
    window.setFramerateLimit(FPS);
}
