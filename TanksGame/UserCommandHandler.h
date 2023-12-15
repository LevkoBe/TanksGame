#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Commands.h"

class UserCommandHandler
{
    std::string userInput = "";
    std::vector<Command> commands;

    void handleTextEvent(sf::Event& event);

    void handleKeyEvent(sf::Event& event);

public:
    std::vector<Command> processEvents(sf::RenderWindow& window);

};

