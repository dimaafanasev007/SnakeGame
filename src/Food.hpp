#ifndef FOOD_HPP
#define FOOD_HPP

#include <utility>
#include <random>

class Food {
public:
    Food();
    
    void randomizePosition(int maxX, int maxY);
    void setPosition(int x, int y);
    std::pair<int, int> getPosition() const { return position; }
    
private:
    std::pair<int, int> position;
    std::mt19937 rng;
};

#endif