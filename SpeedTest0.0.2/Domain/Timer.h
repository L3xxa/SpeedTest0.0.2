#ifndef  TIMER_H
#define TIMER_H

#include <SFML/System.hpp>

class Timer {
private:
    sf::Clock clock;
    float duration;
    float remainingTime;
    bool isRunning;

public:
    Timer(float initialDuration = 60.0f);  // Конструктор, що ініціалізує таймер з початковою тривалістю
        void start();                      // Запускає таймер
        void stop();                       // Зупиняє таймер
        float getRemainingTime() const;    // Повертає залишок часу
        bool isFinished() const;           // Перевіряє, чи завершився таймер
        void reset();                      // Скидає таймер до початкового стану
};

#endif // TIMER_H