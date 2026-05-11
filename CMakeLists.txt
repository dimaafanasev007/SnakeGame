cmake_minimum_required(VERSION 3.10)
project(SnakeGame VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Определяем платформу
if(WIN32)
    add_compile_definitions(PLATFORM_WINDOWS)
else()
    add_compile_definitions(PLATFORM_LINUX)
endif()

# Основной исполняемый файл
add_executable(snake_game
    src/main.cpp
    src/Game.cpp
    src/Snake.cpp
    src/Food.cpp
    src/Renderer.cpp
)

# Тесты
add_executable(snake_tests
    tests/test_snake.cpp
    src/Snake.cpp
)

# Настройки для Windows
if(WIN32)
    target_link_options(snake_game PRIVATE -static)
    target_link_options(snake_tests PRIVATE -static)
endif()

# Включаем директории
target_include_directories(snake_game PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(snake_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Для Linux добавляем библиотеку ncurses
if(NOT WIN32)
    find_package(Curses REQUIRED)
    target_link_libraries(snake_game ${CURSES_LIBRARIES})
    target_include_directories(snake_game PRIVATE ${CURSES_INCLUDE_DIR})
endif()

# Включение предупреждений
if(MSVC)
    target_compile_options(snake_game PRIVATE /W4)
else()
    target_compile_options(snake_game PRIVATE -Wall -Wextra -Wpedantic)
endif()