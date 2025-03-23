#pragma once
#include <SFML/Graphics.hpp>

class EndScreen {
private:
    sf::RenderWindow& window;
    sf::Font& font;
    sf::Text timeUpText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    EndScreen(sf::RenderWindow& window, sf::Font& font);
    void initialize();
    void draw();
};