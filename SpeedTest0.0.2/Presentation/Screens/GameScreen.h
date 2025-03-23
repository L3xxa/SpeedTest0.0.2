#pragma once
#include <SFML/Graphics.hpp>
#include "../../Domain/Timer.h"
#include "../../Domain/TextManager.h"

class GameScreen {
private:
    sf::RenderWindow& window;
    sf::Font& font;
    Timer timer;
    TextManager textManager;
    sf::Text inputText;
    sf::Text targetText;
    sf::Text timeText;
    sf::Text mistakeText;
    sf::RectangleShape inputTextBackground;
    sf::RectangleShape outputTextBackground;
    sf::CircleShape timeBackground;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool gameOver; // Додаємо змінну для стану

public:
    GameScreen(sf::RenderWindow& window, sf::Font& font);
    void initialize();
    void draw();
    void update();
    void handleEvent(const sf::Event& event);
    void startGame();
    bool isGameOver() const;
};