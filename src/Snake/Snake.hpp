#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <utility>

enum class Direction {
    UP, DOWN, LEFT, RIGHT, NONE
};

class Snake {
public:
    Snake(int startX, int startY);
    
    void move();
    void grow();
    void changeDirection(Direction newDir);
    bool checkSelfCollision() const;
    
    std::pair<int, int> getHead() const;
    const std::vector<std::pair<int, int>>& getBody() const { return body; }
    
private:
    std::vector<std::pair<int, int>> body;
    Direction direction;
    Direction nextDirection;
    bool growing;
};

#endif