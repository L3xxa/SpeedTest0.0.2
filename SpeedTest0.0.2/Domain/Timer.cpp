#include "Timer.h"

Timer::Timer(float initialDuration) : duration(initialDuration), remainingTime(initialDuration), isRunning(false) {}

void Timer::start() {
    if (!isRunning) {
        clock.restart(); // Скидаємо clock при старті
        isRunning = true;
    }
}

void Timer::stop() {
    isRunning = false;
}

float Timer::getRemainingTime() const {
    if (isRunning) {
        float elapsed = clock.getElapsedTime().asSeconds();
        float remaining = duration - elapsed; // Використовуємо duration замість remainingTime
        return (remaining < 0.0f) ? 0.0f : remaining;
    }
    return remainingTime; // Повертаємо залишковий час, якщо таймер зупинений
}

bool Timer::isFinished() const {
    return isRunning && getRemainingTime() <= 0.0f;
}

void Timer::reset() {
    clock.restart();
    remainingTime = duration;
    isRunning = false;
}