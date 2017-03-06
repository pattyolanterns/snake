#ifndef __CANAVS_H__
#define __CANAVS_H__

#include <ncurses.h>
#include "snake.h"
#include <sys/timeb.h>
#include <stdlib.h>
#include <time.h>

#define XBOUND_LOW	4
#define XBOUND_HIGH	90

#define YBOUND_LOW	3
#define YBOUND_HIGH	36

class Canvas
{

public:
	void init(char* name);
	void loop();
	bool checkCollision();
	void updateBar();
	void dropFood();
	int getRandomNum (int min, int max);
	void printSnake();
	void updateTail();
	void parseInput();

	int xFood;
	int yFood;
	int prevX;
	int prevY;
	int curX;
	int curY;

private:
	void updateScreen();
	Snake* snake;

};

#endif