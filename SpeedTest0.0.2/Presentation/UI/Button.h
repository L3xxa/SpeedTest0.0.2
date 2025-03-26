#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Button {
private:
    sf::Text text;                      // Текст кнопки
    sf::RectangleShape background;      // Фон кнопки
    sf::Sound clickSound;               // Звук натискання
    sf::SoundBuffer clickSoundBuffer;   // Буфер звуку натискання
    
    public:
    Button(sf::Font& font, const std::string& label, sf::Vector2f position, sf::Vector2f size); // Конструктор
    void draw(sf::RenderWindow& window);                                                        // Метод для відображення кнопки
    bool isClicked(sf::Vector2i mousePos) const;                                                // Метод для перевірки натискання кнопки
    void setColors(sf::Color textColor, sf::Color bgColor);                                     // Метод для встановлення кольорів тексту та фону
    void playClickSound();                                                                      // Метод для відтворення звуку натискання
};

#endif // BUTTON_H