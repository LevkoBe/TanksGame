#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Text and Image Display");
    sf::Font font;
    font.loadFromFile("Arial.ttf"); // Change the font file path as needed

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);

    std::string userInput;

    sf::Texture texture;
    if (!texture.loadFromFile("./images/tank1.png")) { // Change the image file path as needed
        std::cerr << "Failed to load image!" << std::endl;
        return 1;
    }

    sf::Sprite sprite(texture);
    sprite.setPosition(200, 200); // Adjust the position of the image

    // Set the origin to the center of the image
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    float rotationAngle = 0.0f;
    const float rotationSpeed = 5.0f;
    const float movementSpeed = 5.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
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
            else if (event.type == sf::Event::KeyPressed) {
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
                    float radians = (rotationAngle - 90) * (3.14159265f / 180.0f);
                    float moveX = movementSpeed * std::cos(radians);
                    float moveY = movementSpeed * std::sin(radians);
                    sprite.move(moveX, moveY);
                }
            }
        }

        window.clear();
        window.draw(sprite); // Draw the image
        window.draw(text);
        window.display();
    }

    return 0;
}
