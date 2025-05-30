﻿#include "ScreenManager.h"
#include <iostream>

ScreenManager::ScreenManager()
    : window(sf::VideoMode(1920, 1080), "Speed Typing Test", sf::Style::Default),
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

    sf::Image icon;
    if (!icon.loadFromFile("assets/img/Game_logo (1).jpg")) {
        std::cerr << "Error loading icon" << std::endl;
    } else {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
                    gameScreen.playTypingMusic(); // Починаємо відтворювати музику при старті гри
                }
                if (startScreen.isStatisticsButtonPressed(event)) {
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
                gameScreen.stopTypingMusic(); // Зупиняємо музику, коли гра закінчується
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
    // Зупиняємо музику при перемиканні на будь-який екран, крім Game
    if (screen != ScreenType::Game) {
        gameScreen.stopTypingMusic();
    }
    currentScreen = screen;
}