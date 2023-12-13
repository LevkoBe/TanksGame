#include "Renderer.h"

Renderer::Renderer(int windowSize) : windowSize(windowSize) {
    font.loadFromFile("Arial.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    texture.loadFromFile("./images/tank1.png");
    sprite = sf::Sprite(texture);
    sprite.setPosition(200, 200);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    // sprite.setOrigin(20, 20);
}

void Renderer::render(sf::RenderWindow& window, GameState gamestate) {
    window.clear();
    window.draw(text);
    window.draw(sprite); // Draw the tank

    for (const auto& tank : *gamestate.bots) {
        sprite.setPosition(static_cast<float>(tank.getPos().first), static_cast<float>(tank.getPos().second));
        sprite.setRotation(static_cast<float>(tank.getAngle()));
        // Set the scale based on the size of the tank
        float scaleFactor = static_cast<float>(tank.getSize()) / sprite.getLocalBounds().width;
        sprite.setScale(scaleFactor, scaleFactor);
        window.draw(sprite);
    }
    window.display();
}
