#pragma once
#include <SFML/Graphics.hpp>
#include "Screens/StartScreen.h"
#include "Screens/GameScreen.h"
#include "Screens/EndScreen.h"
#include "Screens/StatScreen.h" // Додаємо новий екран
#include "../../Domain/Game.h"
#include "../../Data/ScoreRepository.h"

enum class ScreenType { Start, Game, End, Stats }; // Додаємо Stats

class ScreenManager {
private:
    sf::RenderWindow window;
    sf::Font font;
    StartScreen startScreen;
    Game game;
    GameScreen gameScreen;
    ScoreRepository scoreRepo;
    EndScreen endScreen;
    StatScreen statScreen; // Новий екран
    ScreenType currentScreen;

public:
    ScreenManager();
    void run();
    void switchScreen(ScreenType screen);
};