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
		if (snake->parts[i].pos.x > 0 && snake->parts[i].pos.x < WIDTH &&
			snake->parts[i].pos.y >= 0 && snake->parts[i].pos.y <= HEIGHT)
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

void printLevel(Exit *exit)
{
	attron(COLOR_PAIR(4));
	for (int i = 0; i <= HEIGHT; i++)
	{
		for (int j = 0; j <= WIDTH; j++)
		{
			if (j == 0 || j == WIDTH)
				mvaddch(i, j, WALL_SYMBOL);
		}
	}
	if (exit->isOpen)
		mvaddch(exit->pos.y, exit->pos.x, ' ');
	attroff(COLOR_PAIR(4));
}

void printScore(Snake *snake)
{
	attron(COLOR_PAIR(42));
	char score[10];
	bzero(score, 10);
	sprintf(score, "%d / %d", 
		snake->size - SNAKE_MIN_SIZE,
			SNAKE_MAX_SIZE - SNAKE_MIN_SIZE);
	mvaddstr(HEIGHT, WIDTH + 2, score);
	attroff(COLOR_PAIR(6));
}

void render(Snake *snake, Fruit *fruit, Exit *exit)
{
	erase();
	printLevel(exit);
	if (!exit->isOpen)
		printFruit(fruit);
	printSnake(snake);
	printScore(snake);
}