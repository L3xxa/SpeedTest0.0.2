#pragma once
#include <SFML/System.hpp>

class Timer {
private:
    sf::Clock clock;
    float duration;         // Початкова тривалість (62 секунди)
    float remainingTime;    // Залишок часу
    bool isRunning;

public:
    Timer(float initialDuration = 62.0f);
    void start();
    void stop();
    float getRemainingTime() const;
    bool isFinished() const;
    void reset();
};