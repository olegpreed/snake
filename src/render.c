#include "snake.h"

void printMsg(char *str)
{
	int i = 1;
	while (1)
	{
		int pressed = wgetch(win);
		if (pressed == KEY_SPACE)
			break;
		if (i == 7)
			i = 1;
		if (strcmp(str, "GAME OVER") == 0)
			i = 1;
		if (strcmp(str, "PAUSED") == 0)
			i = 3;
		attron(COLOR_PAIR(i));
		mvaddstr(HEIGHT / 2, WIDTH / 2 - 5, str);
		attroff(COLOR_PAIR(i));
		i++;
		refresh();
		usleep(100000);
	}
}

void printSnake(Snake *snake)
{
	attron(COLOR_PAIR(2));
	for (int i = 1; i < snake->size; i++)
	{
		if (snake->parts[i].eatApple)
			snake->parts[i].symbol = SNAKE_BODY_FULL_SYMBOL;
		else 
			snake->parts[i].symbol = SNAKE_BODY_SYMBOL;
	}
	for (int i = 0; i < snake->size; i++)
	{
		mvaddch(snake->parts[i].pos.y, snake->parts[i].pos.x,
			snake->parts[i].symbol);
	}
	for (int i = 0; i < snake->size; i++)
	{
		if (snake->parts[i].eatApple)
		{
			snake->parts[i].eatApple = false;
			if (i != snake->size - 1)
				snake->parts[i + 1].eatApple = true;
			break;
		}
	}
	attroff(COLOR_PAIR(2));
}

void printFruit(Fruit *fruit)
{
	attron(COLOR_PAIR(5));
	mvaddch(fruit->pos.y, fruit->pos.x, fruit->symbol);
	attroff(COLOR_PAIR(5));
}

void printWalls()
{
	int height = HEIGHT;
	int width = WIDTH;
	for (int i = 0; i <= height; i++)
	{
		if (i == 0 || i == height)
		{
			for (int j = 0; j <= width; j++)
				mvaddch(i, j, '+');
		}
		else
		{
			mvaddch(i, 0, '+');
			mvaddch(i, width, '+');
		}
	}
}

void printScore(Snake *snake)
{
	attron(COLOR_PAIR(6));
	char score[10];
	bzero(score, 10);
	sprintf(score, "%d / %d", snake->size - SNAKE_MIN_SIZE, SNAKE_MAX_SIZE - SNAKE_MIN_SIZE);
	mvaddstr(HEIGHT, WIDTH + 2, score);
	attroff(COLOR_PAIR(6));
}

void render(Snake *snake, Fruit *fruit, Exit *exit)
{
	erase();
	printWalls();
	if (exit->isOpen == false)
		printFruit(fruit);
	else
		mvaddch(exit->pos.y, exit->pos.x, ' ');
	printSnake(snake);
	printScore(snake);
}