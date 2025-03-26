#include "Timer.h"

Timer::Timer(float initialDuration) : duration(initialDuration), remainingTime(initialDuration), isRunning(false) {}

// Запускає таймер
void Timer::start() {
    if (!isRunning) {
        clock.restart();
        isRunning = true;
    }
}

// Зупиняє таймер
void Timer::stop() {
    isRunning = false;
}

// Повертає залишок часу, якщо таймер запущений, інакше повертає залишок часу при зупинці
float Timer::getRemainingTime() const {
    if (isRunning) {
        float elapsed = clock.getElapsedTime().asSeconds();
        float remaining = duration - elapsed;
        return (remaining < 0.0f) ? 0.0f : remaining;
    }
    return remainingTime;
}

// Повертає час, що пройшов від початку таймера
// Повертає true, якщо таймер завершився
bool Timer::isFinished() const {
    return isRunning && getRemainingTime() <= 0.0f;
}

// Скидає таймер до початкового стану
void Timer::reset() {
    clock.restart();
    remainingTime = duration;
    isRunning = false;
}