#include "Timer.h"

Timer::Timer(float initialDuration) : duration(initialDuration), remainingTime(initialDuration), isRunning(false) {}

void Timer::start() {
    if (!isRunning) {
        clock.restart();
        isRunning = true;
    }
}

void Timer::stop() {
    isRunning = false;
}

float Timer::getRemainingTime() const {
    if (isRunning) {
        float elapsed = clock.getElapsedTime().asSeconds();
        float remaining = remainingTime - elapsed;
        return (remaining < 0.0f) ? 0.0f : remaining; // Обмежуємо від’ємні значення
    }
    return remainingTime;
}

bool Timer::isFinished() const {
    bool finished = isRunning && getRemainingTime() <= 0.0f;
    if (finished) {
        const_cast<Timer*>(this)->isRunning = false; // Зупиняємо таймер, коли час закінчується
    }
    return finished;
}

void Timer::reset() {
    remainingTime = duration;
    isRunning = false;
    clock.restart();
}