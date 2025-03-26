#ifndef ENDSCREEN_H
#define ENDSCREEN_H
#include <SFML/Graphics.hpp>
#include "../../Data/ScoreRepository.h"
#include "../UI/Button.h"

class Game;          // Попереднє оголошення для Game
class ScreenManager; // Попереднє оголошення для handleEvent

class EndScreen {
private:
   sf::RenderWindow& window;                // Вікно для відображення
        sf::Font& font;                     // Шрифт для тексту
        ScoreRepository& scoreRepo;         // Репозиторій для збереження результатів
        Game& game;                         // Гра
        sf::Text endTitle;                  // Текст заголовку
        sf::Text statsText;                 // Текст статистики
        sf::RectangleShape statsBackground; // Фон для статистики
        Button restartButton;               // Кнопка перезапуску
        Button exitButton;                  // Кнопка виходу
        sf::Texture backgroundTexture;      // Текстура фону
        sf::Sprite backgroundSprite;        // Спрайт фону
        sf::RectangleShape backgroundMenu;  // Фон для меню
    
        void setBackgroundFullScreen();      // Встановлює фон на весь екран
        std::string calculatePoints(float wpm, float accuracy, int mistakes, int times); // Обчислює очки
    
    public:
        EndScreen(sf::RenderWindow& window, sf::Font& font, ScoreRepository& scoreRepo, Game& game); // Конструктор
        void initialize(); // Ініціалізує елементи екрану
        void draw(); // Відображає елементи екрану
        void handleEvent(const sf::Event& event, ScreenManager& screenManager); // Обробляє події
        void setStats(float wpm, float accuracy, int mistakes, int times); // Встановлює статистику
};

#endif // ENDSCREEN_H