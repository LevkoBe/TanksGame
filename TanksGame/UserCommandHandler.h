#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Commands.h"

class UserCommandHandler
{
    std::string userInput = "";
    int windowSize = 0;
    std::vector<Command> commands;

    void handleTextEvent(sf::Event& event);

    void handleKeyEvent(sf::Event& event);

public:
    std::vector<Command> processEvents(sf::RenderWindow& window);

    Command handleMenuInteractions(sf::RenderWindow& window);

    Command handlePause(sf::RenderWindow& window, int buttonsNumber);

    void setWindowSize(int windowSize) {
        this->windowSize = windowSize;
    }
};

