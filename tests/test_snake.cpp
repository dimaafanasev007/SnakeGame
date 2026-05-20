#include "../src/Snake/Snake.hpp"
#include <cassert>
#include <iostream>

// 1. Тест создания змейки
void testSnakeInitialization() {
    Snake snake(10, 10);
    assert(snake.getBody().size() == 3);
    assert(snake.getHead().first == 10);
    assert(snake.getHead().second == 10);
    std::cout << "[OK] Snake initialization test passed\n";
}

// 2. Тест движения вправо (начальное направление)
void testSnakeMovementRight() {
    Snake snake(10, 10);
    auto oldHead = snake.getHead();
    snake.move();
    auto newHead = snake.getHead();
    assert(newHead.first == oldHead.first + 1);
    assert(newHead.second == oldHead.second);
    std::cout << "[OK] Snake movement right test passed\n";
}

// 3. Тест движения вверх
void testSnakeMovementUp() {
    Snake snake(10, 10);
    snake.changeDirection(Direction::UP);
    snake.move();
    auto newHead = snake.getHead();
    assert(newHead.second == 9);
    std::cout << "[OK] Snake movement up test passed\n";
}

// 4. Тест движения вниз
void testSnakeMovementDown() {
    Snake snake(10, 10);
    snake.changeDirection(Direction::DOWN);
    snake.move();
    auto newHead = snake.getHead();
    assert(newHead.second == 11);
    std::cout << "[OK] Snake movement down test passed\n";
}

// 5. Тест движения влево
void testSnakeMovementLeft() {
    Snake snake(10, 10);
    snake.changeDirection(Direction::LEFT);
    snake.move();
    auto newHead = snake.getHead();
    assert(newHead.first == 9);
    std::cout << "[OK] Snake movement left test passed\n";
}

// 6. Тест роста змейки
void testSnakeGrowth() {
    Snake snake(10, 10);
    size_t oldSize = snake.getBody().size();
    snake.grow();
    snake.move();
    assert(snake.getBody().size() == oldSize + 1);
    std::cout << "[OK] Snake growth test passed\n";
}

// 7. Тест: змейка не может развернуться на 180 градусов
void testSnakeNoReverse() {
    Snake snake(10, 10);
    // Сейчас движется вправо
    snake.changeDirection(Direction::LEFT);  // пытаемся развернуться
    snake.move();
    auto newHead = snake.getHead();
    // Должна продолжить движение вправо
    assert(newHead.first > 10);
    std::cout << "[OK] Snake no reverse test passed\n";
}

// 8. Тест смены направления несколько раз подряд
void testSnakeMultipleDirectionChanges() {
    Snake snake(10, 10);
    snake.changeDirection(Direction::UP);
    snake.changeDirection(Direction::LEFT);
    snake.changeDirection(Direction::DOWN);
    snake.move();
    auto newHead = snake.getHead();
    // Последнее валидное направление - вниз
    assert(newHead.second == 11);
    std::cout << "[OK] Multiple direction changes test passed\n";
}

// 9. Тест самопересечения (должно вернуть false когда всё ок)
void testSnakeSelfCollisionFalse() {
    Snake snake(10, 10);
    assert(!snake.checkSelfCollision());
    std::cout << "[OK] Self collision false test passed\n";
}

// 10. Тест получения позиции головы
void testSnakeGetHead() {
    Snake snake(10, 10);
    auto head = snake.getHead();
    assert(head.first == 10 && head.second == 10);
    snake.move();
    head = snake.getHead();
    assert(head.first == 11 && head.second == 10);
    std::cout << "[OK] Get head position test passed\n";
}

// 11. Тест получения тела змейки
void testSnakeGetBody() {
    Snake snake(10, 10);
    const auto& body = snake.getBody();
    assert(body.size() == 3);
    assert(body[0].first == 10 && body[0].second == 10);
    assert(body[1].first == 9 && body[1].second == 10);
    assert(body[2].first == 8 && body[2].second == 10);
    std::cout << "[OK] Get body test passed\n";
}

// 12. Тест: змейка не может изменить направление на NONE
void testSnakeInvalidDirection() {
    Snake snake(10, 10);
    snake.changeDirection(Direction::NONE);
    snake.move();
    auto newHead = snake.getHead();
    // Должна продолжать движение вправо
    assert(newHead.first == 11);
    std::cout << "[OK] Invalid direction ignored test passed\n";
}

int main() {
    std::cout << "Running Snake Game Tests...\n\n";
    
    testSnakeInitialization();
    testSnakeMovementRight();
    testSnakeMovementUp();
    testSnakeMovementDown();
    testSnakeMovementLeft();
    testSnakeGrowth();
    testSnakeNoReverse();
    testSnakeMultipleDirectionChanges();
    testSnakeSelfCollisionFalse();
    testSnakeGetHead();
    testSnakeGetBody();
    testSnakeInvalidDirection();
    
    std::cout << "\n[OK] All " << 12 << " tests passed!\n";
    return 0;
}