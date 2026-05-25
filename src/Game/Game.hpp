#ifndef GAME_HPP
#define GAME_HPP

#include "../Snake/Snake.hpp"
#include "../Food/Food.hpp"
#include "../Renderer/Renderer.hpp"
#include <chrono>

class Game {
public:
    Game(int width, int height);
    ~Game() = default;
    
    void run();
    bool isRunning() const { return running; }
    int getScore() const { return score; }
    
private:
    void processInput();
    void update();
    void render();
    void checkCollisions();
    void spawnFood();
    bool handleGameOver();
    void reset();
    
    int width, height;
    Snake snake;
    Food food;
    Renderer renderer;
    bool running;
    bool needRestart;
    int score;
    std::chrono::steady_clock::time_point lastUpdate;
    static constexpr int UPDATE_INTERVAL_MS = 150;
};

#endif