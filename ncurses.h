//Implenting UI
#include <ncurses.h>
#include <string>
#include <vector>

using namespace std;
const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 22;

void drawBox(WINDOW* win, int x, int y, int w, int h, const string& tittle){
	//borders
	for(int i = x; i < x + w; i++){
		mvwaddch(win, y, i, "-");
		mvwaddch(win, y + h - 1, i, "_");
	}

	for (int i = y; i < y + h; i++){
		mvwaddch(win, i, x, "|");
		mvwaddch(win, i, x + W - 1, "|");
	}

	mvwaddch(win, y, x, "+");
	mvwaddch(win, y, x + w - 1, "+");
	mvwaddch(win, y + h - 1, x, "+");
	mvwaddch(win, y + h - 1, x + w - 1, "+");

	if (w > tittle.length() + 2){
		mvwprintw(win, y, x + (w - tittle.length())/2,tittle.c_str());
	}
}

void drawMap(WINDOW* win){
	wclear(win); // clearn scrren

	//outer walls
	for (int y = 0; y < MAP_HEIGHT; y++){
		mvwaddch(win, y, 0, "#");
		mvwaddch(win, y, MAP_WIDTH -1, "#");
	}

	for (int x = 0; x < MAP_WIDTH; x++){
		mvwaddch(win, 0, x, "#");
		mvwaddch(win, MAP_HEIGHT-1, x, "#");
	}

	//rooms
	drawBox(win, 3, 2, 18, 5, "SEARS");
	drawBox(win, 25, 2, 18, 5, "Vendor Area");
	drawBox(win, 47, 2, 18, 5, "Never 21");
	mvwaddch(win, 8, 25, "c");
	drawBox(win, 7, 9, 38, 5, "Food Court");
	drawBox(win, 7, 16, 38, 5, "Angry Mom");
	drawBox(win, 49, 9, 24, 5, "Parking Lot");

	//doors
	mvwaddch(win, 5, 12, "D"); //sears
	mvwaddch(win, 5, 34, "D"); //vendor area
	mvwaddch(win, 5, 61, "D"); // Never 21
	mvwaddch (win, 12, 44, "D"); // food court

	//cop
	mvwaddch(win, MAP_HEIGHT-2, MAP_WIDTH/2, "C");

	//path
	for (int y = 7; y <= 8; y++){
		mvwaddch(win, y, 12, "|"); // towards sears 
		mvwaddch(win, y, 34, "|"); // vendoe area
		mvwaddch(win, y, 56, "|"); // never 21
	}
	for (int y = 14; y <= 15; y++){
		mvwaddch(win, y, 26, "|");
	}

	wrefreash(win);
}
