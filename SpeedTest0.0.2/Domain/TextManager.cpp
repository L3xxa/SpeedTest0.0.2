#include "TextManager.h"
#include <fstream>
#include <sstream>
#include <random>
#include <iostream>

TextManager::TextManager() : mistakes(0) {
    targetText = loadRandomText();
}

// Завантажує випадковий текст з файлу
std::string TextManager::loadRandomText() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    int randomNum = dis(gen);
    std::string filename = "assets/TXT/Text_" + std::to_string(randomNum) + ".txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "Kyiv is a large political, industrial, and cultural center of Ukraine."
               " It has a rich history, beautiful architecture, and a vibrant atmosphere."
               " The city plays a crucial role in the country’s economy, education, and governance, "
               "attracting tourists and professionals from all over the world."; // Запасний текст
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

// Встановлює цільовий текст та скидає введений текст і кількість помилок
void TextManager::setTargetText(const std::string& text) {
    targetText = text;
    inputText.clear();
    mistakes = 0;
}

// Додає введений символ до введеного тексту та перевіряє на помилки
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
// Видаляє останній введений символ
void TextManager::deleteLastInput() { 
    if (!inputText.empty()) {
        inputText.pop_back();
    }
}

// Повертає кількість помилок
int TextManager::getMistakes() const { return mistakes; }

// Повертає введений текст
std::string TextManager::getInputText() const { return inputText; }

// Повертає цільовий текст
std::string TextManager::getTargetText() const { return targetText; }

// Скидає цільовий текст, введений текст та кількість помилок
void TextManager::reset() {
    targetText = loadRandomText();
    inputText.clear();
    mistakes = 0;
}