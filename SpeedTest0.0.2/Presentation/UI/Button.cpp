#include "Button.h"
#include <iostream>

Button::Button(sf::Font& font, const std::string& label, sf::Vector2f position, sf::Vector2f size) {
    background.setSize(size);
    background.setPosition(position);
    background.setFillColor(sf::Color(0, 0, 255, 150));

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(40);
    text.setPosition(position.x + 10, position.y + 10);

    if (!clickSoundBuffer.loadFromFile("assets/sound/Start_Exit_1.wav")) {
        std::cerr << "Failed to load click sound" << std::endl;
    }
    clickSound.setBuffer(clickSoundBuffer);
}

// Метод для відображення кнопки
void Button::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(text);
}

// Метод для перевірки натискання кнопки
bool Button::isClicked(sf::Vector2i mousePos) const {
    return background.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

// Метод для встановлення кольорів тексту та фону
void Button::setColors(sf::Color textColor, sf::Color bgColor) {
    text.setFillColor(textColor);
    background.setFillColor(bgColor);
}

// Метод для відтворення звуку натискання
void Button::playClickSound() {
    clickSound.play();
}