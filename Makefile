a.out: main.o
	g++ -g -fsanitize=address -std=c++23 main.o -lncurses

main.o: main.cc characters.h linkedlist.h ncurses.h
	g++ -g -fsanitize=address -std=c++23 -c main.cc

clean:
	rm -f a.out core *.o
