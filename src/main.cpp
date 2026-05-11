#include "Game.hpp"
#include <iostream>

int main() {
    const int WIDTH = 50;
    const int HEIGHT = 20;
    
    try {
        Game game(WIDTH, HEIGHT);
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}