#include "canvas.h"

int main (int argc, char** argv)
{
	char* name;

	if (argc < 2)
	{
		name = (char*)malloc(sizeof(char) * 8);
		strcpy(name, "Unkown");
	}
	else
	{
		name = (char*)malloc(sizeof(char) * 32);
		strcpy(name, argv[1]);
	}
	
	Canvas* canvas = new Canvas();
	canvas->init(name);

	canvas->loop();
	
	return 0;
}