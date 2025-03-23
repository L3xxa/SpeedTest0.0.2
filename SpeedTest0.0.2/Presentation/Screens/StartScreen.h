#pragma once
#include <SFML/Graphics.hpp>
#include "../UI/Button.h"

class StartScreen {
private:
    sf::RenderWindow& window;
    sf::Font& font;
    Button startButton;
    Button statisticsButton;
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
};