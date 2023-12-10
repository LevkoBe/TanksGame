#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <memory>
#include "Map.h"

enum ProjectileType {
    CannonBall, // basic
    FireBall,   // burns
    SnowBall,   // slows down
    Chip,       // turns into an ally
    Magnet,     // attracts to itself
    LazerBeam,  // basically basic
    Reducer     // makes smaller
};

enum ObjectShape {
    Circle,
    Square
};


class GameObject {
protected:
    int xPos = 0;
    int yPos = 0;
    int xVel = 0;
    int yVel = 0;
    int xAcc = 0;
    int yAcc = 0;
    int size = 10;
    int maxSpeed = 100;
    int maxAccel = 10;
    int healthPoints = 100;
    int angle = 0;
    ObjectShape shape = Circle;

public:
    GameObject(int initialXPos, int initialYPos, int initialSize, int initialMaxSpeed, int initialMaxAccel, int angle, ObjectShape shape)
        : xPos(initialXPos), yPos(initialYPos), size(initialSize), maxSpeed(initialMaxSpeed), maxAccel(initialMaxAccel), angle(angle), shape(shape) {}

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
        GameObject(0, 0, coefficient / 100 * 100, coefficient / 100 * 100, coefficient / 100 * 100, -90, Circle),
        pHealth(coefficient / 100 * 100), pDamage(coefficient / 100 * 10), pxSize(coefficient / 100 * 100),
        projectile(CannonBall), vMove(coefficient / 100 * 10), vShoot(coefficient / 100 * 20), vReload(coefficient / 100 * 10) {}

    Tank(int vMove, int vShoot, int vReload, int pHealth, int pDamage, int size, ProjectileType projectile) :
        GameObject(0, 0, size, size, size, -90, Circle),
        vMove(vMove), vShoot(vShoot), vReload(vReload), pHealth(pHealth), pDamage(pDamage), pxSize(size), projectile(projectile) {}

    void move(int x, int y) {}
    void shoot() {}
    void setProjectileType(ProjectileType projectileType) {}
};

class Renderer {
private:
    int windowSize = 800;
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
    Renderer(int windowSize) : windowSize(windowSize), window(sf::VideoMode(windowSize, windowSize), "Tank Game") {
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
    int level;
    int gridSize = 10;
    int windowSize = 800;
    std::shared_ptr<std::vector<GameObject>> users = std::make_shared<std::vector<GameObject>>();
    std::shared_ptr<std::vector<GameObject>> bots = std::make_shared<std::vector<GameObject>>();
    std::shared_ptr<std::vector<GameObject>> walls = std::make_shared<std::vector<GameObject>>();
    std::shared_ptr<std::vector<GameObject>> projectiles = std::make_shared<std::vector<GameObject>>();
    std::unique_ptr<Renderer> renderer;

public:
    GameRun() : renderer(std::make_unique<Renderer>(800)) {
        createMap();
    }

    void createMap() {
        Map map;
        int wallSize = windowSize / gridSize;
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                if ((*map.map)[i][j] == Wall)
                {
                    int xPos = wallSize * (i + 0.5);
                    int yPos = wallSize * (j + 0.5);
                    walls->push_back(GameObject(xPos, yPos, wallSize, 0, 0, 0, Square));
                }
            }
        }
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
