#include "Game.hpp"
#include "../Config.hpp"
#include <iostream>
#include <map>

#ifdef PLATFORM_WINDOWS
    #include <conio.h>
#else
    #include <curses.h>
#endif

Game::Game(int width, int height) 
    : width(width), height(height), snake(width/2, height/2), 
      renderer(width, height), running(true), needRestart(false), score(0) {
    spawnFood();
    lastUpdate = std::chrono::steady_clock::now();
}

void Game::run() {
    while (true) {
        // Основной игровой цикл
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
        
        // Игра закончилась - показываем меню
        renderer.showGameOver(score);
        
        // Ждём выбора (перезапустить или выйти)
        if (!handleGameOver()) {
            break;  // Выход из игры
        }
        
        // Перезапуск игры
        reset();
    }
}

bool Game::handleGameOver() {
    #ifdef PLATFORM_WINDOWS
        while (true) {
            if (_kbhit()) {
                int key = _getch();
                
                if (key == Config::KEY_RESTART || key == Config::KEY_RESTART_CAPS) {
                    return true;  // Перезапуск
                }
                if (key == Config::KEY_QUIT || key == Config::KEY_QUIT_Q || key == Config::KEY_QUIT_Q_CAPS) {
                    return false; // Выход
                }
            }
        }
    #else
        int key = getch();
        if (key == Config::KEY_RESTART || key == Config::KEY_RESTART_CAPS) {
            return true;
        }
        return false;
    #endif
}

void Game::reset() {
    // Сбрасываем всё состояние игры
    running = true;
    needRestart = false;
    score = 0;
    
    // Создаём новую змейку
    snake = Snake(width/2, height/2);
    
    // Новая еда
    spawnFood();
    
    // Сбрасываем таймер
    lastUpdate = std::chrono::steady_clock::now();
}

void Game::processInput() {
    #ifdef PLATFORM_WINDOWS
        if (_kbhit()) {
            int key = _getch();
            
            if (key == 224) {  // Специальная клавиша (стрелки)
                key = _getch();
                if (key == Config::KEY_UP_ARROW) snake.changeDirection(Direction::UP);
                if (key == Config::KEY_DOWN_ARROW) snake.changeDirection(Direction::DOWN);
                if (key == Config::KEY_LEFT_ARROW) snake.changeDirection(Direction::LEFT);
                if (key == Config::KEY_RIGHT_ARROW) snake.changeDirection(Direction::RIGHT);
            } else {
                // Буквенные клавиши
                if (key == Config::KEY_UP_W || key == Config::KEY_UP_W_CAPS) snake.changeDirection(Direction::UP);
                if (key == Config::KEY_DOWN_S || key == Config::KEY_DOWN_S_CAPS) snake.changeDirection(Direction::DOWN);
                if (key == Config::KEY_LEFT_A || key == Config::KEY_LEFT_A_CAPS) snake.changeDirection(Direction::LEFT);
                if (key == Config::KEY_RIGHT_D || key == Config::KEY_RIGHT_D_CAPS) snake.changeDirection(Direction::RIGHT);
                
                // Выход
                if (key == Config::KEY_QUIT || key == Config::KEY_QUIT_Q || key == Config::KEY_QUIT_Q_CAPS) {
                    running = false;
                    needRestart = false;
                }
            }
        }
    #else
        int key = getch();
        if (key != ERR) {
            if (key == KEY_UP) snake.changeDirection(Direction::UP);
            if (key == KEY_DOWN) snake.changeDirection(Direction::DOWN);
            if (key == KEY_LEFT) snake.changeDirection(Direction::LEFT);
            if (key == KEY_RIGHT) snake.changeDirection(Direction::RIGHT);
            if (key == Config::KEY_UP_W || key == Config::KEY_UP_W_CAPS) snake.changeDirection(Direction::UP);
            if (key == Config::KEY_DOWN_S || key == Config::KEY_DOWN_S_CAPS) snake.changeDirection(Direction::DOWN);
            if (key == Config::KEY_LEFT_A || key == Config::KEY_LEFT_A_CAPS) snake.changeDirection(Direction::LEFT);
            if (key == Config::KEY_RIGHT_D || key == Config::KEY_RIGHT_D_CAPS) snake.changeDirection(Direction::RIGHT);
            if (key == Config::KEY_QUIT || key == Config::KEY_QUIT_Q || key == Config::KEY_QUIT_Q_CAPS) {
                running = false;
                needRestart = false;
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
        needRestart = true;
    }
    
    // Столкновение с собой
    if (snake.checkSelfCollision()) {
        running = false;
        needRestart = true;
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