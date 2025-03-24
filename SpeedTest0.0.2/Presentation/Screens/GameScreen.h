#pragma once
#include <SFML/Graphics.hpp>
#include "../../Domain/Game.h"

class GameScreen {
private:
    sf::RenderWindow& window;
    sf::Font& font;
    Game& game;
    sf::Text inputText;
    sf::Text targetText;
    sf::Text timeText;
    sf::Text mistakeText;
    sf::RectangleShape mistakeBackground;
    sf::RectangleShape inputTextBackground;
    sf::RectangleShape outputTextBackground;
    sf::CircleShape timeBackground;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    std::string wrapText(const std::string& text, float maxWidth) const;

public:
    GameScreen(sf::RenderWindow& window, sf::Font& font, Game& game);
    void initialize();
    void draw();
    void update();
    void handleEvent(const sf::Event& event);
    bool isGameOver() const;
};