#include "snake.h"

void init_colors()
{
	start_color();
	use_default_colors();
	init_color(COLOR_RED, INIT_COLOR_RED);
	init_color(COLOR_GREEN, INIT_COLOR_GREEN);
	init_color(COLOR_YELLOW, INIT_COLOR_YELLOW);
	init_color(COLOR_BLUE, INIT_COLOR_BLUE);
	init_color(COLOR_MAGENTA, INIT_COLOR_MAGENTA);
	init_color(COLOR_CYAN, INIT_COLOR_CYAN);
	init_color(COLOR_GRAY, INIT_COLOR_GRAY);
	init_color(COLOR_BLACK, INIT_COLOR_BLACK);
	init_color(COLOR_WHITE, INIT_COLOR_WHITE);
	init_pair(1, COLOR_RED, -1);
	init_pair(2, COLOR_GREEN, -1);
	init_pair(3, COLOR_YELLOW, -1);
	init_pair(4, COLOR_WHITE, -1);
	init_pair(5, COLOR_MAGENTA, -1);
	init_pair(6, COLOR_CYAN, -1);
	init_pair(7, COLOR_BLUE, -1);
	init_pair(42, COLOR_WHITE, -1);
}

void init_fruit(Fruit *fruit)
{
	fruit->pos.x = getRandNum(1, WIDTH - 1);
	fruit->pos.y = getRandNum(1, HEIGHT - 1);
	fruit->symbol = FRUIT_SYMBOL;
}

void init_snake(Snake *snake)
{
	bzero(snake, sizeof(Snake));
	snake->size = SNAKE_MIN_SIZE;
	snake->parts[0].pos.x = WIDTH / 2;
	snake->parts[0].pos.y = HEIGHT / 2;
	snake->parts[0].direction = '>';
	snake->parts[0].symbol = SNAKE_HEAD_SYMBOL;
	for (int i = 1; i < snake->size; i++)
	{
		snake->parts[i].pos.x = snake->parts[i - 1].pos.x - 1;
		snake->parts[i].pos.y = snake->parts[i - 1].pos.y;
		snake->parts[i].direction = '>';
		snake->parts[i].symbol = SNAKE_BODY_SYMBOL;
	}
}

void init_exit(Exit *exit)
{
	exit->pos.x = WIDTH;
	exit->pos.y = getRandNum(0, HEIGHT);
}

void init(WINDOW **win, Fruit *fruit, Snake *snake, Exit *exit)
{
	*win = initscr();
	curs_set(0);
	keypad(*win, true);
	nodelay(*win, true);
	init_colors();
	init_fruit(fruit);
	init_snake(snake);
	init_exit(exit);
}