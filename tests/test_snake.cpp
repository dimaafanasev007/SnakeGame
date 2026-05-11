#include "../src/Snake.hpp"
#include <cassert>
#include <iostream>

void testSnakeInitialization() {
    Snake snake(10, 10);
    assert(snake.getBody().size() == 3);
    assert(snake.getHead().first == 10);
    assert(snake.getHead().second == 10);
    std::cout << "[OK] Snake initialization test passed\n";
}

void testSnakeMovement() {
    Snake snake(10, 10);
    auto oldHead = snake.getHead();
    snake.move();
    auto newHead = snake.getHead();
    assert(newHead.first > oldHead.first);
    std::cout << "[OK] Snake movement test passed\n";
}

void testSnakeGrowth() {
    Snake snake(10, 10);
    size_t oldSize = snake.getBody().size();
    snake.grow();
    snake.move();
    assert(snake.getBody().size() == oldSize + 1);
    std::cout << "[OK] Snake growth test passed\n";
}

void testSnakeDirectionChange() {
    Snake snake(10, 10);
    snake.changeDirection(Direction::UP);
    snake.move();
    auto newHead = snake.getHead();
    assert(newHead.second < 10);
    std::cout << "[OK] Direction change test passed\n";
}

void testSnakeSelfCollision() {
    Snake snake(10, 10);
    assert(!snake.checkSelfCollision());
    std::cout << "[OK] Self collision test passed\n";
}

int main() {
    std::cout << "Running Snake Game Tests...\n\n";
    
    testSnakeInitialization();
    testSnakeMovement();
    testSnakeGrowth();
    testSnakeDirectionChange();
    testSnakeSelfCollision();
    
    std::cout << "\n[OK] All tests passed!\n";
    return 0;
}