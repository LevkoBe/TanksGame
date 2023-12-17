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
    drawBackground(window);

    renderWalls(window, gamestate.walls);
    renderBots(window, gamestate.bots);
    renderUserTank(window, gamestate.userTank);
    renderProjectiles(window, gamestate.projectiles);

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

void Renderer::renderBots(sf::RenderWindow& window, const std::shared_ptr<std::vector<Tank>>& bots) {
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
}

void Renderer::renderProjectiles(sf::RenderWindow& window, const std::shared_ptr<std::vector<Projectile>>& projectiles) {
    for (const auto& projectile : *projectiles) {
        sf::Texture projectileTexture;
        if (projectileTexture.loadFromFile(projectile.getImageName())) {
            sf::Sprite projectileSprite(projectileTexture);
            projectileSprite.setOrigin(projectileSprite.getLocalBounds().width / 2, projectileSprite.getLocalBounds().height / 2);
            projectileSprite.setPosition(static_cast<float>(projectile.getPos().first), static_cast<float>(projectile.getPos().second));
            float scaleFactor = static_cast<float>(projectile.getSize()) / projectileSprite.getLocalBounds().width;
            projectileSprite.setScale(scaleFactor, scaleFactor);
            window.draw(projectileSprite);
        }
        else {
            std::cerr << "Failed to load projectile texture: " << projectile.getImageName() << std::endl;
        }
    }
}
