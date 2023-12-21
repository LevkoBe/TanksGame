// Renderer.cpp
#include "Renderer.h"
#include <random>

Renderer::Renderer(int windowSize) : windowSize(windowSize) {
    font.loadFromFile("./RubikDoodleTriangles-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
}

void Renderer::renderGameObjects(sf::RenderWindow& window, const GameState& gamestate) {
    renderWalls(window, gamestate.walls);
    renderBots(window, gamestate.bots);
    renderUserTank(window, gamestate.userTank);
    renderProjectiles(window, gamestate.projectiles);
}

GameRunningState Renderer::renderGame(sf::RenderWindow& window, GameState& gamestate) {
    window.clear();
    //drawBackground(window);

    if (gamestate.userTank->getHP() <= 0) {
        return Lost;
    }
    if (gamestate.bots == nullptr || gamestate.bots->empty()) {
        return Won;
    }
    renderGameObjects(window, gamestate);
    window.display();
    return Running;
}
void Renderer::drawText(sf::RenderWindow& window, const std::string& text, const sf::Color& fillColor, float centerX, float centerY, int height) {

    sf::Text buttonText(text, font, height / 2);
    buttonText.setFillColor(fillColor);
    buttonText.setOrigin(buttonText.getLocalBounds().width / 2, buttonText.getLocalBounds().height / 2);
    buttonText.setPosition(centerX, centerY);
    window.draw(buttonText);
}

void Renderer::drawButton(sf::RenderWindow& window, const std::string& text, const sf::Color& fillColor, float centerX, float centerY, int height) {
    
    sf::Text buttonText(text, font, height / 2);
    buttonText.setFillColor(fillColor);
    buttonText.setOrigin(buttonText.getLocalBounds().width / 2, buttonText.getLocalBounds().height / 2);
    buttonText.setPosition(centerX, centerY);

    sf::RectangleShape buttonRect(sf::Vector2f(buttonText.getGlobalBounds().width * 1.5, buttonText.getGlobalBounds().height * 1.5));
    buttonRect.setOrigin(buttonRect.getLocalBounds().width / 2, buttonRect.getLocalBounds().height / 2);
    buttonRect.setPosition(centerX, centerY + 20);
    buttonRect.setFillColor(sf::Color::Black);

    window.draw(buttonRect);
    window.draw(buttonText);
}

void Renderer::drawLabelWithButtons(sf::RenderWindow& window, const std::string& label, int centerY, int height,
        const std::string& leftButtonText, const std::string& rightButtonText) {
    sf::Text labelText(label, font, height / 4);
    sf::Color Gray(170, 170, 170);
    labelText.setFillColor(Gray);
    labelText.setOrigin(labelText.getLocalBounds().width / 2, labelText.getLocalBounds().height / 2);
    labelText.setPosition(windowSize / 2, centerY);

    window.draw(labelText);

    drawButton(window, leftButtonText, sf::Color(27, 142, 186, 255), windowSize / 6, centerY, height);

    drawButton(window, rightButtonText, sf::Color(205, 92, 59, 255), windowSize * 5 / 6, centerY, height);
}

void Renderer::renderMenu(sf::RenderWindow& window, int gridSize, int difficulty) {
    window.clear();

    drawButton(window, "Play", sf::Color::Yellow, windowSize / 2, windowSize / 8, windowSize / 4);
    drawButton(window, "Quit", sf::Color::Red, windowSize / 2, windowSize * 7 / 8, windowSize / 4);

    std::string buttonText = "Map size: " + std::to_string(gridSize);
    drawLabelWithButtons(window, buttonText, windowSize * 3 / 8, windowSize / 4, "-", "+");

    buttonText = "Difficulty: " + std::to_string(difficulty);
    drawLabelWithButtons(window, buttonText, windowSize * 5 / 8, windowSize / 4, "-", "+");

    window.display();
}

void Renderer::renderPause(sf::RenderWindow& window, std::vector<std::string> buttons) {
    window.clear();

    int number = buttons.size();

    for (int i = 0; i < number; i++) {
        drawButton(window, buttons[i], sf::Color(255, 153, 51), windowSize / 2, (2 * i + 1) * windowSize / number / 2, windowSize / number / 2);
    }

    window.display();
}


void Renderer::drawBackground(sf::RenderWindow& window) {
    sf::Texture backgroundTexture;
    if (backgroundTexture.loadFromFile("./images/grass2.jpg")) {
        sf::RectangleShape backgroundRect(static_cast<sf::Vector2f>(window.getSize()));
        backgroundRect.setTexture(&backgroundTexture);
        window.draw(backgroundRect);
    }
    else {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
}

void Renderer::renderWalls(sf::RenderWindow& window, const std::shared_ptr<std::vector<GameObject>>& walls) {
    for (const auto& wall : *walls) {
        sf::Texture wallTexture;
        if (wallTexture.loadFromFile(wall.getImageName())) {
            sf::RectangleShape wallShape(sf::Vector2f(static_cast<float>(wall.getSize()), static_cast<float>(wall.getSize())));
            wallShape.setPosition(static_cast<float>(wall.getPos().first), static_cast<float>(wall.getPos().second));
            wallShape.setTexture(&wallTexture);
            window.draw(wallShape);
        }
        else {
            std::cerr << "Failed to load wall texture: " << wall.getImageName() << std::endl;
        }
    }
}

void Renderer::renderBots(sf::RenderWindow& window, const std::shared_ptr<std::vector<BotTank>>& bots) {
    for (const auto& tank : *bots) {
        sf::Texture botTexture;
        if (botTexture.loadFromFile(tank.getImageName())) {
            sf::Sprite bot(botTexture);
            bot.setOrigin(bot.getLocalBounds().width / 2, bot.getLocalBounds().height / 2);
            bot.setPosition(static_cast<float>(tank.getPos().first), static_cast<float>(tank.getPos().second));
            bot.setRotation(static_cast<float>(tank.getAngle()));
            float scaleFactor = static_cast<float>(tank.getSize()) / bot.getLocalBounds().width;
            bot.setScale(scaleFactor, scaleFactor);
            window.draw(bot);
        }
        else {
            std::cerr << "Failed to load bot texture: " << tank.getImageName() << std::endl;
        }
    }
}

void Renderer::renderUserTank(sf::RenderWindow& window, const std::shared_ptr<Tank>& userTank) {
    sf::Texture texture;
    texture.loadFromFile(userTank->getImageName());
    sprite = sf::Sprite(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(static_cast<float>(userTank->getPos().first), static_cast<float>(userTank->getPos().second));
    float scaleFactor = static_cast<float>(userTank->getSize()) / sprite.getLocalBounds().width;
    sprite.setScale(scaleFactor, scaleFactor);
    sprite.setRotation(static_cast<float>(userTank->getAngle()));
    window.draw(sprite);

    std::string hpText = "HP: " + std::to_string(userTank->getHP());
    drawText(window, hpText, sf::Color::Cyan, userTank->getPos().first, userTank->getPos().second - userTank->getSize() / 2, 40);
}

void Renderer::renderProjectiles(sf::RenderWindow& window, const std::shared_ptr<std::vector<Projectile>>& projectiles) {
    for (const auto& projectile : *projectiles) {
        sf::Color Gray(170, 170, 170);
        sf::CircleShape projectileCircle(projectile.getSize() / 2.0f);
        projectileCircle.setOrigin(projectileCircle.getRadius(), projectileCircle.getRadius());
        projectileCircle.setPosition(static_cast<float>(projectile.getPos().first), static_cast<float>(projectile.getPos().second));
        projectileCircle.setFillColor(Gray);
        window.draw(projectileCircle);
    }
}

