#pragma once
#include <SFML/Graphics.hpp>
#include "../../Data/ScoreRepository.h"
#include "../UI/Button.h"

class Game;
class ScreenManager; // Попереднє оголошення для handleEvent

class EndScreen {
private:
    sf::RenderWindow& window;
    sf::Font& font;
    ScoreRepository& scoreRepo;
    Game& game;
    sf::Text endTitle;
    sf::Text statsText;
    sf::RectangleShape statsBackground;
    Button restartButton;
    Button exitButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape backgroundMenu;

    void setBackgroundFullScreen();
    std::string calculatePoints(float wpm, float accuracy, int mistakes, int times);

public:
    EndScreen(sf::RenderWindow& window, sf::Font& font, ScoreRepository& scoreRepo, Game& game);
    void initialize();
    void draw();
    void handleEvent(const sf::Event& event, ScreenManager& screenManager); 
    void setStats(float wpm, float accuracy, int mistakes, int times);
};