#ifndef CONFIG_H
#define CONFIG_H

// Define the size of the window
#define HEIGHT 20
#define WIDTH 50

// Define the speed of the snake
#define SPEED 100000 // 1000000 = 1 second

#define KEY_SPACE 32

// Define the size of the snake
#define SNAKE_MAX_SIZE 10
#define SNAKE_MIN_SIZE 3

#define FRUIT_SYMBOL 'Q'
#define SNAKE_HEAD_SYMBOL '@'
#define SNAKE_BODY_SYMBOL 'o'
#define SNAKE_BODY_FULL_SYMBOL 'O'
#define WALL_SYMBOL 'H'

// Define color initialization values
#define INIT_COLOR_RED      1000, 0, 0
#define INIT_COLOR_GREEN    0, 1000, 0
#define INIT_COLOR_YELLOW   1000, 1000, 0
#define INIT_COLOR_BLUE     0, 0, 1000
#define INIT_COLOR_MAGENTA  1000, 0, 1000
#define INIT_COLOR_CYAN     0, 1000, 1000
#define INIT_COLOR_GRAY     100, 100, 100
#define INIT_COLOR_BLACK    0, 0, 0
#define INIT_COLOR_WHITE    1000, 1000, 1000

#define COLOR_GRAY 8

#endif