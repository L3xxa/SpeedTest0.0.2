#include "EndScreen.h"
#include "../ScreenManager.h" // Додаємо для ScreenManager
#include <iostream>
#include <sstream>

EndScreen::EndScreen(sf::RenderWindow& window, sf::Font& font, ScoreRepository& scoreRepo)
    : window(window), font(font), scoreRepo(scoreRepo),
      restartButton(font, "Restart", sf::Vector2f(700, 830), sf::Vector2f(200, 60)),
      exitButton(font, "Exit", sf::Vector2f(1025, 830), sf::Vector2f(200, 60)) {
    if (!backgroundTexture.loadFromFile("assets/img/BACKGROUND№3 (1).jpg")) {
        std::cout << "Failed to load background image" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    setBackgroundFullScreen();

    restartButton.setColors(sf::Color::White, sf::Color(0, 120, 255, 200));
    exitButton.setColors(sf::Color::White, sf::Color(255, 50, 50, 200));
}

void EndScreen::setBackgroundFullScreen() {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    if (textureSize.x == 0 || textureSize.y == 0) return;
    float windowRatio = static_cast<float>(windowSize.x) / windowSize.y;
    float textureRatio = static_cast<float>(textureSize.x) / textureSize.y;
    float scaleX = (windowRatio > textureRatio) ? static_cast<float>(windowSize.x) / textureSize.x : static_cast<float>(windowSize.y) / textureSize.y;
    float scaleY = scaleX;
    backgroundSprite.setScale(scaleX, scaleY);
    sf::FloatRect spriteBounds = backgroundSprite.getLocalBounds();
    backgroundSprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
    backgroundSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
}

void EndScreen::initialize() {
    endTitle.setFont(font);
    endTitle.setString("Game Over");
    endTitle.setCharacterSize(115);
    endTitle.setFillColor(sf::Color::White);
    endTitle.setPosition(window.getSize().x / 2 - endTitle.getGlobalBounds().width / 2, 200);

    statsText.setFont(font);
    statsText.setCharacterSize(30);
    statsText.setFillColor(sf::Color::White);
    statsText.setPosition(window.getSize().x / 2 - 80, 400);

    statsBackground.setSize(sf::Vector2f(800, 750));
    statsBackground.setFillColor(sf::Color(0, 0, 0, 180));
    statsBackground.setPosition(window.getSize().x / 2 - 400, window.getSize().x / 2 - 800);

    backgroundMenu.setSize(sf::Vector2f(800, 100));
    backgroundMenu.setFillColor(sf::Color(255, 255, 255, 150));
    backgroundMenu.setPosition(window.getSize().x / 2 - 400, window.getSize().x / 2 - 150);
}

void EndScreen::draw() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(statsBackground);
    window.draw(backgroundMenu);
    window.draw(endTitle);
    window.draw(statsText);
    restartButton.draw(window);
    exitButton.draw(window);
    window.display();
}

std::string EndScreen::calculatePoints(float wpm, float accuracy, int mistakes, int times) {
    int score = 0;
    if (wpm < 20) score += 2;
    if (accuracy < 70) score += 1;
    if (mistakes > 5) score += 1;
    if (times < 10) score += 1;

    if (score >= 4) return "Bad";
    else if (score == 3) return "Norm";
    else if (score == 2) return "Good";
    else return "Very good";
}

void EndScreen::setStats(float wpm, float accuracy, int mistakes, int times) {
    std::string points = calculatePoints(wpm, accuracy, mistakes, times);
    std::stringstream ss;
    ss << "WPM: " << static_cast<int>(wpm) << "\n\nAccuracy: " << static_cast<int>(accuracy) 
       << "%\n\nMistakes: " << mistakes << "\n\nTime Left: " << times << "\n\nPoints: " << points;
    statsText.setString(ss.str());
    scoreRepo.addScore(wpm, accuracy, mistakes, times, points);
}

void EndScreen::handleEvent(const sf::Event& event, ScreenManager& screenManager) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (restartButton.isClicked(mousePos)) {
            restartButton.playClickSound();
            screenManager.switchScreen(ScreenType::Game); // Переключаємо на GameScreen
        }
        if (exitButton.isClicked(mousePos)) {
            exitButton.playClickSound();
            window.close(); // Закриваємо вікно
        }
    }
}