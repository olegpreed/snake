#include "snake.h"

int getRandNum(int min, int max)
{
	srand(time(NULL));
	return (rand() % (max - min + 1)) + min;
}