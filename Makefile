all:
	rm -f *.h.gch
	rm -f snake
	g++ -o snake src/*.cpp -Iinclude -lncurses
