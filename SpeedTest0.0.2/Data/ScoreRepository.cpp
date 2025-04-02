#include "ScoreRepository.h"
#include "../Data/FileManager.h"
#include <sstream>
#include <ctime>

ScoreRepository::ScoreRepository(const std::string& filename) : filename(filename) {
    loadFromFile();
}

// Додає новий результат до репозиторію та зберігає його у файл
void ScoreRepository::addScore(float wpm, float accuracy, int mistakes, int times, const std::string& points) {
    time_t now = time(0);
    char dateBuffer[26];
    if (ctime_s(dateBuffer, sizeof(dateBuffer), &now) == 0) {
        std::string date(dateBuffer);
        date.pop_back();
        scores.push_back({wpm, accuracy, mistakes, times, points, date});
        saveToFile();
    } else {
        scores.push_back({wpm, accuracy, mistakes, times, points, "Unknown date"});
        saveToFile();
    }
}


// Повертає всі результати у репозиторії
std::vector<Score> ScoreRepository::getScores() const { return scores; }

// Повертає найкращий результат за кількістю слів за хвилину (wpm)
Score ScoreRepository::getBestScore() const {
    if (scores.empty()) return {0, 0, 0, 0, "bad", ""};
    Score best = scores[0];
    for (const auto& score : scores) {
        if (score.wpm > best.wpm) best = score;
    }
    return best;
}

// Зберігає всі результати у файл
void ScoreRepository::saveToFile() {
    FileManager fm;
    std::stringstream ss;
    for (const auto& score : scores) {
        ss << score.wpm << " " << score.accuracy << " " << score.mistakes << " "
           << score.times << " " << score.points << " " << score.date << "\n";
    }
    fm.writeFile(filename, ss.str());
}

// Завантажує всі результати з файлу
void ScoreRepository::loadFromFile() { 
    FileManager fm; 
    std::string content = fm.readFile(filename);
    std::stringstream ss(content);
    scores.clear();
    float wpm, accuracy;
    int mistakes, times;
    std::string points, date;
    while (ss >> wpm >> accuracy >> mistakes >> times >> points) {
        std::getline(ss, date);
        if (!date.empty() && date[0] == ' ') date.erase(0, 1);
        scores.push_back({wpm, accuracy, mistakes, times, points, date});
    }
}