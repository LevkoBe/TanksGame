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

Command UserCommandHandler::handleMenuInteractions(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.y <= windowSize / 4) { // Upper part of the window
                return FirstButtonPressed;
            }
            else if (mousePos.y >= windowSize * 3 / 4) { // Lower part of the window
                return LastButtonPressed;
            }
            else if (mousePos.y <= windowSize / 2) { // Central upper
                if (mousePos.x <= windowSize / 3) { // Left
                    return SecondLeftPressed;
                }
                else if (mousePos.x >= windowSize * 2 / 3) { // Right
                    return SecondRightPressed;
                }
            }
            else if (mousePos.y >= windowSize / 2) { // Central lower
                if (mousePos.x <= windowSize / 3) { // Left
                    return ThirdLeftPressed;
                }
                else if (mousePos.x >= windowSize * 2 / 3) { // Right
                    return ThirdRightPressed;
                }
            }
        }
    }
    return None;
}

std::vector<Command> getCommandsVector(int buttonsNumber) {
    switch (buttonsNumber)
    {
    case 1:
        return std::vector<Command>{ FirstButtonPressed };
    case 2:
        return std::vector<Command>{ FirstButtonPressed, LastButtonPressed };
    case 3:
        return std::vector<Command>{ FirstButtonPressed, SecondLeftPressed, LastButtonPressed };
    case 4:
        return std::vector<Command>{ FirstButtonPressed, SecondLeftPressed, ThirdLeftPressed, LastButtonPressed };
    default:
        return std::vector<Command>();
    }
}

Command UserCommandHandler::handlePause(sf::RenderWindow& window, int buttonsNumber) {
    sf::Event event;
    std::vector<Command> returnOptions = getCommandsVector(buttonsNumber);
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for (int i = 0; i < buttonsNumber; i++)
            {
                if (mousePos.y <= (i + 1) * windowSize / buttonsNumber) { // Upper part of the window
                    return returnOptions[i];
                }
            }
        }
    }
    return None;
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
    else if (event.key.code == sf::Keyboard::Escape) {
        commands.push_back(Pause);
    }
    else if (event.key.code == sf::Keyboard::Escape && event.key.control) {
        commands.push_back(FaulsyPause);
    }
}

