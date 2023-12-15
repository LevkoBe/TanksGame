// Renderer.cpp
#include "Renderer.h"
#include <random>

Renderer::Renderer(int windowSize) : windowSize(windowSize) {
    font.loadFromFile("Arial.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
}

void Renderer::render(sf::RenderWindow& window, GameState gamestate) {
    window.clear();
    window.draw(text);

    sf::Texture backgroundTexture;
    if (backgroundTexture.loadFromFile("./images/gravel1.png")) {
        sf::RectangleShape backgroundRect(static_cast<sf::Vector2f>(window.getSize()));
        backgroundRect.setTexture(&backgroundTexture);
        window.draw(backgroundRect);
    }
    else {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    for (const auto& wall : *gamestate.walls) {
        sf::Texture wallTexture;
        wallTexture.loadFromFile(wall.getImageName());
        // Create a rectangle representing the wall
        sf::RectangleShape wallShape(sf::Vector2f(static_cast<float>(wall.getSize()), static_cast<float>(wall.getSize())));
        wallShape.setPosition(static_cast<float>(wall.getPos().first), static_cast<float>(wall.getPos().second));

        // Apply the randomly selected texture to the wall shape
        wallShape.setTexture(&wallTexture);

        window.draw(wallShape);
    }

    // Draw each tank
    for (const auto& tank : *gamestate.bots) {
        sf::Texture botTexture;

        if (botTexture.loadFromFile(tank.getImageName())) {
            sf::Sprite bot(botTexture);
            bot.setPosition(static_cast<float>(tank.getPos().first), static_cast<float>(tank.getPos().second));
            bot.setRotation(static_cast<float>(tank.getAngle()));

            float scaleFactor = static_cast<float>(tank.getSize()) / sprite.getLocalBounds().width;
            bot.setScale(scaleFactor, scaleFactor);
            
            window.draw(bot);
        }
        else {
            std::cerr << "Failed to load bot texture: " << tank.getImageName() << std::endl;
        }
    }

    sf::Texture texture;
    texture.loadFromFile(gamestate.userTank->getImageName());
    sprite = sf::Sprite(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    float tankSize = static_cast<float>(gamestate.userTank->getSize());
    float scaleFactor = tankSize / sprite.getLocalBounds().width;
    sprite.setPosition(static_cast<float>(gamestate.userTank->getPos().first), static_cast<float>(gamestate.userTank->getPos().second));
    sprite.setScale(scaleFactor, scaleFactor);
    sprite.setRotation(static_cast<float>(gamestate.userTank->getAngle()));

    window.draw(sprite); // Draw the tank

    window.display();

}
