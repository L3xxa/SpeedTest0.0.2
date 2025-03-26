#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <string>

class TextManager {
private:
    std::string targetText;                      // Цільовий текст
    std::string inputText;                       // Введений текст
    int mistakes;                                // Кількість помилок
    std::string loadRandomText();                // Завантажує випадковий текст з файлу

public:
    TextManager();                               // Конструктор, що ініціалізує TextManager та завантажує випадковий цільовий текст
    void setTargetText(const std::string& text); // Встановлює цільовий текст та скидає введений текст і кількість помилок
    void addInput(char c);                       // Додає введений символ до введеного тексту та перевіряє на помилки
    void deleteLastInput();                      // Видаляє останній введений символ
    int getMistakes() const;                     // Повертає кількість помилок
    std::string getInputText() const;            // Повертає введений текст
    std::string getTargetText() const;           // Повертає цільовий текст
    void reset();                                // Скидає цільовий текст, введений текст та кількість помилок
};

#endif // TEXTMANAGER_H