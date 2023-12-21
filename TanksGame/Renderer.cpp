// Renderer.cpp
#include "Renderer.h"
#include <random>

Renderer::Renderer(int windowSize) : windowSize(windowSize) {
    font.loadFromFile("Arial.ttf");
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

void Renderer::renderGameOverText(sf::RenderWindow& window, const std::string& textString, int xPos, int yPos, const sf::Color& textColor) {
    sf::Font stylishFont;
    if (!stylishFont.loadFromFile("./RubikDoodleTriangles-Regular.ttf")) {
        std::cerr << "Failed to load stylish font!" << std::endl;
        return;
    }

    text.setFont(stylishFont);
    text.setString(textString);
    text.setCharacterSize(100);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    text.setPosition(xPos, yPos);
    text.setFillColor(textColor);

    renderTextWithOutline(text, window, sf::Color::Black);
}

void Renderer::renderTextWithOutline(sf::Text& text, sf::RenderWindow& window, const sf::Color& outlineColor) {
    sf::Color textColor = text.getFillColor();
    text.setOutlineColor(outlineColor);
    text.setOutlineThickness(2.0);

    window.draw(text);

    text.setFillColor(textColor);
    text.setOutlineThickness(0.0);
}

void Renderer::renderGame(sf::RenderWindow& window, GameState& gamestate) {
    window.clear();
    //drawBackground(window);

    if (gamestate.userTank->getHP() <= 0) {
        renderGameOverText(window, "You lost!", windowSize / 2, windowSize / 2, sf::Color::Red);
    }
    else if (gamestate.bots == nullptr || gamestate.bots->empty()) {
        sf::Color warmOrange(255, 153, 51);
        renderGameOverText(window, "You won!", windowSize / 2, windowSize / 2, warmOrange);
    }
    else {
        renderGameObjects(window, gamestate);
    }

    window.display();
}

void Renderer::drawButton(sf::RenderWindow& window, const std::string& text, const sf::Font& font, const sf::Color& fillColor, float centerX, float centerY, int height) {
    
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

void Renderer::drawLabelWithButtons(sf::RenderWindow& window, const std::string& label, const sf::Font& font, int centerY, int height,
        const std::string& leftButtonText, const std::string& rightButtonText) {
    sf::Text labelText(label, font, height / 4);
    sf::Color Gray(170, 170, 170);
    labelText.setFillColor(Gray);
    labelText.setOrigin(labelText.getLocalBounds().width / 2, labelText.getLocalBounds().height / 2);
    labelText.setPosition(windowSize / 2, centerY);

    window.draw(labelText);

    drawButton(window, leftButtonText, font, sf::Color(27, 142, 186, 255), windowSize / 6, centerY, height);

    drawButton(window, rightButtonText, font, sf::Color(205, 92, 59, 255), windowSize * 5 / 6, centerY, height);
}

void Renderer::renderMenu(sf::RenderWindow& window, int gridSize, int difficulty) {
    window.clear();

    sf::Font playFont;
    playFont.loadFromFile("./RubikDoodleTriangles-Regular.ttf");

    drawButton(window, "Play", playFont, sf::Color::Yellow, windowSize / 2, windowSize / 8, windowSize / 4);
    drawButton(window, "Quit", playFont, sf::Color::Red, windowSize / 2, windowSize * 7 / 8, windowSize / 4);

    std::string buttonText = "Map size: " + std::to_string(gridSize);
    drawLabelWithButtons(window, buttonText, playFont, windowSize * 3 / 8, windowSize / 4, "-", "+");

    buttonText = "Difficulty: " + std::to_string(difficulty);
    drawLabelWithButtons(window, buttonText, playFont, windowSize * 5 / 8, windowSize / 4, "-", "+");

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

    // Display userTank's HP
    sf::Font stylishFont;
    if (!stylishFont.loadFromFile("./RubikDoodleTriangles-Regular.ttf")) {
        std::cerr << "Failed to load stylish font!" << std::endl;
        return;
    }

    sf::Text hpText;
    hpText.setFont(stylishFont);
    hpText.setString("HP: " + std::to_string(userTank->getHP())); // Assuming getHP() returns the tank's HP
    hpText.setCharacterSize(30);
    hpText.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = hpText.getLocalBounds();
    hpText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    hpText.setPosition(static_cast<float>(userTank->getPos().first), static_cast<float>(userTank->getPos().second - userTank->getSize() / 2));

    renderTextWithOutline(hpText, window, sf::Color::Black);
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

