#include "Game.h"

Game::Game() : timer(20.0f), textManager(), isRunning(false) {}

void Game::start() {
    textManager.reset();
    timer.reset(); // Скидаємо таймер перед стартом
    timer.start();
    isRunning = true;
}

void Game::update() {
    if (isRunning && timer.isFinished()) {
        isRunning = false;
    }
}

void Game::handleInput(char c) {
    if (isRunning && !timer.isFinished()) {
        textManager.addInput(c);
        if (textManager.getInputText() == textManager.getTargetText()) {
            isRunning = false;
            timer.stop();
        }
    }
}

bool Game::isFinished() const {
    return timer.isFinished() || (textManager.getInputText() == textManager.getTargetText());
}

int Game::getMistakes() const { return textManager.getMistakes(); }
std::string Game::getInputText() const { return textManager.getInputText(); }
std::string Game::getTargetText() const { return textManager.getTargetText(); }
float Game::getRemainingTime() const { return timer.getRemainingTime(); }

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

float Game::calculateAccuracy() const {
    std::string target = textManager.getTargetText();
    std::string input = textManager.getInputText();
    int correct = 0;
    for (size_t i = 0; i < input.size() && i < target.size(); i++) {
        if (input[i] == target[i]) correct++;
    }
    return input.empty() ? 0 : (correct * 100.0f / input.size());
}

void Game::reset() {
    timer.reset();
    textManager.reset();
    isRunning = false;
}