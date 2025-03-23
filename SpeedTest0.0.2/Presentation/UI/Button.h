#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Button {
private:
    sf::Text text;
    sf::RectangleShape background;
    sf::Sound clickSound;
    sf::SoundBuffer clickSoundBuffer;

public:
    Button(sf::Font& font, const std::string& label, sf::Vector2f position, sf::Vector2f size);
    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2i mousePos) const;
    void setColors(sf::Color textColor, sf::Color bgColor);
    void playClickSound();
};