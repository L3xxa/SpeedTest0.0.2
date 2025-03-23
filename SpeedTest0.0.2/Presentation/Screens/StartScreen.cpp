#include "StartScreen.h"
#include <iostream>

StartScreen::StartScreen(sf::Font& font, sf::RenderWindow& window) :
    window(window),
    font(font),
    startButton(font, "Start", sf::Vector2f(650, 750), sf::Vector2f(200, 60)),
    statisticsButton(font, "Statistics", sf::Vector2f(895, 750), sf::Vector2f(200, 60)),
    exitButton(font, "Exit", sf::Vector2f(1140, 750), sf::Vector2f(200, 60)),
    startButtonPressed(false) {
    startButton.setColors(sf::Color::Black, sf::Color(255, 255, 255, 150));
    statisticsButton.setColors(sf::Color::Black, sf::Color(255, 255, 255, 150));
    exitButton.setColors(sf::Color::Black, sf::Color(255, 255, 255, 150));

    if (!backgroundTexture.loadFromFile("assets/img/BACKGROUND_VIBE_2.jpg")) {
        std::cerr << "Failed to load background image" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    );
}

void StartScreen::initialize() {
    menuBar.setSize(sf::Vector2f(750, 135));
    menuBar.setFillColor(sf::Color(0, 0, 0, 200));
    menuBar.setPosition(620, 720);
}

void StartScreen::draw() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(menuBar);
    startButton.draw(window);
    statisticsButton.draw(window);
    exitButton.draw(window);
    window.display();
}

bool StartScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (startButton.isClicked(mousePos)) {
            startButton.playClickSound();
            startButtonPressed = true;
            return false;
        }
        if (exitButton.isClicked(mousePos)) {
            exitButton.playClickSound();
            return true;
        }
    }
    return false;
}

bool StartScreen::isStartButtonPressed() const {
    return startButtonPressed;
}