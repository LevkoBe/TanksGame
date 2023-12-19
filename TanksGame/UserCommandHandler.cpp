#include "UserCommandHandler.h"

std::vector<Command> UserCommandHandler::processEvents(sf::RenderWindow& window) { // (: I wanted to give a window, instead of a reference
    sf::Event event;
    commands = std::vector<Command>();
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::TextEntered) {
            handleTextEvent(event);
        }
        else if (event.type == sf::Event::KeyPressed) {
            handleKeyEvent(event);
        }
    }

    return commands;
}

void UserCommandHandler::handleTextEvent(sf::Event& event) {
    if (event.text.unicode < 128) {
        if (event.text.unicode == '\b' && !userInput.empty()) { // Backspace
            userInput.pop_back();
        }
        else if ((event.text.unicode == '\r' || event.text.unicode == '\n')) { // Enter
            userInput += "\n";
        }
        else if (event.text.unicode == 127) { // Delete
            userInput.clear();
        }
        else {
            userInput += static_cast<char>(event.text.unicode);
        }
    }
}

void UserCommandHandler::handleKeyEvent(sf::Event& event) {
    if (event.key.code == sf::Keyboard::Subtract) {
        commands.push_back(ScaleDown);
    }
    else if (event.key.code == sf::Keyboard::Add) {
        commands.push_back(ScaleUp);
    }
    else if (event.key.code == sf::Keyboard::Left) {
        commands.push_back(RotateCounterClockWise);
    }
    else if (event.key.code == sf::Keyboard::Right) {
        commands.push_back(RotateClockWise);
    }
    else if (event.key.code == sf::Keyboard::Up) {
        commands.push_back(MoveForward);
    }
    else if (event.key.code == sf::Keyboard::Down) {
        commands.push_back(MoveBackward);
    }
    else if (event.key.code == sf::Keyboard::Space) {
        commands.push_back(Shoot);
    }
}
