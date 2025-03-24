#pragma once
#include <SFML/System.hpp>

class Timer {
private:
    sf::Clock clock;
    float duration;
    float remainingTime;
    bool isRunning;

public:
    Timer(float initialDuration = 60.0f);
    void start();
    void stop();
    float getRemainingTime() const;
    bool isFinished() const;
    void reset();
};