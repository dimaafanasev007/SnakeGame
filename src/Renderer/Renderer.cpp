#include "Renderer.hpp"
#include <iostream>
#include <thread>
#include <chrono>

#ifdef PLATFORM_WINDOWS
    #include <windows.h>
    #include <conio.h>
#else
    #include <cstdio>
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
    #include <curses.h>
#endif

Renderer::Renderer(int width, int height) : width(width), height(height) {
    buffer.resize(height, std::vector<char>(width, ' '));
    initConsole();
}

Renderer::~Renderer() {
    #ifndef PLATFORM_WINDOWS
        endwin();
    #endif
}

void Renderer::initConsole() {
    #ifdef PLATFORM_WINDOWS
        SetConsoleTitle("Snake Game");
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        system("cls");
    #else
        initscr();
        cbreak();
        noecho();
        curs_set(0);
        nodelay(stdscr, TRUE);
        keypad(stdscr, TRUE);
        clear();
    #endif
}

void Renderer::gotoxy(int x, int y) {
    #ifdef PLATFORM_WINDOWS
        COORD coord;
        coord.X = static_cast<SHORT>(x);
        coord.Y = static_cast<SHORT>(y);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    #else
        move(y, x);
    #endif
}

void Renderer::clear() {
    for (auto& row : buffer) {
        std::fill(row.begin(), row.end(), ' ');
    }
}

void Renderer::drawBorder() {
    for (int x = 0; x < width; x++) {
        buffer[0][x] = '#';
        buffer[height - 1][x] = '#';
    }
    for (int y = 0; y < height; y++) {
        buffer[y][0] = '#';
        buffer[y][width - 1] = '#';
    }
}

void Renderer::drawSnakeSegment(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        buffer[y][x] = 'O';
    }
}

void Renderer::drawFood(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        buffer[y][x] = '@';
    }
}

void Renderer::render(int score) {
    gotoxy(0, 0);
    
    std::string output;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            output += buffer[y][x];
        }
        output += '\n';
    }
    
    output += "Score: " + std::to_string(score) + "\n";
    output += "Controls: WASD or Arrows | Q to quit";
    
    #ifdef PLATFORM_WINDOWS
        std::cout << output;
    #else
        printw("%s", output.c_str());
        refresh();
    #endif
}

void Renderer::showGameOver(int score) {
    #ifdef PLATFORM_WINDOWS
        system("cls");
        std::cout << "\n\n\n\n\n";
        std::cout << "     ========== GAME OVER ==========\n\n";
        std::cout << "          Final Score: " << score << "\n\n";
        std::cout << "     Press any key to exit...\n";
        std::cout << "     ================================\n";
        _getch();
    #else
        clear();
        mvprintw(height/2 - 2, (width-20)/2, "========== GAME OVER ==========");
        mvprintw(height/2, (width-20)/2, "Final Score: %d", score);
        mvprintw(height/2 + 2, (width-20)/2, "Press any key to exit...");
        mvprintw(height/2 + 4, (width-20)/2, "================================");
        refresh();
        nodelay(stdscr, FALSE);
        getch();
    #endif
}