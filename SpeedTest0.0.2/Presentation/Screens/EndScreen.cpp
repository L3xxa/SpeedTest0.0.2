#include "EndScreen.h"
#include <iostream>

EndScreen::EndScreen(sf::RenderWindow& window, sf::Font& font) : window(window), font(font) {
    if (!backgroundTexture.loadFromFile("assets/img/BACKGROUND_VIBE_2.jpg")) {
        std::cout << "Failed to load background image" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    );
}

void EndScreen::initialize() {
    timeUpText.setFont(font);
    timeUpText.setString("Time's up!");
    timeUpText.setCharacterSize(80);
    timeUpText.setFillColor(sf::Color::Red);
    timeUpText.setPosition(window.getSize().x / 2 - timeUpText.getGlobalBounds().width / 2, window.getSize().y / 2 - 40);
}

void EndScreen::draw() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(timeUpText);
    window.display();
}