#ifndef StartScreen_H
#define StartScreen_H

#include <SFML/Graphics.hpp>
#include "../UI/Button.h"

class StartScreen {
private:
    sf::RenderWindow& window;    // Вікно для відображення
    sf::Font& font;              // Шрифт для тексту
    Button startButton;          // Кнопка "Start"
    Button statisticsButton;     // Кнопка "Statistics"
    Button exitButton;           // Кнопка "Exit"
    sf::RectangleShape menuBar;  // Фон для меню
    sf::Texture backgroundTexture; // Текстура фону
    sf::Sprite backgroundSprite; // Спрайт фону
    bool startButtonPressed;     // Прапорець натискання кнопки "Start"
    
    public:
    StartScreen(sf::Font& font, sf::RenderWindow& window); // Конструктор
    void initialize();                                     // Метод для ініціалізації елементів екрану
    void draw();                                           // Метод для відображення елементів екрану
    bool handleEvent(const sf::Event& event);              // Метод для обробки подій
    bool isStartButtonPressed() const;                     // Метод для перевірки натискання кнопки "Start"
    bool isStatisticsButtonPressed(const sf::Event& event); // Метод для перевірки натискання кнопки "Statistics"
};

#endif // StartScreen_H