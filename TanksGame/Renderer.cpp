#include "Renderer.h"

Renderer::Renderer(int windowSize) : windowSize(windowSize), window(sf::VideoMode(windowSize, windowSize), "Tank Game") {
    font.loadFromFile("Arial.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    texture.loadFromFile("./images/tank1.png");
    sprite = sf::Sprite(texture);
    sprite.setPosition(200, 200);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void Renderer::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(text);
    window.draw(sprite); // Draw the tank
    window.display();
}

void Renderer::moveTankForward() {

    float radians = (rotationAngle - 90) * (3.14159265f / 180.0f);
    float moveX = movementSpeed * std::cos(radians);
    float moveY = movementSpeed * std::sin(radians);
    sprite.move(moveX, moveY);
}
