#include "Snake.hpp"

Snake::Snake(int startX, int startY) 
    : direction(Direction::RIGHT), 
      nextDirection(Direction::RIGHT), 
      growing(false) {
    body.push_back({startX, startY});
    body.push_back({startX - 1, startY});
    body.push_back({startX - 2, startY});
}

void Snake::move() {
    direction = nextDirection;
    
    auto newHead = body[0];
    
    switch (direction) {
        case Direction::UP:    newHead.second--; break;
        case Direction::DOWN:  newHead.second++; break;
        case Direction::LEFT:  newHead.first--; break;
        case Direction::RIGHT: newHead.first++; break;
        default: break;
    }
    
    body.insert(body.begin(), newHead);
    
    if (!growing) {
        body.pop_back();
    } else {
        growing = false;
    }
}

void Snake::grow() {
    growing = true;
}

void Snake::changeDirection(Direction newDir) {
    if ((direction == Direction::UP && newDir == Direction::DOWN) ||
        (direction == Direction::DOWN && newDir == Direction::UP) ||
        (direction == Direction::LEFT && newDir == Direction::RIGHT) ||
        (direction == Direction::RIGHT && newDir == Direction::LEFT) ||
        newDir == Direction::NONE) {
        return;
    }
    nextDirection = newDir;
}

bool Snake::checkSelfCollision() const {
    auto head = body[0];
    for (size_t i = 1; i < body.size(); i++) {
        if (body[i] == head) {
            return true;
        }
    }
    return false;
}

std::pair<int, int> Snake::getHead() const {
    return body[0];
}