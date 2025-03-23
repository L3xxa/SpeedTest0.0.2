#pragma once
#include <string>

class TextManager {
private:
    std::string targetText;
    std::string inputText;
    int mistakes;
    std::string loadRandomText(); // Нова функція для зчитування рандомного тексту

public:
    TextManager();
    void setTargetText(const std::string& text);
    void addInput(char c);
    void deleteLastInput(); 
    int getMistakes() const;
    std::string getInputText() const;
    std::string getTargetText() const;
    void reset();
};