#ifndef SCOREREPOSITORY_H
#define SCOREREPOSITORY_H
#include <string>
#include <vector>

struct Score {
    float wpm;         // Швидкість набору (слів за хвилину)
    float accuracy;    // Точність (%)
    int mistakes;      // Кількість помилок
    int times;         // Залишковий час (у секундах)
    std::string points; // Оцінка: "bad", "norm", "good", "excellent"
    std::string date;   // Дата і час гри
};

class ScoreRepository {
private:
    std::string filename;
    std::vector<Score> scores;
    void saveToFile();
    void loadFromFile();

public:
    ScoreRepository(const std::string& filename);
    void addScore(float wpm, float accuracy, int mistakes, int times, const std::string& points);
    std::vector<Score> getScores() const;
    Score getBestScore() const;
};

#endif // SCOREREPOSITORY_H