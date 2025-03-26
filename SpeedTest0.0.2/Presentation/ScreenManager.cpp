#include "ScreenManager.h"
#include <iostream>

ScreenManager::ScreenManager()
    : window(sf::VideoMode(1920, 1080), "Speed Typing Test", sf::Style::Fullscreen),
      font(),
      startScreen(font, window),
      game(),
      gameScreen(window, font, game),
      scoreRepo("scores.txt"),
      endScreen(window, font, scoreRepo, game),
      statScreen(window, font, scoreRepo),
      currentScreen(ScreenType::Start) {
    if (!font.loadFromFile("assets/font/SegUIVar.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        exit(-1);
    }
    startScreen.initialize();
    gameScreen.initialize();
    endScreen.initialize();
    statScreen.initialize();
}

// Метод для запуску головного циклу програми
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
                    game.reset();
                    switchScreen(ScreenType::Game);
                    game.start();
                }
                if (startScreen.isStatisticsButtonPressed(event)) { // Використовуємо новий метод
                    switchScreen(ScreenType::Stats);
                }
            } else if (currentScreen == ScreenType::Game) {
                gameScreen.handleEvent(event);
            } else if (currentScreen == ScreenType::End) {
                endScreen.handleEvent(event, *this);
            } else if (currentScreen == ScreenType::Stats) {
                statScreen.handleEvent(event, *this);
            }
        }

        if (currentScreen == ScreenType::Start) {
            startScreen.draw();
        } else if (currentScreen == ScreenType::Game) {
            game.update();
            gameScreen.update();
            gameScreen.draw();
            if (gameScreen.isGameOver()) {
                endScreen.setStats(game.calculateWPM(), game.calculateAccuracy(), game.getMistakes(), static_cast<int>(game.getRemainingTime()));
                switchScreen(ScreenType::End);
            }
        } else if (currentScreen == ScreenType::End) {
            endScreen.draw();
        } else if (currentScreen == ScreenType::Stats) {
            statScreen.draw();
        }
    }
}

// Метод для переключення екрану
void ScreenManager::switchScreen(ScreenType screen) {
    currentScreen = screen;
}