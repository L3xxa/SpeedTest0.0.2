#include "ScreenManager.h"
#include <iostream>

ScreenManager::ScreenManager() :
    window(sf::VideoMode(1920, 1080), "Speed Typing Test", sf::Style::Fullscreen),
    font(),
    startScreen(font, window),
    gameScreen(window, font),
    endScreen(window, font),
    currentScreen(ScreenType::Start) {
    if (!font.loadFromFile("assets/font/BOOKOS.TTF")) {
        std::cerr << "Error loading font" << std::endl;
        exit(-1);
    }
    startScreen.initialize();
    gameScreen.initialize();
    endScreen.initialize();
}

void ScreenManager::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            if (currentScreen == ScreenType::Start) {
                if (startScreen.handleEvent(event)) {
                    window.close();
                }
                if (startScreen.isStartButtonPressed()) {
                    switchScreen(ScreenType::Game);
                    gameScreen.startGame();
                }
            } else if (currentScreen == ScreenType::Game) {
                gameScreen.handleEvent(event);
                if (gameScreen.isGameOver()) {
                    switchScreen(ScreenType::End); // Перехід на EndScreen при завершенні гри
                }
            }
        }

        if (currentScreen == ScreenType::Start) {
            startScreen.draw();
        } else if (currentScreen == ScreenType::Game) {
            gameScreen.update();
            gameScreen.draw();
        } else if (currentScreen == ScreenType::End) {
            endScreen.draw();
        }
    }
}

void ScreenManager::switchScreen(ScreenType screen) {
    currentScreen = screen;
}