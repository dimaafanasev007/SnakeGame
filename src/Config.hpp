#ifndef CONFIG_HPP
#define CONFIG_HPP

// Настройки управления
namespace Config {
    // Стрелки (спец. коды)
    constexpr int KEY_UP_ARROW = 72;
    constexpr int KEY_DOWN_ARROW = 80;
    constexpr int KEY_LEFT_ARROW = 75;
    constexpr int KEY_RIGHT_ARROW = 77;
    
    // Буквенные клавиши
    constexpr int KEY_UP_W = 'w';
    constexpr int KEY_UP_W_CAPS = 'W';
    constexpr int KEY_DOWN_S = 's';
    constexpr int KEY_DOWN_S_CAPS = 'S';
    constexpr int KEY_LEFT_A = 'a';
    constexpr int KEY_LEFT_A_CAPS = 'A';
    constexpr int KEY_RIGHT_D = 'd';
    constexpr int KEY_RIGHT_D_CAPS = 'D';
    
    // Клавиши выхода/перезапуска
    constexpr int KEY_QUIT = 27;      // ESC
    constexpr int KEY_QUIT_Q = 'q';
    constexpr int KEY_QUIT_Q_CAPS = 'Q';
    constexpr int KEY_RESTART = 'r';
    constexpr int KEY_RESTART_CAPS = 'R';
}

#endif