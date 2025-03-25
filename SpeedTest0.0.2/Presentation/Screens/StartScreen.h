#pragma once
#include <SFML/Graphics.hpp>
#include "../UI/Button.h"

class StartScreen {
private:
    sf::RenderWindow& window;
    sf::Font& font;
    Button startButton;
    Button statisticsButton; // Залишаємо приватною
    Button exitButton;
    sf::RectangleShape menuBar;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool startButtonPressed;

public:
    StartScreen(sf::Font& font, sf::RenderWindow& window);
    void initialize();
    void draw();
    bool handleEvent(const sf::Event& event);
    bool isStartButtonPressed() const;
    bool isStatisticsButtonPressed(const sf::Event& event); // Новий метод
};