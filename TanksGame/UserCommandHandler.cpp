#include "UserCommandHandler.h"

std::vector<Command> UserCommandHandler::processEvents(sf::RenderWindow& window) { // (: I wanted to give a window, instead of a reference
    sf::Event event;
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
    if (event.key.code == sf::Keyboard::Subtract) { // Decrease image size
        commands.push_back(ScaleDown);
    }
    else if (event.key.code == sf::Keyboard::Add) { // Increase image size
        commands.push_back(ScaleUp);
    }
    else if (event.key.code == sf::Keyboard::Left) { // Rotate image left
        commands.push_back(RotateCounterClockWise);
    }
    else if (event.key.code == sf::Keyboard::Right) { // Rotate image right
        commands.push_back(RotateClockWise);
    }
    else if (event.key.code == sf::Keyboard::Up) { // Move image forward / accelerate
        commands.push_back(MoveForward);
    }
    else if (event.key.code == sf::Keyboard::Down) { // Move image backward / deccelerate
        commands.push_back(MoveBackward);
    }
    else if (event.key.code == sf::Keyboard::Space) { // Move image backward / deccelerate
        commands.push_back(Shoot);
    }
}
