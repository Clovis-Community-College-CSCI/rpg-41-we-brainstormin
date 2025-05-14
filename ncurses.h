//Implenting UI
#include <ncurses.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
const int MAP_WIDTH = 160;
const int MAP_HEIGHT = 33;

//declare player
int playerX = 110;
int playerY = 11;

int prevPlayerX = playerX;
int prevPlayerY = playerY;

void drawBox(WINDOW* win, int x, int y, int w, int h, const string& title){
    //borders
    for(int i = x; i < x + w; i++){ // top and bottom
        mvwaddch(win, y, i, '-');
        mvwaddch(win, y + h - 1, i, '_');
    }

    for (int i = y; i < y + h; i++){ // right and left
        mvwaddch(win, i, x, '|');
        mvwaddch(win, i, x + w - 1, '|');
    }

	//corners
    mvwaddch(win, y, x, '+');
    mvwaddch(win, y, x + w - 1, '+');
    mvwaddch(win, y + h - 1, x, '+');
    mvwaddch(win, y + h - 1, x + w - 1, '+');

	//title
    if (w >static_cast<int>(title.length()) + 2){
    mvwprintw(win, y, x + (w - static_cast<int>(title.length()))/2, "%s", title.c_str());
    }
}

void handleInput(int ch){
	prevPlayerX = playerX;
	prevPlayerY = playerY;

	//movement
    switch(ch){
        case KEY_UP: if(playerY > 1) playerY--; break;
        case KEY_DOWN: if(playerY < MAP_HEIGHT-2) playerY++; break;
        case KEY_LEFT: if(playerX > 1) playerX--; break;
        case KEY_RIGHT: if(playerX < MAP_WIDTH-2) playerX++; break;
    }
}

void drawMap(WINDOW* win){
//    wclear(win); // clear screen (causing screen to flicker)

	mvwaddch(win, prevPlayerY, prevPlayerX, ' ');
	mvwaddch(win, playerY, playerX, '@');

    //outer walls
    for (int y = 0; y < MAP_HEIGHT; y++){
        mvwaddch(win, y, 0, '#');
        mvwaddch(win, y, MAP_WIDTH -1, '#');
    }
	for (int x = 0; x < MAP_WIDTH; x++){
        mvwaddch(win, 0, x, '#');
        mvwaddch(win, MAP_HEIGHT-1, x, '#');
    }

    //rooms
    drawBox(win, 55, 2, 40, 5, "SEARS");
    drawBox(win, 30, 2, 18, 5, "Vendor Area");
    drawBox(win, 7, 2, 18, 5, "Never 21");
//    mvwaddch(win, 8, 25, 'c');
	drawBox(win, 7, 9, 80, 5, "Main Center");
	drawBox(win, 20, 16, 40, 5, "Food Court");
    drawBox(win, 100, 9, 25, 5, "Parking Lot");

    //doors
    mvwaddch(win, 6, 70, 'D'); //sears
    mvwaddch(win, 6, 35, 'D'); //vendor area
    mvwaddch(win, 6, 15, 'D'); // Never 21
    mvwaddch (win, 11, 86, 'D'); // food court

    //cop
//    mvwaddch(win, MAP_HEIGHT-2, MAP_WIDTH/2, 'C');

    //path
    for (int y = 7; y <= 8; y++){
        mvwaddch(win, y, 70, '|'); // towards sears
        mvwaddch(win, y, 35, '|'); // vendor area
        mvwaddch(win, y, 15, '|'); // never 21
    }
    for (int y = 14; y <= 15; y++){
        mvwaddch(win, y, 45, '|');
    }

    //draw player
    mvwaddch(win, playerY, playerX, '@');

    wrefresh(win);
}

void mapTest() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);//cursor hide

    //arrow keys
    mousemask(0, NULL);
    nodelay(stdscr, TRUE);

    //game loop
	int ch;
    while((ch = getch()) != 'q') { // q to quit
        handleInput(ch);
        drawMap(stdscr);

        // display instructions
        mvprintw(MAP_HEIGHT + 2, 0, "Use : arrow keys to move, space to attack, and 'q' to quit");
        refresh();
    }
    endwin();
} 
