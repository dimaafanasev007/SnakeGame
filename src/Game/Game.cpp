#include "Game.hpp"
#include <iostream>
#include <map>

#ifdef PLATFORM_WINDOWS
    #include <conio.h>
#else
    #include <curses.h>
#endif

Game::Game(int width, int height) 
    : width(width), height(height), snake(width/2, height/2), 
      renderer(width, height), running(true), score(0) {
    spawnFood();
    lastUpdate = std::chrono::steady_clock::now();
}

void Game::run() {
    while (running) {
        processInput();
        
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate);
        
        if (elapsed.count() >= UPDATE_INTERVAL_MS) {
            update();
            render();
            lastUpdate = now;
        }
        
        #ifndef PLATFORM_WINDOWS
            napms(10);
        #endif
    }
}

void Game::processInput() {
    #ifdef PLATFORM_WINDOWS
        if (_kbhit()) {
            int key = _getch();
            
            // Словарь для стрелок (специальные клавиши)
            static const std::map<int, Direction> arrowMap = {
                {72, Direction::UP},   // стрелка вверх
                {80, Direction::DOWN}, // стрелка вниз
                {75, Direction::LEFT}, // стрелка влево
                {77, Direction::RIGHT} // стрелка вправо
            };
            
            // Словарь для обычных клавиш (направления и выход)
            static const std::map<int, std::pair<Direction, bool>> keyMap = {
                // Направления (буквы)
                {'w', {Direction::UP, false}}, {'W', {Direction::UP, false}},
                {'s', {Direction::DOWN, false}}, {'S', {Direction::DOWN, false}},
                {'a', {Direction::LEFT, false}}, {'A', {Direction::LEFT, false}},
                {'d', {Direction::RIGHT, false}}, {'D', {Direction::RIGHT, false}},
                // Выход
                {27, {Direction::NONE, true}},   // ESC
                {'q', {Direction::NONE, true}}, {'Q', {Direction::NONE, true}}
            };
            
            if (key == 224) {  // Специальная клавиша (стрелки)
                key = _getch();
                auto it = arrowMap.find(key);
                if (it != arrowMap.end()) {
                    snake.changeDirection(it->second);
                }
            } else {
                auto it = keyMap.find(key);
                if (it != keyMap.end()) {
                    if (it->second.second) {  // если нужно выйти
                        running = false;
                    } else {
                        snake.changeDirection(it->second.first);
                    }
                }
            }
        }
    #else
        int key = getch();
        if (key != ERR) {
            static const std::map<int, std::pair<Direction, bool>> keyMap = {
                {KEY_UP, {Direction::UP, false}}, {KEY_DOWN, {Direction::DOWN, false}},
                {KEY_LEFT, {Direction::LEFT, false}}, {KEY_RIGHT, {Direction::RIGHT, false}},
                {'w', {Direction::UP, false}}, {'W', {Direction::UP, false}},
                {'s', {Direction::DOWN, false}}, {'S', {Direction::DOWN, false}},
                {'a', {Direction::LEFT, false}}, {'A', {Direction::LEFT, false}},
                {'d', {Direction::RIGHT, false}}, {'D', {Direction::RIGHT, false}},
                {'q', {Direction::NONE, true}}, {'Q', {Direction::NONE, true}}
            };
            
            auto it = keyMap.find(key);
            if (it != keyMap.end()) {
                if (it->second.second) {
                    running = false;
                } else {
                    snake.changeDirection(it->second.first);
                }
            }
        }
    #endif
}

void Game::update() {
    snake.move();
    checkCollisions();
    
    if (snake.getHead() == food.getPosition()) {
        snake.grow();
        score++;
        spawnFood();
    }
}

void Game::render() {
    renderer.clear();
    renderer.drawBorder();
    
    for (const auto& segment : snake.getBody()) {
        renderer.drawSnakeSegment(segment.first, segment.second);
    }
    
    auto foodPos = food.getPosition();
    renderer.drawFood(foodPos.first, foodPos.second);
    renderer.render(score);
}

void Game::checkCollisions() {
    auto head = snake.getHead();
    
    // Столкновение со стенами
    if (head.first <= 0 || head.first >= width - 1 || 
        head.second <= 0 || head.second >= height - 1) {
        running = false;
        renderer.showGameOver(score);
    }
    
    // Столкновение с собой
    if (snake.checkSelfCollision()) {
        running = false;
        renderer.showGameOver(score);
    }
}

void Game::spawnFood() {
    food.randomizePosition(width, height);
    
    // Убедиться, что еда не появилась на змейке
    for (const auto& segment : snake.getBody()) {
        if (food.getPosition() == segment) {
            food.randomizePosition(width, height);
            break;
        }
    }
}