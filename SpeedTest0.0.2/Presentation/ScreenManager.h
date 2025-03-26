#ifndef SCREENMANAGER_H_
#define SCREENMANAGER_H_

#include <SFML/Graphics.hpp>
#include "Screens/StartScreen.h"
#include "Screens/GameScreen.h"
#include "Screens/EndScreen.h"
#include "Screens/StatScreen.h"
#include "../../Domain/Game.h"
#include "../../Data/ScoreRepository.h"

enum class ScreenType { Start, Game, End, Stats };

class ScreenManager {
private:
    sf::RenderWindow window;       // Вікно програми
    sf::Font font;                 // Шрифт
    StartScreen startScreen;       // Екран старту
    Game game;                     // Гра
    GameScreen gameScreen;         // Екран гри
    ScoreRepository scoreRepo;     // Репозиторій результатів
    EndScreen endScreen;           // Екран завершення
    StatScreen statScreen;         // Екран статистики
    ScreenType currentScreen;      // Поточний екран
    
    public:
    ScreenManager();               // Конструктор
    void run();                    // Метод для запуску головного циклу програми
    void switchScreen(ScreenType screen); // Метод для переключення екрану
};

#endif // SCREENMANAGER_H_