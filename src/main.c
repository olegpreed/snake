#include "snake.h"

WINDOW *win;

int main()
{
	Fruit fruit;
	Snake snake;
	Exit exit;
	int speed = SPEED;
	init(&win, &fruit, &snake, &exit);
	while (true)
	{
		int pressed = wgetch(win);
		keypress(pressed, &snake.parts[0]);
		snakeMoves(&snake);
		if (checkEat(&snake.parts[0], &fruit))
			snakeEats(&snake, &fruit, &exit, &speed);
		render(&snake, &fruit, &exit);
		if (checkEscape(&snake, &exit))
			printMsg("YOU ESCAPED!");	
		if (checkCollision(&snake, &exit))
			printMsg("GAME OVER");
		usleep(speed);
	}
	endwin();
	return 0;
}