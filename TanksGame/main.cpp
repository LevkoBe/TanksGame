#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <memory>

enum ProjectileType {
    CannonBall,
    FireBall,
    SnowBall,
    Chip,
    Magnet,
    LazerBeam,
    Reducer
};

class GameObject {
private:
    int xPos;
    int yPos;
    int xVel;
    int yVel;
    int xAcc;
    int yAcc;
    int size;
    int maxSpeed;
    int maxAccel;

public:
    GameObject(int initialXPos, int initialYPos, int initialXVel, int initialYVel, int initialXAcc, int initialYAcc,
        int initialSize, int initialMaxSpeed, int initialMaxAccel)
        : xPos(initialXPos), yPos(initialYPos), xVel(initialXVel), yVel(initialYVel),
        xAcc(initialXAcc), yAcc(initialYAcc), size(initialSize),
        maxSpeed(initialMaxSpeed), maxAccel(initialMaxAccel) {}

    std::tuple<int, int> getPos() const {
        return std::make_tuple(xPos, yPos);
    }

    std::tuple<int, int> getVel() const {
        return std::make_tuple(xVel, yVel);
    }

    std::tuple<int, int> getAcc() const {
        return std::make_tuple(xAcc, yAcc);
    }

    int getMaxSpeed() const {
        return maxSpeed;
    }

    int getMaxAccel() const {
        return maxAccel;
    }
};

class Tank : public GameObject {
private:
    int vMove;
    int vShoot;
    int vReload;
    int pHealth;
    int pDamage;
    int pxSize;
    ProjectileType projectile;

public:
    Tank(int coefficient = 100) :
        GameObject(0, 0, 0, 0, 0, 0, coefficient / 100 * 100, coefficient / 100 * 100, coefficient / 100 * 100),
        pHealth(coefficient / 100 * 100), pDamage(coefficient / 100 * 10), pxSize(coefficient / 100 * 100),
        projectile(CannonBall), vMove(coefficient / 100 * 10), vShoot(coefficient / 100 * 20), vReload(coefficient / 100 * 10) {}

    Tank(int vMove, int vShoot, int vReload, int pHealth, int pDamage, int size, ProjectileType projectile) :
        GameObject(0, 0, 0, 0, 0, 0, size, size, size),
        vMove(vMove), vShoot(vShoot), vReload(vReload), pHealth(pHealth), pDamage(pDamage), pxSize(size), projectile(projectile) {}

    void move(int x, int y) {}
    void shoot() {}
    void setProjectileType(ProjectileType projectileType) {}
};

class Renderer {
private:
    const int windowSize = 200;
    float rotationAngle = 0.0f;
    const float rotationSpeed = 5.0f;
    const float movementSpeed = 5.0f;
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string userInput = "";

public:
    Renderer() : window(sf::VideoMode(800, 600), "Tank Game") {
        font.loadFromFile("Arial.ttf");
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        texture.loadFromFile("./images/tank1.png");
        sprite = sf::Sprite(texture);
        sprite.setPosition(200, 200);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    }

    void run() {
        initWindow();
        while (window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

    void initWindow() {
        // Initialize window properties
    }

    void update() {
        // Update game logic here if needed
    }

    void render() {
        window.clear();
        window.draw(text);
        window.draw(sprite); // Draw the tank
        window.display();
    }

    void processEvents() {
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

private:

    void handleTextEvent(sf::Event& event) {
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

    void handleKeyEvent(sf::Event& event) {
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

    void moveTankForward() {
        float radians = (rotationAngle - 90) * (3.14159265f / 180.0f);
        float moveX = movementSpeed * std::cos(radians);
        float moveY = movementSpeed * std::sin(radians);
        sprite.move(moveX, moveY);
    }
};

class GameRun {
private:
    int gridSize;
    int level;
    std::vector<std::vector<bool>> map;
    Tank* user;
    std::vector<Tank> bots;
    std::unique_ptr<Renderer> renderer;

public:
    GameRun() : renderer(std::make_unique<Renderer>()) {
        createMap();
    }

    void createMap() {
        // creating an array;
    }

    void reset() {}
    void makeMove(int x, int y) {}

    void run() {
        renderer->run();
    }
};

int main() {
    GameRun game;
    game.run();

    return 0;
}
