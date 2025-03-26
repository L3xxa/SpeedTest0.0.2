#include "Game.h"

Game::Game() : timer(1.0f), textManager(), isRunning(false) {}

// Починає гру, скидаючи таймер і текстовий менеджер, та встановлює isRunning в true
void Game::start() {
    textManager.reset();
    timer.reset();
    timer.start();
    isRunning = true;
}

// Оновлює стан гри, перевіряючи, чи закінчився таймер
void Game::update() {
    if (isRunning && timer.isFinished()) {
        isRunning = false;
    }
}

// Обробляє введення користувача, додаючи символ до текстового менеджера та перевіряючи, чи завершена гра
void Game::handleInput(char c) {
    if (isRunning && !timer.isFinished()) {
        textManager.addInput(c);
        if (textManager.getInputText() == textManager.getTargetText()) {
            isRunning = false;
            timer.stop();
        }
    }
}

// Перевіряє, чи завершена гра
bool Game::isFinished() const {
    return timer.isFinished() || (textManager.getInputText() == textManager.getTargetText());
}

// Повертає кількість помилок
int Game::getMistakes() const { return textManager.getMistakes(); }

// Повертає введений текст
std::string Game::getInputText() const { return textManager.getInputText(); }

// Повертає цільовий текст
std::string Game::getTargetText() const { return textManager.getTargetText(); }

// Повертає залишковий час
float Game::getRemainingTime() const { return timer.getRemainingTime(); }

// Обчислює кількість слів за хвилину (WPM)
float Game::calculateWPM() const {
    int wordCount = 0;
    std::string target = textManager.getTargetText();
    for (char c : target) {
        if (c == ' ') wordCount++;
    }
    wordCount++;
    float minutes = (60.0f - timer.getRemainingTime()) / 60.0f;
    return minutes > 0 ? (wordCount / minutes) : 0;
}

// Обчислює точність введення (%)
float Game::calculateAccuracy() const {
    std::string target = textManager.getTargetText();
    std::string input = textManager.getInputText();
    int correct = 0;
    for (size_t i = 0; i < input.size() && i < target.size(); i++) {
        if (input[i] == target[i]) correct++;
    }
    return input.empty() ? 0 : (correct * 100.0f / input.size());
}

// Скидає гру, таймер і текстовий менеджер, та встановлює isRunning в false
void Game::reset() {
    timer.reset();
    textManager.reset();
    isRunning = false;
}