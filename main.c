#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define HEIGHT 20
#define WIDTH 100

#define KEY_SPACE 32

#define SNAKE_MAX_SIZE 15
#define SNAKE_MIN_SIZE 3

typedef struct
{
	int x;
	int y;
} Vector;

typedef struct
{
	int x;
	int y;
	Vector speed;
	char symbol;
	bool eatApple;
} SnakePart;

typedef struct
{
	SnakePart parts[SNAKE_MAX_SIZE];
	int size;
} Snake;

typedef struct 
{
	int x;
	int y;
	bool isOpen;
} Exit;

WINDOW *win;

int getRandNum(int min, int max)
{
	srand(time(NULL));
	return (rand() % (max - min + 1)) + min;
}

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

void init(WINDOW **win, Vector *apple, Snake *snake, Exit *exit)
{
	*win = initscr();
	curs_set(0);
	keypad(*win, true);
	nodelay(*win, true);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);

	apple->x = getRandNum(1, WIDTH - 1);
	apple->y = getRandNum(1, HEIGHT - 1);

	bzero(snake, sizeof(Snake));
	snake->size = SNAKE_MIN_SIZE;
	snake->parts[0].x = WIDTH / 2;
	snake->parts[0].y = HEIGHT / 2;
	snake->parts[0].speed.x = 1;
	snake->parts[0].speed.y = 0;
	snake->parts[0].symbol = '@';
	for (int i = 1; i < snake->size; i++)
	{
		snake->parts[i].x = snake->parts[i - 1].x - 1;
		snake->parts[i].y = snake->parts[i - 1].y;
		snake->parts[i].speed.x = 1;
		snake->parts[i].speed.y = 0;
		snake->parts[i].symbol = '#';
	}

	exit->x = getRandNum(0, WIDTH);
	if (exit->x == 0 || exit->x == WIDTH)
		exit->y = getRandNum(0, HEIGHT);
	else 
	{
		if (getRandNum(0, 1))
			exit->y = 0;
		else
			exit->y = HEIGHT;
	}
}

void keypress(int pressed, SnakePart *head)
{
	if (pressed == KEY_LEFT && head->speed.x != 1)
	{
		head->speed.x = -1;
		head->speed.y = 0;
	}
	else if (pressed == KEY_RIGHT && head->speed.x != -1)
	{
		head->speed.x = 1;
		head->speed.y = 0;
	}
	else if (pressed == KEY_UP && head->speed.y != 1)
	{
		head->speed.x = 0;
		head->speed.y = -1;
	}
	else if (pressed == KEY_DOWN && head->speed.y != -1)
	{
		head->speed.x = 0;
		head->speed.y = 1;
	}
	else if (pressed == KEY_SPACE)
		printMsg("PAUSED");
}

void changeSnakePosition(Snake *snake)
{
	for (int i = snake->size - 1; i >= 0; i--)
	{
		snake->parts[i].x += snake->parts[i].speed.x;
		snake->parts[i].y += snake->parts[i].speed.y;
		if (i != 0)
		{
			snake->parts[i].speed.x = snake->parts[i - 1].speed.x;
			snake->parts[i].speed.y = snake->parts[i - 1].speed.y;
		}
	}
}

void printSnake(Snake *snake)
{
	attron(COLOR_PAIR(2));
	for (int i = 0; i < snake->size; i++)
	{
		if (snake->parts[i].eatApple)
		{
			snake->parts[i + 1].symbol = 'O';
			snake->parts[i].eatApple = false;
			if (i == 0)
				snake->parts[i].symbol = '@';
			else
				snake->parts[i].symbol = '#';
			snake->parts[i + 1].eatApple = true;
			break;
		}
	}
	for (int i = 0; i < snake->size; i++)
	{
		mvaddstr(snake->parts[i].y, snake->parts[i].x,
			&snake->parts[i].symbol);
	}
	attroff(COLOR_PAIR(2));
}

void printFruit(Vector *apple)
{
	attron(COLOR_PAIR(1));
	mvaddstr(apple->y, apple->x, "o");
	attroff(COLOR_PAIR(1));
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
				mvaddstr(i, j, "+");
		}
		else
		{
			mvaddstr(i, 0, "+");
			mvaddstr(i, width, "+");
		}
	}
}

void snakeEat(Snake *snake, Vector *apple, Exit *exit, int *speed)
{
	if (snake->parts[0].x == apple->x && snake->parts[0].y == apple->y)
	{
		snake->size++;
		if (snake->size == SNAKE_MAX_SIZE)
			exit->isOpen = true;
		if (*speed > 30000)
			*speed -= 5000;
		snake->parts[0].eatApple = true;
		snake->parts[snake->size - 1].symbol = '#';
		snake->parts[snake->size - 1].speed.x = snake->parts[snake->size - 2].speed.x;
		snake->parts[snake->size - 1].speed.y = snake->parts[snake->size - 2].speed.y;
		snake->parts[snake->size - 1].x = 
			snake->parts[snake->size - 2].x - snake->parts[snake->size - 1].speed.x;
		snake->parts[snake->size - 1].y =
			snake->parts[snake->size - 2].y - snake->parts[snake->size - 1].speed.y;
		apple->x = getRandNum(1, WIDTH - 1);
		apple->y = getRandNum(1, HEIGHT - 1);
	}
}

void render(Snake *snake, Vector *apple, Exit *exit)
{
	erase();
	printWalls();
	if (exit->isOpen == false)
		printFruit(apple);
	else
		mvaddstr(exit->y, exit->x, " ");
	printSnake(snake);
}

bool checkCollision(Snake *snake, Exit *exit)
{
	if (exit->isOpen == true)
	{
		if (snake->parts[0].x == exit->x && snake->parts[0].y == exit->y)
			return false;
	}
	for (int i = 1; i < snake->size; i++)
	{
		if (snake->parts[0].x == snake->parts[i].x 
			&& snake->parts[0].y == snake->parts[i].y)
			return true;
	}
	for (int i = 0; i <= HEIGHT; i++)
	{
		if (i == 0 || i == HEIGHT)
		{
			for (int j = 0; j <= WIDTH; j++)
				if (snake->parts[0].x == j && snake->parts[0].y == i)
					return true;
		}
		else
			if ((snake->parts[0].x == 0 && snake->parts[0].y == i) 
			|| (snake->parts[0].x == WIDTH && snake->parts[0].y == i))
					return true;
	}
	return false;
}

bool checkEscape(Snake *snake, Exit *exit)
{
	if (snake->parts[snake->size - 1].x == exit->x 
		&& snake->parts[snake->size - 1].y == exit->y)
		return true;
	return false;
}

void main()
{
	Vector apple;
	Snake snake;
	Exit exit;
	int speed = 100000;
	init(&win, &apple, &snake, &exit);
	while (true)
	{
		int pressed = wgetch(win);
		keypress(pressed, &snake.parts[0]);
		changeSnakePosition(&snake);
		render(&snake, &apple, &exit);
		if (exit.isOpen == false)
			snakeEat(&snake, &apple, &exit, &speed);
		else 
		{
			if (checkEscape(&snake, &exit))
				printMsg("YOU ESCAPED!");	
		}
		if (checkCollision(&snake, &exit))
			printMsg("GAME OVER");
		usleep(speed);
	}

	endwin();
}