#include "canvas.h"

void Canvas::init(char* name)
{
	snake = new Snake();
	snake->init(XBOUND_LOW + 1, YBOUND_LOW + 1, name);

	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);

	move(1, XBOUND_LOW);
	printw("WELCOME TO THE GAME OF SNAKE.");
	
	for (int i = XBOUND_LOW; i <= XBOUND_HIGH; i++)
	{
		move(YBOUND_LOW, i);
		printw("%s", "-");
		move(YBOUND_HIGH, i);
		printw("%s", "-");
	}

	for (int j = YBOUND_LOW; j <= YBOUND_HIGH; j++)
	{
		move(j, XBOUND_LOW);
		printw("%s", "|");
		move(j, XBOUND_HIGH);
		printw("%s", "|");
	}

	move(YBOUND_LOW + 1, XBOUND_LOW + 1);
	printw("%s", "0");
	dropFood();
}

bool Canvas::checkCollision()
{
	// BORDER COLLSION
	if (snake->y == YBOUND_LOW || snake->y == YBOUND_HIGH || snake->x <= XBOUND_LOW 
	|| snake->x >= XBOUND_HIGH)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Canvas::loop()
{
	while(1)
	{
		updateScreen();
	}
}

void Canvas::updateScreen()
{
	struct timeb t_start, t_current;
	int t_diff;

	ftime(&t_start);

	// FRAME RATE
	do
	{
		ftime(&t_current);
		t_diff = (int) (1000.0 * (t_current.time - t_start.time) + (t_current.millitm - t_start.millitm));
	}
	while(t_diff <= (1000/15));
	// END FRAME RATE

	prevX = snake->s[snake->size-1]->x;
	prevY = snake->s[snake->size-1]->y;
	move(prevY, prevX);
	printw("%s", " ");

	snake->updatePoints();

	parseInput();

	// COLLIDES WITH WALL OR ITSELF 
	if (checkCollision())
	{
		snake->resetSnake();
		snake->init(XBOUND_LOW + 1, YBOUND_LOW + 1, snake->player);
	}
	// ATE A PIRCE OF FOOD
	else if (curX == xFood && curY == yFood)
	{
		Point* p = (Point*)malloc(sizeof(Point));
		p->x = prevX;
		p->y = prevY;
		snake->s[snake->size] = p;
		snake->size++;

		dropFood();
	}

	
	updateBar();
	refresh();
}

void Canvas::updateBar()
{
	int tempx;
	int tempy;
	getyx(stdscr, tempy, tempx);

	move(YBOUND_HIGH + 2, XBOUND_LOW);
	clrtoeol();
	printw("Score: %d      Highscore: %s %d", snake->size, snake->highscoreName, snake->highscore);
	if (snake->highscore < snake->size)
	{
		printw("      NEW HIGHSCORE!!");
	}
	move(tempy, tempx);
}

void Canvas::dropFood()
{
	int tempx;
	int tempy;
	getyx(stdscr, tempy, tempx);

	int randX, randY;
	randY = getRandomNum(YBOUND_LOW + 1, YBOUND_HIGH - 1);

	while (1)
	{
		randX = getRandomNum(XBOUND_LOW + 1, XBOUND_HIGH - 1);

		if (randX % 2 == 1)
			break;
	}

	move(randY, randX);
	printw("%s", "X");
	move(tempy, tempx);

	xFood = randX;
	yFood = randY;
}

int Canvas::getRandomNum (int min, int max)
{
    return (rand() % (1 + max - min)) + min;
}

void Canvas::printSnake()
{
	for (int i = 0; i < snake->size; i++)
	{
		move(snake->s[i]->y, snake->s[i]->x);
		printw("%s", "0");
	}
}

void Canvas::parseInput()
{
	char c = getch();

	if (c != ERR)
	{
		if (c == 'q' || c == 'Q')
		{
			endwin();
			snake->exit();
			exit(0);
		}
		else
		{
			snake->updateSnake(c);
		}
	}
}