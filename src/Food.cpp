#include "Food.hpp"
#include <chrono>

Food::Food() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {
    position = {0, 0};
}

void Food::randomizePosition(int maxX, int maxY) {
    std::uniform_int_distribution<int> distX(1, maxX - 2);
    std::uniform_int_distribution<int> distY(1, maxY - 2);
    position = {distX(rng), distY(rng)};
}

void Food::setPosition(int x, int y) {
    position = {x, y};
}