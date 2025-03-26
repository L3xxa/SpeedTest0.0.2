#ifndef GAME_H
#define GAME_H
#include "Timer.h"
#include "TextManager.h"

class Game {
private:
    Timer timer;
    TextManager textManager;
    bool isRunning;

public:
    Game();
    void start();
    void update();
    void handleInput(char c);
    bool isFinished() const;
    int getMistakes() const;
    std::string getInputText() const;
    std::string getTargetText() const;
    float getRemainingTime() const;
    float calculateWPM() const;
    float calculateAccuracy() const;
    void reset();
};

#endif // GAME_H