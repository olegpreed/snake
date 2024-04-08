#ifndef SNAKE_H
#define SNAKE_H

#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "structs.h"

int getRandNum(int min, int max);

void init(WINDOW **win, Fruit *fruit, Snake *snake, Exit *exit);

void init_exit(Exit *exit);

void init_snake(Snake *snake);

void keypress(int pressed, SnakePart *head);
void snakeMoves(Snake *snake);
void snakeEats(Snake *snake, Fruit *fruit, Exit *exit, int *speed);
bool checkEat(SnakePart *head, Fruit *fruit);
bool checkCollision(Snake *snake, Exit *exit);
bool checkEscape(Snake *snake, Exit *exit);

void printMsg(char *str);
void printSnake(Snake *snake);
void printFruit(Fruit *fruit);
void printWalls();
void printScore(Snake *snake);
void render(Snake *snake, Fruit *fruit, Exit *exit);

extern WINDOW *win;

#endif