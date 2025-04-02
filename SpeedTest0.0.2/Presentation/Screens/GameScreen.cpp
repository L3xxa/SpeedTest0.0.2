#include "GameScreen.h"
#include <iostream>

GameScreen::GameScreen(sf::RenderWindow& window, sf::Font& font, Game& game)
    : window(window), font(font), game(game) {
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

    // Завантажуємо музику
    if (!typingMusic.openFromFile("assets/sound/energetic-chiptune-video-game-music-platformer-8-bit-318348.wav")) {
        std::cout << "Failed to load typing music" << std::endl;
    }
    typingMusic.setLoop(true); // Зациклюємо музику, щоб вона грала безперервно
    typingMusic.setVolume(40.f); // Встановлюємо гучність (0-100), можна налаштувати
}

// Метод для ініціалізації елементів екрану
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

    mistakeBackground.setSize(sf::Vector2f(150, 40));
    mistakeBackground.setFillColor(sf::Color(255, 255, 255, 150));
    mistakeBackground.setPosition(330, 395);
}

// Метод для обгортання тексту
std::string GameScreen::wrapText(const std::string& text, float maxWidth) const {
    std::string result;
    std::string currentLine;
    std::string currentWord;
    sf::Text tempText("", font, 24);

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

    tempText.setString(currentLine + currentWord);
    if (tempText.getLocalBounds().width > maxWidth) {
        result += currentLine + "\n" + currentWord;
    } else {
        result += currentLine + currentWord;
    }
    return result;
}

// Метод для відображення елементів екрану
void GameScreen::draw() {
    window.clear(sf::Color::Black);
    window.draw(backgroundSprite);
    window.draw(inputTextBackground);
    window.draw(outputTextBackground);
    window.draw(timeBackground);
    window.draw(inputText);
    window.draw(targetText);
    window.draw(timeText);
    window.draw(mistakeBackground);
    window.draw(mistakeText);
    window.display();
}

// Метод для оновлення елементів екрану
void GameScreen::update() {
    float maxWidth = inputTextBackground.getSize().x - 20;
    inputText.setString(wrapText(game.getInputText(), maxWidth));
    targetText.setString(wrapText(game.getTargetText(), maxWidth));
    timeText.setString(std::to_string(static_cast<int>(game.getRemainingTime())));
    mistakeText.setString("Mistakes: " + std::to_string(game.getMistakes()));

    // Зупиняємо музику, якщо гра закінчилася
    if (isGameOver()) {
        stopTypingMusic();
    }
}

// Метод для обробки подій
void GameScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        // Відтворюємо музику, коли користувач вводить текст
        playTypingMusic();
        game.handleInput(event.text.unicode);
    }
}

// Метод для перевірки закінчення гри
bool GameScreen::isGameOver() const {
    return game.isFinished();
}

// Метод для відтворення музики
void GameScreen::playTypingMusic() {
    if (typingMusic.getStatus() != sf::Music::Playing) {
        typingMusic.play();
    }
}

// Метод для зупинки музики
void GameScreen::stopTypingMusic() {
    typingMusic.stop();
}