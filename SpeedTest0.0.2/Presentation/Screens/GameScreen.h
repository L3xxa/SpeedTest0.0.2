#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include <SFML/Graphics.hpp>
#include "../../Domain/Game.h"

class GameScreen {
private:
    sf::RenderWindow& window;                    // Вікно для відображення
        sf::Font& font;                          // Шрифт для тексту
        Game& game;                              // Гра
        sf::Text inputText;                      // Текст введеного тексту
        sf::Text targetText;                     // Текст цільового тексту
        sf::Text timeText;                       // Текст часу
        sf::Text mistakeText;                    // Текст помилок
        sf::RectangleShape mistakeBackground;    // Фон для тексту помилок
        sf::RectangleShape inputTextBackground;  // Фон для введеного тексту
        sf::RectangleShape outputTextBackground; // Фон для цільового тексту
        sf::CircleShape timeBackground;          // Фон для часу
        sf::Texture backgroundTexture;           // Текстура фону
        sf::Sprite backgroundSprite;             // Спрайт фону
    
        std::string wrapText(const std::string& text, float maxWidth) const; // Метод для обгортання тексту
    
    public:
        GameScreen(sf::RenderWindow& window, sf::Font& font, Game& game); // Конструктор
        void initialize();                                                // Метод для ініціалізації елементів екрану
        void draw();                                                      // Метод для відображення елементів екрану
        void update();                                                    // Метод для оновлення елементів екрану
        void handleEvent(const sf::Event& event);                         // Метод для обробки подій
        bool isGameOver() const;                                          // Метод для перевірки закінчення гри
};

#endif // GAMESCREEN_H