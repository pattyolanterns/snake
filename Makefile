all:
	rm -f *.h.gch
	rm -f snake
	g++ -o snake *.cpp *.h -lncurses
