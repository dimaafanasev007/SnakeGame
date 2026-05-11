#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <string>

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();
    
    void clear();
    void drawBorder();
    void drawSnakeSegment(int x, int y);
    void drawFood(int x, int y);
    void render(int score);
    void showGameOver(int score);
    bool shouldClose() const { return false; }
    
private:
    void initConsole();
    void gotoxy(int x, int y);
    
    int width, height;
    std::vector<std::vector<char>> buffer;
};

#endif