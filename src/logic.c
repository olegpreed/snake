#include "snake.h"

void keypress(int pressed, SnakePart *head)
{
	if (pressed == KEY_LEFT && head->direction != '>')
		head->direction = '<';
	else if (pressed == KEY_RIGHT && head->direction != '<')
		head->direction = '>';
	else if (pressed == KEY_UP && head->direction != 'v')
		head->direction = '^';
	else if (pressed == KEY_DOWN && head->direction != '^')
		head->direction = 'v';
	else if (pressed == KEY_SPACE)
		printMsg("PAUSED");
}

void snakeMoves(Snake *snake)
{
	for (int i = snake->size - 1; i >= 0; i--)
	{
		switch (snake->parts[i].direction)
		{
			case '>':
				snake->parts[i].pos.x += 1;
				break;
			case '<':
				snake->parts[i].pos.x -= 1;
				break;
			case '^':
				snake->parts[i].pos.y -= 1;
				break;
			case 'v':
				snake->parts[i].pos.y += 1;
				break;
		}
		if (snake->parts[i].pos.y == -1)
			snake->parts[i].pos.y = HEIGHT;
		else if (snake->parts[i].pos.y == HEIGHT + 1)
			snake->parts[i].pos.y = 0;
		if (i != 0)
			snake->parts[i].direction = snake->parts[i - 1].direction;
	}
}

void addNewPart(SnakePart *partNew, SnakePart *partLast)
{
	partNew->symbol = SNAKE_BODY_SYMBOL;
	partNew->direction = partLast->direction;
	partNew->pos.x = partLast->pos.x;
	partNew->pos.y = partLast->pos.y;
	switch (partNew->direction)
	{
		case '>':
			partNew->pos.x -= 1;
			break;
		case '<':
			partNew->pos.x += 1;
			break;
		case '^':
			partNew->pos.y += 1;
			break;
		case 'v':
			partNew->pos.y -= 1;
			break;
	}
}

void snakeEats(Snake *snake, Fruit *fruit, Exit *exit, int *speed)
{
	snake->size++;
	if (snake->size == SNAKE_MAX_SIZE)
	{
		exit->isOpen = true;
		fruit->pos.x = -1;
		fruit->pos.y = -1;
	}
	else 
	{
		fruit->pos.x = getRandNum(1, WIDTH - 1);
		fruit->pos.y = getRandNum(1, HEIGHT - 1);
	}
	if (*speed > 30000)
		*speed -= 1000;
	snake->parts[0].eatApple = true;
	addNewPart(&snake->parts[snake->size - 1], &snake->parts[snake->size - 2]);
}

bool checkEat(SnakePart *head, Fruit *fruit)
{
	if (head->pos.x == fruit->pos.x && head->pos.y == fruit->pos.y)
		return true;
	return false;
}

bool checkCollision(Snake *snake, Exit *exit)
{
	if (exit->isOpen == true)
	{
		if (snake->parts[0].pos.x == exit->pos.x
			&& snake->parts[0].pos.y == exit->pos.y)
			return false;
	}
	for (int i = 1; i < snake->size; i++)
	{
		if (snake->parts[0].pos.x == snake->parts[i].pos.x 
			&& snake->parts[0].pos.y == snake->parts[i].pos.y)
			return true;
	}
	for (int i = 0; i <= HEIGHT; i++)
	{
		if ((snake->parts[0].pos.x == 0 
			|| snake->parts[0].pos.x == WIDTH)
				&& snake->parts[0].pos.y == i)
			return true;
	}
	return false;
}

bool checkEscape(Snake *snake, Exit *exit)
{
	if (exit->isOpen
		&& snake->parts[snake->size - 1].pos.x == exit->pos.x 
			&& snake->parts[snake->size - 1].pos.y == exit->pos.y)
		return true;
	return false;
}