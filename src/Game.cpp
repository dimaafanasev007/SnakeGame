#include "Game.hpp"
#include <iostream>

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
            if (key == 224) {
                key = _getch();
                switch (key) {
                    case 72: snake.changeDirection(Direction::UP); break;
                    case 80: snake.changeDirection(Direction::DOWN); break;
                    case 75: snake.changeDirection(Direction::LEFT); break;
                    case 77: snake.changeDirection(Direction::RIGHT); break;
                }
            } else {
                switch (key) {
                    case 'w': case 'W': snake.changeDirection(Direction::UP); break;
                    case 's': case 'S': snake.changeDirection(Direction::DOWN); break;
                    case 'a': case 'A': snake.changeDirection(Direction::LEFT); break;
                    case 'd': case 'D': snake.changeDirection(Direction::RIGHT); break;
                    case 27: case 'q': case 'Q': running = false; break;
                }
            }
        }
    #else
        int key = getch();
        if (key != ERR) {
            switch (key) {
                case KEY_UP:    snake.changeDirection(Direction::UP); break;
                case KEY_DOWN:  snake.changeDirection(Direction::DOWN); break;
                case KEY_LEFT:  snake.changeDirection(Direction::LEFT); break;
                case KEY_RIGHT: snake.changeDirection(Direction::RIGHT); break;
                case 'w': case 'W': snake.changeDirection(Direction::UP); break;
                case 's': case 'S': snake.changeDirection(Direction::DOWN); break;
                case 'a': case 'A': snake.changeDirection(Direction::LEFT); break;
                case 'd': case 'D': snake.changeDirection(Direction::RIGHT); break;
                case 'q': case 'Q': running = false; break;
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
    
    auto snakeBody = snake.getBody();
    for (const auto& segment : snakeBody) {
        renderer.drawSnakeSegment(segment.first, segment.second);
    }
    
    auto foodPos = food.getPosition();
    renderer.drawFood(foodPos.first, foodPos.second);
    
    renderer.render(score);
}

void Game::checkCollisions() {
    auto head = snake.getHead();
    
    if (head.first <= 0 || head.first >= width - 1 || 
        head.second <= 0 || head.second >= height - 1) {
        running = false;
        renderer.showGameOver(score);
    }
    
    if (snake.checkSelfCollision()) {
        running = false;
        renderer.showGameOver(score);
    }
}

void Game::spawnFood() {
    food.randomizePosition(width, height);
    
    auto body = snake.getBody();
    for (const auto& segment : body) {
        if (food.getPosition() == segment) {
            food.randomizePosition(width, height);
            break;
        }
    }
}