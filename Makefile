a.out: main.o characters.h linkedlist.h ncurses.h
	g++ -g fsanitize=address -std=c++23 main.o

main.o: main.cc characters.h linkedlist.h ncurses.h
	g++ -g fsanitize=address -std=c++23 -c main.cc

clean:
	rm -f a.out core *.o
