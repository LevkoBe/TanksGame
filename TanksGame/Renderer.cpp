// Renderer.cpp
#include "Renderer.h"

Renderer::Renderer(int windowSize) : windowSize(windowSize) {
    font.loadFromFile("Arial.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    texture.loadFromFile("./images/tank1.png");
    sprite = sf::Sprite(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void Renderer::render(sf::RenderWindow& window, GameState gamestate) {
    window.clear();
    window.draw(text);
    window.draw(sprite); // Draw the tank

    // Draw each tank
    for (const auto& tank : *gamestate.bots) {
        sprite.setPosition(static_cast<float>(tank.getPos().first), static_cast<float>(tank.getPos().second));
        sprite.setRotation(static_cast<float>(tank.getAngle()));
        // Set the scale based on the size of the tank
        float scaleFactor = static_cast<float>(tank.getSize()) / sprite.getLocalBounds().width;
        sprite.setScale(scaleFactor, scaleFactor);
        window.draw(sprite);
    }

    // Load wall texture
    sf::Texture wallTexture;
    if (!wallTexture.loadFromFile("./images/whall.png")) {
        // Handle loading error
        std::cerr << "Failed to load wall texture!" << std::endl;
        return;
    }

    // Draw each wall with texture
    for (const auto& wall : *gamestate.walls) {
        // Create a rectangle representing the wall
        sf::RectangleShape wallShape(sf::Vector2f(static_cast<float>(wall.getSize()), static_cast<float>(wall.getSize())));
        wallShape.setPosition(static_cast<float>(wall.getPos().first), static_cast<float>(wall.getPos().second));

        // Apply the loaded texture to the wall shape
        wallShape.setTexture(&wallTexture);

        window.draw(wallShape);
    }

    window.display();
}
