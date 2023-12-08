#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <memory>
#include <random>

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
    Squre
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
    int angle = 0;
    ObjectShape shape = Circle;

public:
    GameObject(int initialXPos, int initialYPos, int initialXVel, int initialYVel, int initialXAcc, int initialYAcc,
        int initialSize, int initialMaxSpeed, int initialMaxAccel, int angle, ObjectShape shape)
        : xPos(initialXPos), yPos(initialYPos), xVel(initialXVel), yVel(initialYVel),
        xAcc(initialXAcc), yAcc(initialYAcc), size(initialSize),
        maxSpeed(initialMaxSpeed), maxAccel(initialMaxAccel), angle(angle), shape(shape) {}

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
        GameObject(0, 0, 0, 0, 0, 0, coefficient / 100 * 100, coefficient / 100 * 100, coefficient / 100 * 100, -90, Circle),
        pHealth(coefficient / 100 * 100), pDamage(coefficient / 100 * 10), pxSize(coefficient / 100 * 100),
        projectile(CannonBall), vMove(coefficient / 100 * 10), vShoot(coefficient / 100 * 20), vReload(coefficient / 100 * 10) {}

    Tank(int vMove, int vShoot, int vReload, int pHealth, int pDamage, int size, ProjectileType projectile) :
        GameObject(0, 0, 0, 0, 0, 0, size, size, size, -90, Circle),
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
    int level;
    int gridSize = 10;
    std::vector<Tank> users;
    std::vector<Tank> bots;
    std::vector<GameObject> walls;
    std::vector<GameObject> projectiles;
    std::unique_ptr<Renderer> renderer;

public:
    GameRun() : renderer(std::make_unique<Renderer>()) {
        createMap();
    }

    void printMatrix(const std::shared_ptr<std::vector<std::vector<bool>>>& matrix) {
        std::system("cls");
        for (const auto& row : *matrix) {
            for (bool value : row) {
                if (value == 0)
                {
                    std::cout << ". ";
                }
                else {
                    std::cout << "# ";
                }
            }
            std::cout << std::endl;
        }
    }

    void createMap() {
        // creating an array;
        auto map = std::make_shared<std::vector<std::vector<bool>>>(gridSize, std::vector<bool>(gridSize, 0));
        auto special = std::make_shared<std::vector<std::pair<int, int>>>(std::vector<std::pair<int, int>>{ {0, gridSize - 1 }, { gridSize - 1, 0 }, { gridSize - 1, gridSize - 1 } });

        for (int i = 1; i < 4; i++) {
            auto visited = std::make_shared<std::vector<std::pair<int, int>>>(std::vector<std::pair<int, int>>());

            auto position = startingPoint(map, special);
            while (visited->empty() || !closeToDestination(special, visited->back())) {
                (*map)[position.first][position.second] = 1;
                auto neighbours = getNeighbours(map, std::make_shared<std::pair<int, int>>(position), special);
                auto newPair = getRandomPair(neighbours, visited);
                printMatrix(map);
                if (neighbours->empty()) {
                    position = visited->back(); // DFS
                    visited->pop_back();
                }
                else {
                    visited->push_back(position);
                    position = newPair;
                }
            }
            markDestination(map, position, special);
            if (!(*map)[0][gridSize - 1] && !(*map)[gridSize - 1][0] && !(*map)[gridSize - 1][gridSize - 1]) {
                special->clear();
            }
            special->insert(special->end(), visited->begin(), visited->end());
            printMatrix(map);
        }
    }

    void markDestination(std::shared_ptr<std::vector<std::vector<bool>>> map, std::pair<int, int> position, std::shared_ptr<std::vector<std::pair<int, int>>> special) {

        auto neighbour = std::make_pair(position.first + 1, position.second);
        if (insideTheGameField(map, neighbour) && std::find(special->begin(), special->end(), neighbour) != special->end()) {
            (*map)[neighbour.first][neighbour.second] = 1;
            return;
        }
        neighbour = std::make_pair(position.first - 1, position.second);
        if (insideTheGameField(map, neighbour) && std::find(special->begin(), special->end(), neighbour) != special->end()) {
            (*map)[neighbour.first][neighbour.second] = 1;
            return;
        }
        neighbour = std::make_pair(position.first, position.second + 1);
        if (insideTheGameField(map, neighbour) && std::find(special->begin(), special->end(), neighbour) != special->end()) {
            (*map)[neighbour.first][neighbour.second] = 1;
            return;
        }
        neighbour = std::make_pair(position.first, position.second - 1);
        if (insideTheGameField(map, neighbour) && std::find(special->begin(), special->end(), neighbour) != special->end()) {
            (*map)[neighbour.first][neighbour.second] = 1;
        }
    }

    std::pair<int, int> startingPoint(std::shared_ptr<std::vector<std::vector<bool>>> map, std::shared_ptr<std::vector<std::pair<int, int>>> special) {
        auto position = std::make_pair(0, 0);
        if (!(*map)[0][0]) {
            return position;
        }
        else if (!(*map)[0][gridSize - 1]) { position.second = gridSize - 1; }
        else if (!(*map)[gridSize - 1][0]) { position.first = gridSize - 1; }
        else {
            position.first = gridSize - 1;
            position.second = gridSize - 1;
        }
        special->erase(std::remove_if(special->begin(), special->end(), [position](const std::pair<int, int>& p) {
            return p == position;
            }), special->end());
        return position;
    }

    std::pair<int, int> getRandomPair(const std::shared_ptr<std::vector<std::pair<int, int>>>& neighbours, const std::shared_ptr<std::vector<std::pair<int, int>>>& visited) {
        if (!neighbours || neighbours->empty()) {
            return visited->back();
        }

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<size_t> distribution(0, neighbours->size() - 1);
        size_t randomIndex = distribution(gen);

        return (*neighbours)[randomIndex];
    }

    bool closeToDestination(std::shared_ptr<std::vector<std::pair<int, int>>> special, std::pair<int, int> toCheck) {
        auto coordinates = std::make_pair(toCheck.first + 1, toCheck.second);
        if (std::find(special->begin(), special->end(), coordinates) != special->end())
        {
            return true;
        }
        coordinates = std::make_pair(toCheck.first - 1, toCheck.second);
        if (std::find(special->begin(), special->end(), coordinates) != special->end())
        {
            return true;
        }
        coordinates = std::make_pair(toCheck.first, toCheck.second + 1);
        if (std::find(special->begin(), special->end(), coordinates) != special->end())
        {
            return true;
        }
        coordinates = std::make_pair(toCheck.first, toCheck.second - 1);
        if (std::find(special->begin(), special->end(), coordinates) != special->end())
        {
            return true;
        }
        return false;
    }

    std::shared_ptr<std::vector<std::pair<int, int>>> getNeighbours(std::shared_ptr<std::vector<std::vector<bool>>> map,
        std::shared_ptr<std::pair<int, int>> toCheck, std::shared_ptr<std::vector<std::pair<int, int>>> special) {

        auto neighbours = std::make_shared<std::vector<std::pair<int, int>>>(std::vector<std::pair<int, int>>());

        // checking whether it's inside the gamefield
        if (!insideTheGameField(map, *toCheck))
        {
            return neighbours;
        }

        // checking whether we're close to destination

        auto coordinates = std::make_pair(toCheck->first + 1, toCheck->second);
        if (closeToDestination(special, coordinates))
        {
            neighbours->push_back(coordinates);
            return neighbours;
        }
        coordinates = std::make_pair(toCheck->first - 1, toCheck->second);
        if (closeToDestination(special, coordinates))
        {
            neighbours->push_back(coordinates);
            return neighbours;
        }
        coordinates = std::make_pair(toCheck->first, toCheck->second + 1);
        if (closeToDestination(special, coordinates))
        {
            neighbours->push_back(coordinates);
            return neighbours;
        }
        coordinates = std::make_pair(toCheck->first, toCheck->second - 1);
        if (closeToDestination(special, coordinates))
        {
            neighbours->push_back(coordinates);
            return neighbours;
        }

        // checking whether we hit visited spots

        coordinates = std::make_pair(toCheck->first + 1, toCheck->second);
        if (insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] != 1  // we hit visited spot
            && std::find(neighbours->begin(), neighbours->end(), coordinates) == neighbours->end()      // we already have it
            && validNeighbours(map, coordinates, toCheck))                                              // non-zero neighbours
        {
            neighbours->push_back(coordinates);
        }
        coordinates = std::make_pair(toCheck->first - 1, toCheck->second);
        if (insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] != 1  // we hit visited spot
            && std::find(neighbours->begin(), neighbours->end(), coordinates) == neighbours->end()      // we already have it
            && validNeighbours(map, coordinates, toCheck))                                              // non-zero neighbours
        {
            neighbours->push_back(coordinates);
        }
        coordinates = std::make_pair(toCheck->first, toCheck->second + 1);
        if (insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] != 1  // we hit visited spot
            && std::find(neighbours->begin(), neighbours->end(), coordinates) == neighbours->end()      // we already have it
            && validNeighbours(map, coordinates, toCheck))                                              // non-zero neighbours
        {
            neighbours->push_back(coordinates);
        }
        coordinates = std::make_pair(toCheck->first, toCheck->second - 1);
        if (insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] != 1  // we hit visited spot
            && std::find(neighbours->begin(), neighbours->end(), coordinates) == neighbours->end()      // we already have it
            && validNeighbours(map, coordinates, toCheck))                                              // non-zero neighbours
        {
            neighbours->push_back(coordinates);
        }

        return neighbours;
    }

    bool validNeighbours(std::shared_ptr<std::vector<std::vector<bool>>> map, std::pair<int, int> toCheck, std::shared_ptr<std::pair<int, int>> toLeave) {

        // checking whether we hit visited spots
        auto firstNeighbour = std::make_pair(toCheck.first + 1, toCheck.second);
        auto secondNeighbour = std::make_pair(toCheck.first - 1, toCheck.second);
        auto thirdNeighbour = std::make_pair(toCheck.first, toCheck.second + 1);
        auto fourthNeighbour = std::make_pair(toCheck.first, toCheck.second - 1);
        if ((insideTheGameField(map, firstNeighbour) && !(firstNeighbour.first == toLeave->first &&
                firstNeighbour.second == toLeave->second) && (*map)[firstNeighbour.first][firstNeighbour.second] == 1) ||
            (insideTheGameField(map, secondNeighbour) && !(secondNeighbour.first == toLeave->first &&
                secondNeighbour.second == toLeave->second) && (*map)[secondNeighbour.first][secondNeighbour.second] == 1) ||
            (insideTheGameField(map, thirdNeighbour) && !(thirdNeighbour.first == toLeave->first &&
                thirdNeighbour.second == toLeave->second) && (*map)[thirdNeighbour.first][thirdNeighbour.second] == 1) ||
            (insideTheGameField(map, fourthNeighbour) && !(fourthNeighbour.first == toLeave->first &&
                fourthNeighbour.second == toLeave->second) && (*map)[fourthNeighbour.first][fourthNeighbour.second] == 1))
        {
            return false;
        }
        return true;
    }

    bool insideTheGameField(std::shared_ptr<std::vector<std::vector<bool>>> map, std::pair<int, int> toCheck) {
        if (toCheck.first < 0 || toCheck.second < 0 || toCheck.first >= gridSize || toCheck.second >= gridSize)
        {
            return false;
        }
        return true;
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
