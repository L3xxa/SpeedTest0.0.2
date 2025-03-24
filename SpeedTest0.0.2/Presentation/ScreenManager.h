#pragma once
#include <SFML/Graphics.hpp>
#include "Screens/StartScreen.h"
#include "Screens/GameScreen.h"
#include "Screens/EndScreen.h"
#include "../../Domain/Game.h"
#include "../../Data/ScoreRepository.h"

enum class ScreenType { Start, Game, End };

class ScreenManager {
private:
    sf::RenderWindow window;
    sf::Font font;
    StartScreen startScreen;
    Game game;
    GameScreen gameScreen;
    ScoreRepository scoreRepo;
    EndScreen endScreen;
    ScreenType currentScreen;

public:
    ScreenManager();
    void run();
    void switchScreen(ScreenType screen);
};