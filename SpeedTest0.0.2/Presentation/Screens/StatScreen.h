#pragma once
#include <SFML/Graphics.hpp>
#include "../../Data/ScoreRepository.h"
#include "../UI/Button.h"

class ScreenManager;

class StatScreen {
private:
    sf::RenderWindow& window;
    sf::Font& font;
    ScoreRepository& scoreRepo;
    Button backButton;
    sf::RectangleShape backgroundButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape tableBackground;
    std::vector<sf::RectangleShape> cells;
    std::vector<sf::Text> texts;
    sf::RectangleShape scrollbar;
    float scrollOffset;
    float maxScroll;
    int rows;

    void updateTable();

public:
    StatScreen(sf::RenderWindow& window, sf::Font& font, ScoreRepository& scoreRepo);
    void initialize();
    void draw();
    void handleEvent(const sf::Event& event, ScreenManager& screenManager);
};