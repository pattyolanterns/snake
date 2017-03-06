#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <ncurses.h>
#include "stdlib.h"
#include <string.h>

struct point
{
	int x;
	int y;
};
typedef struct point Point;

class Snake
{
public:
	void init(int xStart, int yStart, char* name);
	void updatePoints();
	void updateSnake(char c);
	bool death();
	void updateHighscore();
	void getHighscore();
	void freeTail();
	void resetSnake();
	void exit();

	int x;
	int y;
	int xspeed;
	int yspeed;
	Point** s;
	int size;
	char* player;
	char* highscoreName;
	int highscore;

	int endX;
	int endY;
};


#endif