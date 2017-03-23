#include "snake.h"

void Snake::init(int xStart, int yStart, char* name)
{
	s = (Point**)malloc(sizeof(Point*) * 100);
	Point* p = (Point*)malloc(sizeof(Point));
	p->x = xStart;
	p->y = yStart;

	s[0] = p;

	xspeed = 1;
	yspeed = 0;

	size = 1;
	player = name;
	getHighscore();
}

void Snake::updatePoints()
{
	for (int i = size - 1; i > 0; i--)
	{
		s[i]->x = s[i - 1]->x;
		s[i]->y = s[i - 1]->y;
	}

	s[0]->x += xspeed;
	s[0]->y += yspeed;
}

void Snake::updateSnake(char c)
{
	if (c == 'w' || c == 'W')
	{
		if (yspeed != 1 && yspeed != -1)
		{
			xspeed = 0;
			yspeed = -1;
		}
	}
	else if (c == 's' || c == 'S')
	{
		if (yspeed != 1 && yspeed != -1)
		{
			xspeed = 0;
			yspeed = 1;
		}
	}
	else if (c == 'a' || c == 'A')
	{
		if (xspeed != 1 && xspeed != -1)
		{
			xspeed = -1;
			yspeed = 0;
		}
	}
	else if (c == 'd' || c == 'D')
	{
		if (xspeed != 1 && xspeed != -1)
		{
			xspeed = 1;
			yspeed = 0;
		}
	}
	else
		return;
}

void Snake::getHighscore()
{
	FILE* f = fopen("assets/snake_highscores.txt", "r");

	char line [128];
	
	if (f)
	{
		fgets(line, 128, f);

		highscoreName = (char*)malloc(sizeof(char) * 16);
		strcpy(highscoreName, strtok(line, ","));
		highscore = strtol(strtok(NULL, ","), NULL, 10);
		fclose(f);
	}
	else
	{
		FILE* n = fopen("assets/snake_highscores.txt", "w");

		highscoreName = (char*)malloc(sizeof(char) * 9);
		strcpy(highscoreName, "Thomas");
		highscore = 1;

		fprintf(n, "Thomas,1\n");
		fclose(n);
	}
}

void Snake::updateHighscore()
{
	FILE* old = fopen("assets/snake_highscores.txt", "r");
	FILE* temp = fopen("assets/temp.txt", "w");

	fprintf(temp, "%s,%d\n", player, size);

	char line[128];

	while(fgets(line, 128, old) != NULL)
	{
		fprintf(temp, "%s", line);
	}

	fclose(old);
	fclose(temp);
	remove("assets/snake_highscores.txt");
	rename("assets/temp.txt", "assets/snake_highscores.txt");
}

bool Snake::death()
{
	for (int i = 1; i < size; i++)
	{
		if (s[i]->x == s[0]->x && s[i]->y == s[0]->y)
		{
			// HIT ITSELF
			return 1;
		}
	}
	return 0;
}

void Snake::resetSnake()
{
	for (int i = 0; i < size; i++)
	{
		free(s[i]);
	}
	free(s);
}

void Snake::exit()
{
	resetSnake();
	free(player);
	free(highscoreName);
}