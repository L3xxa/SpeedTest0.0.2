#include "StatScreen.h"
#include "../ScreenManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>

const float SCALE_FACTOR = 1.0f;
const int COLS = 6;
const int ROW_HEIGHT = 40;

StatScreen::StatScreen(sf::RenderWindow& window, sf::Font& font, ScoreRepository& scoreRepo)
    : window(window), font(font), scoreRepo(scoreRepo),
      backButton(font, "Back", sf::Vector2f(870, 950), sf::Vector2f(200, 60)),
      scrollOffset(0.0f), maxScroll(0.0f), rows(0) {
    if (!backgroundTexture.loadFromFile("assets/img/BACKGROUND_VIBE_2.jpg")) {
        std::cerr << "Failed to load background" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    sf::Vector2u windowSize = window.getSize();
    backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / backgroundTexture.getSize().x,
        static_cast<float>(windowSize.y) / backgroundTexture.getSize().y
    );
    backButton.setColors(sf::Color(0,0,0), sf::Color(207, 209, 209, 200));
}

// Метод для ініціалізації елементів екрану
void StatScreen::initialize() {
    sf::Vector2u windowSize = window.getSize();
    float tableWidth = windowSize.x * 0.8f;
    float tableHeight = windowSize.y * 0.7f;
    float tableX = (windowSize.x - tableWidth) / 2;
    float tableY = (windowSize.y - tableHeight) / 2;
    
    tableBackground.setSize(sf::Vector2f(tableWidth, tableHeight));
    tableBackground.setFillColor(sf::Color(0, 0, 0, 220));
    tableBackground.setPosition(tableX, tableY);
    
    updateTable();
}

// Метод для оновлення таблиці
void StatScreen::updateTable() {
    cells.clear();
    texts.clear();
    auto scores = scoreRepo.getScores();
    rows = scores.size() + 1; // Зберігаємо кількість рядків
    sf::Vector2f tablePos = tableBackground.getPosition();
    sf::Vector2f tableSize = tableBackground.getSize();
    float cellWidth = tableSize.x / COLS;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < COLS; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellWidth, ROW_HEIGHT));
            cell.setPosition(tablePos.x + j * cellWidth, tablePos.y + i * ROW_HEIGHT);
            cell.setFillColor(sf::Color(255, 255, 255, 50));
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::White);
            cells.push_back(cell);

            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(18);
            text.setFillColor(sf::Color::White);
            text.setPosition(cell.getPosition().x + 10, cell.getPosition().y + 5);

            if (i == 0) {
                static const std::string headers[] = {"WPM", "Accuracy", "Mistakes", "Time`s left", "Points", "Date"};
                text.setString(headers[j]);
            } else {
                const auto& score = scores[i - 1];
                switch (j) {
                    case 0: text.setString(std::to_string(static_cast<int>(score.wpm))); break;
                    case 1: text.setString(std::to_string(static_cast<int>(score.accuracy)) + "%"); break;
                    case 2: text.setString(std::to_string(score.mistakes)); break;
                    case 3: text.setString(std::to_string(score.times)); break;
                    case 4: text.setString(score.points); break;
                    case 5: {
                        // Форматуємо дату у форматі MM/DD/YYYY
                       std::tm tm = {};
                        std::istringstream ss(score.date);
                        ss >> std::get_time(&tm, "%a %b %d %H:%M:%S"); // Парсимо строку в структуру tm
                        
                        std::ostringstream formattedDate;
                        formattedDate << std::put_time(&tm, "%m/%d %H:%M:%S"); // Форматуємо як MM/DD HH:MM:SS
                        text.setString(formattedDate.str()); // Виводимо відформатовану дату
                        break;
                    }
                }
            }
            texts.push_back(text);
        }
    }

    maxScroll = std::max(0.0f, static_cast<float>(rows * ROW_HEIGHT - tableBackground.getSize().y));
    std::cout << "Rows: " << rows << ", Row Height: " << ROW_HEIGHT << ", Table Height: " << tableBackground.getSize().y << ", Max Scroll: " << maxScroll << std::endl;
}

// Метод для відображення елементів екрану
void StatScreen::draw() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(tableBackground);

    // Отримуємо позицію та розміри таблиці
    sf::Vector2f tablePos = tableBackground.getPosition();
    float tableHeight = tableBackground.getSize().y;

    // Малюємо комірки та текст із урахуванням scrollOffset
    for (size_t i = 0; i < cells.size(); ++i) {
        // Зміщуємо комірку та текст на основі scrollOffset
        cells[i].move(0, -scrollOffset);
        texts[i].move(0, -scrollOffset);

        // Перевіряємо, чи комірка в межах видимої області таблиці
        if (cells[i].getGlobalBounds().top + cells[i].getGlobalBounds().height > tablePos.y &&
            cells[i].getGlobalBounds().top < tablePos.y + tableHeight) {
            window.draw(cells[i]);
            window.draw(texts[i]);
        }

        // Повертаємо комірку та текст у початкову позицію
        cells[i].move(0, scrollOffset);
        texts[i].move(0, scrollOffset);
    }

    // Малюємо скролбар, якщо є що прокручувати
    if (maxScroll > 0) {
        // Обчислюємо висоту скролбару пропорційно до видимої області
        float scrollHeight = std::max(20.0f, tableBackground.getSize().y * (tableBackground.getSize().y / (rows * ROW_HEIGHT)));
        scrollbar.setSize(sf::Vector2f(10, scrollHeight));
        scrollbar.setFillColor(sf::Color(255, 255, 255, 150));
        // Позиціонуємо скролбар
        scrollbar.setPosition(tableBackground.getPosition().x + tableBackground.getSize().x + 10,
                             tableBackground.getPosition().y + (scrollOffset / maxScroll) * (tableBackground.getSize().y - scrollHeight));
        window.draw(scrollbar);
    }
    window.draw(backgroundButton);

    backButton.draw(window);
    window.display();
}

// Метод для обробки подій
void StatScreen::handleEvent(const sf::Event& event, ScreenManager& screenManager) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (backButton.isClicked(mousePos)) {
            backButton.playClickSound();
            screenManager.switchScreen(ScreenType::Start);
        }
    }
    if (event.type == sf::Event::MouseWheelScrolled && maxScroll > 0) {
        float delta = event.mouseWheelScroll.delta * -30.0f;
        scrollOffset = std::max(0.0f, std::min(maxScroll, scrollOffset + delta));
        std::cout << "Scroll Delta: " << delta << ", New Scroll Offset: " << scrollOffset << std::endl;
    }
}
