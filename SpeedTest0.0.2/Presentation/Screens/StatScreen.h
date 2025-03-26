#ifndef STATSCREEN_H
#define STATSCREEN_H
#include <SFML/Graphics.hpp>
#include "../../Data/ScoreRepository.h"
#include "../UI/Button.h"

class ScreenManager;

class StatScreen {
private:
    sf::RenderWindow& window;              // Вікно рендерингу
    sf::Font& font;                        // Шрифт
    ScoreRepository& scoreRepo;            // Репозиторій результатів
    Button backButton;                     // Кнопка "Назад"
    sf::RectangleShape backgroundButton;   // Фонова кнопка
    sf::Texture backgroundTexture;         // Текстура фону
    sf::Sprite backgroundSprite;           // Спрайт фону
    sf::RectangleShape tableBackground;    // Фон таблиці
    std::vector<sf::RectangleShape> cells; // Комірки таблиці
    std::vector<sf::Text> texts;           // Тексти в таблиці
    sf::RectangleShape scrollbar;          // Скролбар
    float scrollOffset;                    // Зміщення скролу
    float maxScroll;                       // Максимальне зміщення скролу
    int rows;                              // Кількість рядків
    
    void updateTable();                    // Метод для оновлення таблиці
    
    public:
    StatScreen(sf::RenderWindow& window, sf::Font& font, ScoreRepository& scoreRepo); // Конструктор
    void initialize();                                                                // Метод для ініціалізації
    void draw();                                                                      // Метод для відображення елементів екрану
    void handleEvent(const sf::Event& event, ScreenManager& screenManager);           // Метод для обробки подій
};

#endif // STATSCREEN_H