#pragma once
#include <SFML/Graphics.hpp>
#include "Screens/StartScreen.h"
#include "Screens/GameScreen.h"
#include "Screens/EndScreen.h"

enum class ScreenType { Start, Game, End };

class ScreenManager {
private:
    sf::RenderWindow window;
    sf::Font font;
    StartScreen startScreen;
    GameScreen gameScreen;
    EndScreen endScreen;
    ScreenType currentScreen;

public:
    ScreenManager();
    void run();
    void switchScreen(ScreenType screen);
};