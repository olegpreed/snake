#ifndef STRUCTS_H
#define STRUCTS_H

#include "config.h"

typedef struct
{
	int x;
	int y;
} Vector;

typedef struct
{
	Vector pos;
	char direction;
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
	Vector pos;
	bool isOpen;
} Exit;

typedef struct
{
	Vector pos;
	char symbol;
} Fruit;

#endif