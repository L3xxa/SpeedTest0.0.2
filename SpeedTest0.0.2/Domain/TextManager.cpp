#include "TextManager.h"
#include <fstream>
#include <sstream>
#include <random>
#include <iostream>

TextManager::TextManager() : mistakes(0) {
    targetText = loadRandomText();
}

std::string TextManager::loadRandomText() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    int randomNum = dis(gen);
    std::string filename = "assets/TXT/Text_" + std::to_string(randomNum) + ".txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "Kyiv is a large political, industrial and cultural centre..."; // Твій запасний текст
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

void TextManager::setTargetText(const std::string& text) {
    targetText = text;
    inputText.clear();
    mistakes = 0;
}

void TextManager::addInput(char c) {
    if (c == 8 && !inputText.empty()) {
        deleteLastInput();
        return;
    }
    if (c >= 32 && c <= 126) {
        inputText += c;
        if (inputText.size() <= targetText.size()) {
            if (inputText.back() != targetText[inputText.size() - 1]) {
                mistakes++;
            } else if (inputText.size() > 1) {
                char prevInput = inputText[inputText.size() - 2];
                char prevTarget = targetText[inputText.size() - 2];
                if (prevInput != prevTarget) mistakes--;
            }
        }
    }
}

void TextManager::deleteLastInput() {
    if (!inputText.empty()) {
        inputText.pop_back();
    }
}

int TextManager::getMistakes() const { return mistakes; }
std::string TextManager::getInputText() const { return inputText; }
std::string TextManager::getTargetText() const { return targetText; }

void TextManager::reset() {
    targetText = loadRandomText();
    inputText.clear();
    mistakes = 0;
}