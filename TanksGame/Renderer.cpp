#include "Renderer.h"

Renderer::Renderer(int windowSize, GameRun gamerun) : windowSize(windowSize), gamerun(gamerun), window(sf::VideoMode(windowSize, windowSize), "Tank Game") {
    font.loadFromFile("Arial.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    texture.loadFromFile("./images/tank1.png");
    sprite = sf::Sprite(texture);
    sprite.setPosition(200, 200);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void Renderer::run() {
    initWindow();
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Renderer::initWindow() {
    // Initialize window properties
}

void Renderer::update() {
    // Update game logic here if needed
}

void Renderer::render() {
    window.clear();
    window.draw(text);
    window.draw(sprite); // Draw the tank
    window.display();
}

void Renderer::processEvents() {
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
}

void Renderer::handleTextEvent(sf::Event& event) {
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

        text.setString(userInput);
    }
}

void Renderer::handleKeyEvent(sf::Event& event) {
    if (event.key.code == sf::Keyboard::Subtract) { // Decrease image size
        sprite.setScale(sprite.getScale() * 0.9f);
    }
    else if (event.key.code == sf::Keyboard::Add) { // Increase image size
        sprite.setScale(sprite.getScale() * 1.1f);
    }
    else if (event.key.code == sf::Keyboard::Left) { // Rotate image left
        rotationAngle -= rotationSpeed;
        sprite.setRotation(rotationAngle);
    }
    else if (event.key.code == sf::Keyboard::Right) { // Rotate image right
        rotationAngle += rotationSpeed;
        sprite.setRotation(rotationAngle);
    }
    else if (event.key.code == sf::Keyboard::Up) { // Move image forward
        moveTankForward();
    }
}

void Renderer::moveTankForward() {

    float radians = (rotationAngle - 90) * (3.14159265f / 180.0f);
    float moveX = movementSpeed * std::cos(radians);
    float moveY = movementSpeed * std::sin(radians);
    sprite.move(moveX, moveY);
}
