#include "GameScreen.h"
#include <iostream>

GameScreen::GameScreen(sf::RenderWindow& window, sf::Font& font) :
    window(window),
    font(font),
    timer(60.0f),
    textManager(),
    gameOver(false) {
    if (!backgroundTexture.loadFromFile("assets/img/BACKGROUND№3 (1).jpg")) {
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

void GameScreen::initialize() {
    inputTextBackground.setSize(sf::Vector2f(1250, 350));
    inputTextBackground.setFillColor(sf::Color(0, 0, 0, 150));
    inputTextBackground.setPosition(330, 125);

    outputTextBackground.setSize(sf::Vector2f(1250, 350));
    outputTextBackground.setFillColor(sf::Color(0, 0, 0, 150));
    outputTextBackground.setPosition(330, 625);

    timeBackground.setRadius(50);
    timeBackground.setFillColor(sf::Color(255, 0, 0, 150));
    timeBackground.setPosition(900, 500);

    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(340, 135);

    targetText.setFont(font);
    targetText.setCharacterSize(24);
    targetText.setFillColor(sf::Color::White);
    targetText.setPosition(340, 635);

    timeText.setFont(font);
    timeText.setCharacterSize(50);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(920, 520);

    mistakeText.setFont(font);
    mistakeText.setCharacterSize(24);
    mistakeText.setFillColor(sf::Color::Red);
    mistakeText.setPosition(340, 400);
}

std::string wrapText(const std::string& text, const sf::Font& font, unsigned int characterSize, float maxWidth) {
    std::string result;
    std::string currentLine;
    std::string currentWord;
    sf::Text tempText("", font, characterSize);

    for (char c : text) {
        if (c == ' ' || c == '\n') {
            tempText.setString(currentLine + currentWord);
            if (tempText.getLocalBounds().width > maxWidth || c == '\n') {
                result += currentLine + "\n";
                currentLine = currentWord + " ";
            } else {
                currentLine += currentWord + " ";
            }
            currentWord.clear();
            if (c == '\n') {
                result += currentLine;
                currentLine.clear();
            }
        } else {
            currentWord += c;
        }
    }

    // Додаємо останнє слово
    tempText.setString(currentLine + currentWord);
    if (tempText.getLocalBounds().width > maxWidth) {
        result += currentLine + "\n" + currentWord;
    } else {
        result += currentLine + currentWord;
    }

    return result;
}

void GameScreen::draw() {
    window.clear(sf::Color::Black);
    window.draw(backgroundSprite);
    window.draw(inputTextBackground);
    window.draw(outputTextBackground);
    window.draw(timeBackground);
    window.draw(inputText);
    window.draw(targetText);
    window.draw(timeText);
    window.draw(mistakeText);
    window.display();
}

void GameScreen::update() {
    // Максимальна ширина — ширина фону мінус відступи
    float maxWidth = inputTextBackground.getSize().x - 20; // 20 — відступи з боків

    // Форматуємо цільовий текст
    std::string wrappedTarget = wrapText(textManager.getTargetText(), font, 24, maxWidth);
    targetText.setString(wrappedTarget);

    // Форматуємо введений текст
    std::string wrappedInput = wrapText(textManager.getInputText(), font, 24, maxWidth);
    inputText.setString(wrappedInput);

    // Оновлюємо таймер і помилки
    timeText.setString(std::to_string(static_cast<int>(timer.getRemainingTime())));
    mistakeText.setString("Mistakes: " + std::to_string(textManager.getMistakes()));
}

void GameScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        textManager.addInput(event.text.unicode);
    }
}

void GameScreen::startGame() {
    textManager.reset(); // Завантажуємо новий текст
    timer.start();
}

bool GameScreen::isGameOver() const {
    return timer.isFinished();
}